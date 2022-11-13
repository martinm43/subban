"""
 For parsing .csv files obtained from the Sports-Reference website.
 All data belongs to Sports Reference LLC themselves, an excellent site you 
 should consider supporting if you like this stuff.
 
 Inputs:
     season_year_start - year in which the "season year" starts (nominally)
     filename of csv containing Sports Reference data
     csv must have the following header format:
         
     Date,Visitor,Visitor_G,Home,Home_G,Game_Decided_By,Att.,LOG,Notes
     
        
"""
from math import isnan
from pprint import pprint
import pandas as pd
from datetime import datetime

from nhl_database.queries import epochtime, full_name_to_id
from nhl_database.nhl_data_models import database, Games

season_year_start = 2022
filename = "2021-2022-hockey.csv"
df = pd.read_csv(filename)
imported_season_dicts = df.T.to_dict().values()

print(len(imported_season_dicts))

SQLITE_MAX_VARIABLE_NUMBER = 100

id = 1
season_dicts=[]
for d in imported_season_dicts:

    # add in the season year
    d["season_year"] = season_year_start

    # standardized date conversion
    datestr = d["Date"]
    datefmt = "%Y-%m-%d"
    date_datetime = datetime.strptime(datestr, datefmt)
    d["datetime"] = epochtime(date_datetime)
    d['game_datetime']=d['datetime']
    d.pop('datetime')
    d["date"] = date_datetime.strftime("%Y-%m-%d")
    d['game_date']=d['date']
    d.pop('date')
    

    # convert values that should be ints into ints
    # and address zero-attendance COVID games
    if not isnan(d["Att."]):
        d["Att."]=int(d["Att."])
    else:
        d["Att."]=0
    d["attendance"]=d["Att."]
    d.pop('Att.')
    
    
    try:
        if isnan(d["Game_Decided_By"]):
            d["Game_Decided_By"]="Regulation"
    except TypeError:
        pass
    
    try:
        if isnan(d["Notes"]):
            d["Notes"]=""
    except TypeError:
            pass

    d["id"] = d['season_year'] * 10000 + id
    d=dict((k.lower(), v) for k, v in d.items())
    #print(d)
    d.pop('date')
    season_dicts.append(d)
    id += 1


season_dicts = list(season_dicts)
#print("Sample dict to be entered:")
pprint(season_dicts[0])


with database.atomic() as txn:
    size = (SQLITE_MAX_VARIABLE_NUMBER // len(season_dicts[0])) - 1
    # remove one to avoid issue if peewee adds some variable
    for i in range(0, len(season_dicts), size):
        Games.insert_many(
            season_dicts[i : i + size]
        ).on_conflict_replace().execute()
        
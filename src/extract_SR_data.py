"""
 For parsing .csv files obtained from the Sports-Reference website.
 All data belongs to Sports Reference LLC themselves, an excellent site you 
 should consider supporting if you like this stuff.
 
 Inputs:
     season_year_start - year in which the "season year" starts (nominally)
     filename of csv containing Sports Reference data
     csv must have the following header format:
         
     Date,visitor,visitor_g,home,home_g,Game_Decided_By,Att.,log,Notes
     
 File must have format "2022-2023-hockey.csv" for season_year 2023, etc.        
"""
import sys
from math import isnan
from pprint import pprint
import pandas as pd
from datetime import datetime

from nhl_database.queries import epochtime, full_name_to_id
from nhl_database.nhl_data_models import database, Games

season_year = int(sys.argv[1])
prev_season_year = season_year-1
filename = str(prev_season_year)+"-"+str(season_year)+"-hockey.csv"
df = pd.read_csv(filename)
imported_season_dicts = df.T.to_dict().values()

print(len(imported_season_dicts))

SQLITE_MAX_VARIABLE_NUMBER = 100

id = 1
season_dicts=[]
for d in imported_season_dicts:

    # add in the season year
    d["season_year"] = season_year

    # add in team ids
    #print(d['visitor'])
    #print(d)
    d["visitor_team_id"]=full_name_to_id(d["visitor"])
    d["home_team_id"]=full_name_to_id(d["home"])

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
    d.pop('Time')    

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
        

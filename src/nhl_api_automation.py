# -*- coding: utf-8 -*-
"""
Created on Fri Jan 27 23:31:39 2023

@author: AdminLocal
"""

import requests
from datetime import datetime, timedelta

import sqlite3

from nhl_database.queries import epochtime
from nhl_database.nhl_data_models import database, Games

base_url = "https://statsapi.web.nhl.com/api/v1/schedule"

# API call variable

start_date = datetime(2023,1,26) #date, used for observation
end_date = datetime.today() - timedelta(days=1)
loop_date = start_date

while loop_date < end_date:
    game_date = loop_date.strftime("%Y-%m-%d")

    r = requests.get(url=base_url+"?date="+game_date)
    data = r.json()
    
    try:
        games = data["dates"][0]["games"]
    except IndexError:
        loop_date = loop_date + timedelta(days=1)
        print("No games played on "+game_date)
        continue 
    
    # NB: Schedule provides all dates in the Zulu time, so some dates are
    # "in the future" but not really.
    
    # As with the NBA data, more advanced information can be obtained using the APO
    # and this file will provide a basis. The NHL API is far easier to use
    # than the NBA API, and has been used by other people for far more advanced
    # projects. Here this is only for scores.
    
    game_list = []
    for g in games:
        game_dict = {}
        r_game = requests.get(
            "https://statsapi.web.nhl.com/api/v1/game/"+str(g["gamePk"])+"/linescore")
        game_data = r_game.json()
        game_dict["away_team_name"] = game_data["teams"]["away"]["team"]["name"]
        game_dict["away_g"] = game_data["teams"]["away"]["goals"]
        game_dict["home_team_name"] = game_data["teams"]["home"]["team"]["name"]
        game_dict["home_g"] = game_data["teams"]["home"]["goals"]
    
        if game_data["currentPeriodOrdinal"] == "SO":
            game_dict["Game_Decided_By"] = "SO"
        elif game_data["currentPeriodOrdinal"] == "OT":
            game_dict["Game_Decided_By"] = "OT"
        elif game_data["currentPeriodOrdinal"] == "3rd":
            game_dict["Game_Decided_By"] = "Regulation"
        else:
            print("Error - check game status for game "+str(g["gamePk"]))
            break
        game_dict["game_date"] = game_date
        game_dict["game_datetime"] = datetime.fromisoformat(game_date)
        game_dict["datetime"] = epochtime(game_dict["game_datetime"])
        game_list.append(game_dict)
    
    for z in game_list:
        #Quick 
        Games.update(visitor_g = z["away_g"], home_g = z["home_g"]).where((Games.game_date == z["game_date"]) & (Games.visitor == z["away_team_name"]) & (Games.home == z["home_team_name"])).execute()


    loop_date = loop_date + timedelta(days=1)

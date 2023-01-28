# -*- coding: utf-8 -*-
"""
Created on Fri Jan 27 23:31:39 2023

@author: AdminLocal
"""

import requests
import pandas as pd
from datetime import datetime

from nhl_database.queries import epochtime

base_url = "https://statsapi.web.nhl.com/api/v1/schedule"

#API call variable
game_date = "2023-01-07"

r = requests.get(url=base_url+"?date="+game_date)
data = r.json()

games = data["dates"][0]["games"]

#NB: Schedule provides all dates in the Zulu time, so some dates are
#"in the future" but not really.

#As with the NBA data, more advanced information can be obtained using the APO
#and this file will provide a basis. The NHL API is far easier to use
#than the NBA API, and has been used by other people for far more advanced
#projects. Here this is only for scores.

game_list=[]
for g in games:
    game_dict = {}
    r_game = requests.get("https://statsapi.web.nhl.com/api/v1/game/"+str(g["gamePk"])+"/linescore")
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
    

# coding: utf-8
"""
Script for determining on a yes-no basis whether the predicted elo_odds are accurate 
(i.e for how many times the home team has a winning percentage over 50% does the home team actually win)

Inputs: None
        start_year and end_year can be manually adjusted.
        Data is sourced from database.
        
Outputs: None
        Prints overall "success rate" to terminal.

"""
import numpy as np

from random import randint
from nhl_database.queries import season_query, team_elo_rating
from nhl_database.nhl_data_models import Games
from analytics.purdy import Elo_regress

#x = Games.select().order_by(Games.season_year.asc()).get()
start_year = 2007 #Temporary fix here - Elo only starts from 2007 in this iteration of simple sports model
x = Games.select().order_by(Games.season_year.desc()).get()
end_year = x.season_year

for year in range(start_year, end_year+1):

    season_query(year)
    games = season_query(year)
    success_rate = []

    for z in games:
        elo_diff = team_elo_rating(z[2], z[4]) - team_elo_rating(z[0], z[4])
        elo_odds = Elo_regress(elo_diff)
        pts_diff = z[3] - z[1]
        if (elo_odds > 0.5 and pts_diff > 0) or (elo_odds <= 0.5 and pts_diff < 0):
            success_rate.append(1)
        else:
            success_rate.append(0)

    sr_array = np.asarray(success_rate)
    success_rate = np.sum(sr_array) / sr_array.size * 100

    success_rate_string = "%.1f" % success_rate

    print("Accuracy in year " + str(year) + ": " + success_rate_string + "%")

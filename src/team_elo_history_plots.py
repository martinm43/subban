"""
MODULE UNDER DEVELOPMENT - NOT READY FOR USE. - MM.

Short sample script that plots the moving elo for a given team over their 
available history in the Elo database.

Inputs: None
    
Outputs: Bitmap images of the Elo rating history of all 30 teams

"""

import matplotlib.pyplot as plt
import pandas as pd
import sqlite3
import time

from nhl_database.queries import team_abbreviation

for team_id in range(1, 31):
    conn = sqlite3.connect("nhl_data.sqlite")
    query = "SELECT datetime,elo_rating FROM team_elo_data where team_id = " + str(
        team_id
    )

    df = pd.read_sql_query(query, conn)

    df["datetime"] = pd.to_datetime(df["datetime"], unit="s")

    # get the appropriate colours
    cursor = conn.cursor()
    cursor.execute(
        "SELECT primary_color from teams where id=" + str(team_id)
    )
    s = cursor.fetchall()

    plt.plot(
        df["datetime"],
        df["elo_rating"].rolling(41).mean(),
        label="41 game moving avg.",
        color=s[0][0],
    )
    plt.xticks(rotation=45)
    plt.legend()
    plt.title("Elo rating history of " + team_abbreviation(team_id))
    plt.show()

    time.sleep(3)

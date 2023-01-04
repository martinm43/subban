"""
Endfile for testing integration with the mcss.cpp shared library
Using the python library developed using C++ to rapidly speed up how standings are printed and presented
and allow for integration with more 'modern' interfaces -think flask or Django

"""

# Future import first


from nhl_database.nhl_data_models import Teams
from nhl_database.queries import elo_ratings_list, epochtime
from datetime import datetime, timedelta

from pprint import pprint


def playoff_odds_calc(start_datetime, end_datetime, season_year, ratings_mode="Elo"):
    """

    Given a start, end, season_year, and a ratings calculation method
    with some other factors, determine the odds of every team of making
    the playoffs at any given time.

    Parameters
    ----------
    start_datetime : start of period to be used for analysis (Unix timestamp)
    end_datetime : end of period to be used for analysis (Unix timestamp)
    season_year : year that season nominally ends in
                (e.g. if season ends in 2021, use 2021)
    ratings_mode : Elo or SRS. Default mode is Elo.

    Returns
    -------
    a list of 2-item lists for each team (first item ATL, last item WAS)
    each list consists of [playoff odds,average wins]

    """

    from predict.cython_mcss.mcss_ext2 import simulations_result_vectorized
    from analytics.SRS import SRS
    from analytics.morey import SRS_regress, Elo_regress
    from analytics.wins_script import points_list

    from nhl_database.queries import games_query, games_won_query, future_games_query

    # Test results/inputs
    if end_datetime < start_datetime:
        print("Start date is after end date, please check inputs")
        return 1

    predict_date = end_datetime
    predict_season_year = season_year

    # Get List Of Known Wins
    games_list = games_query(start_datetime, end_datetime)
    #print("Debug print of points based analysis")
    current_points = points_list(season_year,start_datetime,end_datetime)
    #print(len(games_list))
    games_won_list_cpp = games_won_query(games_list, return_format="matrix").tolist()

    # Get team data.
    teams_list = Teams.select().order_by(Teams.id)
    # ending 2014-present excluding 2020, 2021
    if season_year >= 2014:
        teams_list = [
        [x.id, x.team_name, x.abbreviation, x.division, x.conference,0,0] 
           for x in teams_list
        ]
    # ending 1999 to ending 2013
    else:
        print(season_year)
        teams_list = [
        [x.id, x.team_name, x.abbreviation, x.legacy_divisions_3, x.conference,0,0] 
           for x in teams_list
        ]
    #print(len(current_points))
    for i,x in enumerate(teams_list):
        #print(i)
        x[6] = current_points[i]

    # Division and conf changes go here
    for z in teams_list:
        #print(z)
        if season_year <= 2013 and z[0]==11: #Red wings
            z[4]="W"
        if season_year <= 2013 and z[0]==9: #Blue Jackets
            z[4]="W"
        if season_year <= 2011 and z[0]==26: #the former Atlanta Thrashers
            z[4]="E"
            z[1]="Atlanta Thrashers"
            print(z[3])


    #pprint("Fixed")
    #pprint(teams_list)



    # Get future games (away_team, home_team, home_team_win_probability)

    future_games_list = future_games_query(predict_date, predict_season_year)

    if ratings_mode == "SRS":
        # Get Team Ratings (and create Team object list)
        ratings_list = SRS(
            games_query(start_datetime, end_datetime)
        ).tolist()  # get ratings for that time.

        for i, x in enumerate(teams_list):
            x[5] = ratings_list[i]
            for j in range(1, 5):  # "all strings"
                x[j] = x[j].encode("utf-8")

        for x in future_games_list:
            away_team_rating = teams_list[x[0] - 1][5]
            home_team_rating = teams_list[x[1] - 1][5]
            SRS_diff = home_team_rating - away_team_rating
            x.append(SRS_regress(SRS_diff))


    if ratings_mode == "Elo":
        ratings_list = elo_ratings_list(epochtime(end_datetime))
        for i, x in enumerate(teams_list):
            x[5] = ratings_list[i]
            for j in range(1, 5):  # "all strings"
                x[j] = x[j].encode("utf-8")

        for x in future_games_list:
            away_team_rating = teams_list[x[0] - 1][5]
            home_team_rating = teams_list[x[1] - 1][5]
            Elo_diff = home_team_rating - away_team_rating
            x.append(Elo_regress(Elo_diff))


    #pprint("Future games")
    #pprint(future_games_list)

    #pprint(teams_list)

    #pprint(games_won_list_cpp)
    team_results = simulations_result_vectorized(
        games_won_list_cpp, future_games_list, teams_list, season_year,current_points
    )
    #print(team_results)
    # Return (top 8 odds, average wins, top 6 odds, and play in tournament odds).
    team_results = [
        [x[0] * 100.0, x[1], x[2] * 100.0, x[3] * 100.0, x[4]] for x in team_results
    ]
    return team_results


def playoff_odds_print(team_results,season_year):
    """
    Prints table based on alphabetically ordered team results matrix.
    Team results are the output of playoff_odds_calc.
    """
    # Custom local function for formatting
    from tabulate import tabulate

    def format_percent(percent_float):
        return str(percent_float) + "%"

    # Format the results into a table
    teams = Teams.select().order_by(Teams.id)

    teams_dict = [
              dict(list(zip(["Team", "Conference"], [i.abbreviation, i.conference])))
        for i in teams
    ]


    #The dict for the teams
    #Conference change implemented here for printing.
    for z in teams_dict:
        if z["Team"]=="DET" and season_year <= 2013:
            z["Conference"]="W"
        if z["Team"]=="CBJ" and season_year <= 2013:
            z["Conference"]="W"
        if z["Team"]=="WPG" and season_year <= 2011: #the Atlanta Thrashers
            z["Conference"]="E"
            z['Team']="ATL"


    for i, d in enumerate(teams_dict):
        d["PF%"] = round(team_results[i][0], 1)
        d["Avg. Wins"] = round(team_results[i][1], 1)
        d["Unused"] = round(team_results[i][2], 1)
        d["WC%"] = round(team_results[i][3], 1)
        d["Points"] = round(team_results[i][4], 1)

        # Convert into percentages for printing
        d["PF%"] = format_percent(d["PF%"])
        d["Unused"] = format_percent(d["Unused"])
        d["WC%"] = format_percent(d["WC%"])


    teams_dict.sort(key=lambda x: (x["Conference"], -x["Points"]))

    team_tuples = [
        (
            d["Conference"],
            d["Team"],
            d["Avg. Wins"],
            d["Points"],
            d["PF%"],
            d["WC%"]
        )
        for d in teams_dict
    ]

    results_table = tabulate(
        team_tuples,
        headers=[
            "Conference",
            "Team",
            "Avg. Wins",
            "Points",
            "PF%",
            "WC%"
        ],
        tablefmt="rst",
        numalign="left",
    )
    return results_table


# Print your results:

if __name__ == "__main__":

    import sys
    season_year = int(sys.argv[1]) # year in which season ends
    start_datetime = datetime(season_year-1, 9, 1)  # start of season Sep, except 12-2013 in Jan
    #end_datetime = datetime(season_year,4,30)  # a few weeks or months in
    end_datetime = datetime(season_year-1,12,1)

    ratings_mode = "SRS"
    results = playoff_odds_calc(
        start_datetime, end_datetime, season_year, ratings_mode=ratings_mode
    )
    results_table = playoff_odds_print(results,season_year)

    print(
        "Playoff odds for the "
        + str(season_year)
        + " season as of "
        + end_datetime.strftime("%b %d %Y")
    )
    print("Method used: " + ratings_mode)
    print(results_table)
    print(
        "Notes Pending. Note that an editorial decision also has yet to be made on whether this tool will use 2020/2021 seasons\n" +
        "While valid for the purposes of determining Elo ratings, the playoff format for 2020 was for obvious reasons changed mid-season"
    )


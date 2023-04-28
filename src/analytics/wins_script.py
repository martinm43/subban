# coding: utf-8
from pprint import pprint
def get_wins(team_id, season_year, start_datetime, end_datetime):
    """
    
    Return wins from a given season for a given team.

    Parameters
    ----------
    team_id : team id (1=ATL,30=WAS)
    season_year : season ending in year X
    start_datetime : UNIX timestamp of start of query
    end_datetime : UNIX timestamp of end of query

    Returns
    -------
    dict: visitor_wins of team, home_wins of team, and overall record.

    """
    from nhl_database.nhl_data_models import Games
    from nhl_database.queries import epochtime

    visitor_query = Games.select().where(
        Games.season_year == season_year,
        Games.visitor_team_id == team_id,
        ((Games.visitor_g > 0)|(Games.home_g > 0)),
        Games.game_datetime >= epochtime(start_datetime),
        Games.game_datetime <= epochtime(end_datetime),
    )

    visitor_results = [[i.visitor_g, i.home_g, i.game_decided_by] for i in visitor_query]

    visitor_wins_total = sum([1 if x[0] > x[1] else 0 for x in visitor_results])
    visitor_T_total = sum([1 if x[2] != "Regulation" and x[0] < x[1] else 0 for x in visitor_results])
    visitor_L_total = sum([1 if x[2] == "Regulation" and x[0] < x[1] else 0 for x in visitor_results])

    visitor_games_total = len(visitor_results)
    # home_query = Games.select().where(Games.season_year == season_year, Games.home_team_id == team_id, Games.home_g > 0)
    home_query = Games.select().where(
        Games.season_year == season_year,
        Games.home_team_id == team_id,
        ((Games.visitor_g > 0)|(Games.home_g > 0)),
        Games.game_datetime >= epochtime(start_datetime),
        Games.game_datetime <= epochtime(end_datetime),
    )
    home_results = [[i.home_g, i.visitor_g,i.game_decided_by] for i in home_query]
    home_wins_total = sum([1 if x[0] > x[1] else 0 for x in home_results])
    home_T_total = sum([1 if x[2] != "Regulation" and x[0] < x[1]  else 0 for x in home_results])
    home_L_total = sum([1 if x[2] == "Regulation" and x[0] < x[1] else 0 for x in home_results])

    home_games_total = len(home_results)

    visitor_record = str(visitor_wins_total) + "-" + str(visitor_L_total) + "-" + str(visitor_T_total)
    home_record = str(home_wins_total) + "-" + str(home_L_total) + "-" + str(home_T_total)

    record = (
        str(visitor_wins_total + home_wins_total)
        + "-"
        + str(visitor_L_total + home_L_total)
        + "-" 
        + str(home_T_total+visitor_T_total)
    )
    pts =  2*(visitor_wins_total+home_wins_total)+1*(visitor_T_total+home_T_total)
    try:
        pts_pct = pts/(2*(home_games_total+visitor_games_total))
    except ZeroDivisionError:
        print("WARNING: Team "+str(team_id)+" played no games this season ending "+str(season_year)+" - please investigate whether this is expected behaviour")
        pts_pct = 0.0
        pass
    return {"visitor_record": visitor_record, "home_record": home_record, "record": record,"points":pts,"pts_pct":pts_pct}

def points_list(season_year, start_datetime, end_datetime):
    wins_dict_list = [
    get_wins(i, season_year, start_datetime, end_datetime) for i in range(1, 33)]
    points_list = [x["points"] for x in wins_dict_list]
    return points_list

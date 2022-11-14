# coding: utf-8
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
    from nhl_database.queries import team_abbreviation, epochtime

    visitor_query = Games.select().where(
        Games.season_year == season_year,
        Games.visitor_team_id == team_id,
        ((Games.visitor_g > 0)|(Games.home_g > 0)),
        Games.game_datetime >= epochtime(start_datetime),
        Games.game_datetime <= epochtime(end_datetime),
    )
    visitor_results = [[i.visitor_g, i.home_g] for i in visitor_query]
    visitor_wins_total = sum([1 if x[0] > x[1] else 0 for x in visitor_results])
    visitor_games_total = len(visitor_results)
    # home_query = Games.select().where(Games.season_year == season_year, Games.home_team_id == team_id, Games.home_g > 0)
    home_query = Games.select().where(
        Games.season_year == season_year,
        Games.home_team_id == team_id,
        ((Games.visitor_g > 0)|(Games.home_g > 0)),
        Games.game_datetime >= epochtime(start_datetime),
        Games.game_datetime <= epochtime(end_datetime),
    )
    home_results = [[i.home_g, i.visitor_g] for i in home_query]
    home_wins_total = sum([1 if x[0] > x[1] else 0 for x in home_results])
    home_games_total = len(home_results)

    visitor_record = str(visitor_wins_total) + "-" + str(visitor_games_total - visitor_wins_total)
    home_record = str(home_wins_total) + "-" + str(home_games_total - home_wins_total)
    record = (
        str(visitor_wins_total + home_wins_total)
        + "-"
        + str(visitor_games_total + home_games_total - visitor_wins_total - home_wins_total)
    )

    return {"visitor_record": visitor_record, "home_record": home_record, "record": record}

"""
ORM class objects for the tables within the nba_data.sqlite database.

"""
# from peewee import *
from peewee import TextField, FloatField, IntegerField, SqliteDatabase, Model

database = SqliteDatabase("nhl_data.sqlite", **{})


class UnknownField(object):
    def __init__(self, *_, **__):
        pass


class BaseModel(Model):
    class Meta:
        database = database


class Games(BaseModel):
    """ORM object for the BballrefScores table"""

    notes = TextField(db_column="Notes", null=True)
    game_decided_by = TextField(null=True)
    visitor_g = IntegerField(null=True)
    visitor = TextField(null=True)
    visitor_team_id = IntegerField(null=True)
    game_date = TextField(null=True)
    game_datetime = IntegerField(null=True)
    home_g = IntegerField(null=True)
    home = TextField(null=True)
    home_team_id = IntegerField(null=True)
    season_year = IntegerField(null=True)
    log = TextField(null=True)
    attendance = IntegerField(null=True)

    class Meta:
        db_table = "games"


class ProApiTeams(BaseModel):
    """ORM object for the ProApiTeams table"""

    abbreviation = TextField(null=True)
    bball_ref = IntegerField(db_column="bball_ref_id", null=True)  #
    city = TextField(null=True)
    conf_or_league = TextField(null=True)
    team = IntegerField(db_column="team_id", null=True)
    team_name = TextField(null=True)
    division = TextField(null=True)
    full_team_name = TextField(null=True)
    current_abbreviation = TextField(null=True)

    class Meta:
        db_table = "pro_api_teams"


class ProlineData(BaseModel):
    """ORM object for the historic ProLine Data table"""

    away_1st = IntegerField(null=True)
    away_2nd = IntegerField(null=True)
    away_3rd = IntegerField(null=True)
    away_4th = IntegerField(null=True)
    away_ot_pts = IntegerField(db_column="away_OT_pts", null=True)
    away_pts = IntegerField(null=True)
    away_team = TextField(null=True)
    away_team_id = IntegerField(null=True)
    away_v_money_line = FloatField(null=True)
    away_v_ou = FloatField(null=True)
    away_v_pts_money = FloatField(null=True)
    away_v_pts_sprd = FloatField(null=True)
    date = TextField(null=True)
    home_1st = IntegerField(null=True)
    home_2nd = IntegerField(null=True)
    home_3rd = IntegerField(null=True)
    home_4th = IntegerField(null=True)
    home_ot_pts = IntegerField(db_column="home_OT_pts", null=True)
    home_pts = IntegerField(null=True)
    home_team = TextField(null=True)
    home_team_id = IntegerField(null=True)
    home_v_money_line = FloatField(null=True)
    home_v_ou = FloatField(null=True)
    home_v_pts_money = FloatField(null=True)
    home_v_pts_sprd = FloatField(null=True)
    home_v_total = FloatField(null=True)
    season = IntegerField(null=True)
    time_of_day = TextField(null=True)
    unix_date = FloatField(null=True)

    class Meta:
        db_table = "proline_data"


class NbaTeamEloData(BaseModel):
    """ORM object for the 'NBATeamEloData' Table"""

    season_year = IntegerField(null=True)  #
    team_abbreviation = TextField(null=True)
    datetime = FloatField(null=True)
    elo_rating = FloatField(null=True)
    team_id = IntegerField(null=True)

    class Meta:
        db_table = "nba_team_elo_data"


"""
Quick set of pytest tests to 
"""
import pytest
from info_table import info_table_data
from datetime import datetime

#Test setup values
season_year = 2023
start_datetime = datetime(2022,10,1)
end_datetime = datetime(2023,4,15)
team_index = 31
ovr_loc = 6



@pytest.fixture
def itd():
    return info_table_data
    


def test_team_tuple(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    tm_abbrev = tm_tuple[team_index][0]
    assert(tm_abbrev=="WPG")

def test_wins(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    tm_abbrev = tm_tuple[team_index][ovr_loc]
    print(tm_tuple[team_index])
    assert(tm_abbrev[0:2]=="46")

def test_losses(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    tm_abbrev = tm_tuple[team_index][ovr_loc]
    print(tm_tuple[team_index])
    assert(tm_abbrev[3:5]=="33") 
    
def test_OTL_losses(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    tm_abbrev = tm_tuple[team_index][ovr_loc]
    print(tm_tuple[team_index])
    assert(tm_abbrev[6:8]=="3") 


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
team_index = 15
ovr_loc = 6


@pytest.fixture
def itd():
    return info_table_data
    

#TO-DO: use fixtures

def test_team_tuple(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    tm_abbrev = tm_tuple[team_index][0]
    assert(tm_abbrev=="MTL")

def test_wins(itd):
    itd = info_table_data(season_year,start_datetime,end_datetime)
    tm_tuple = itd[ovr_loc][6] #overall record
    print(tm_tuple)
    tm_abbrev = tm_tuple[0:1]
    assert(tm_abbrev=="30")

"""def test_losses():
    itd = info_table_data(season_year,start_datetime,end_datetime)
    tm_tuple = itd[ovr_loc][6] #overall record
    tm_abbrev = tm_tuple[3:4]
    assert(tm_abbrev=="42")

def test_OTL_losses():
    itd = info_table_data(season_year,start_datetime,end_datetime)
    tm_tuple = itd[ovr_loc][6] #overall record
    tm_abbrev = tm_tuple[6:7]
    assert(tm_abbrev=="3")  """


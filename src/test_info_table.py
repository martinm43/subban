
"""
Quick set of pytest tests to 
"""
import pytest
from info_table import info_table_data
from datetime import datetime


#WARNING: as of now only works for alphabetically sorted order!!

#variables
season_year = 2023
start_datetime = datetime(season_year-1,10,1)
end_datetime = datetime(season_year,4,20)
team_index = 15
ovr_loc = 6



@pytest.fixture
def itd():
    return info_table_data
    
def test_dimensions(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    assert(len(tm_tuple)==32) #length is 32
    assert(len(tm_tuple[team_index])==10) #width is 10

def test_team_tuple(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    tm_abbrev = tm_tuple[team_index][0]
    assert(tm_abbrev=="MTL")

def test_wins(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    tm_abbrev = tm_tuple[team_index][ovr_loc]
    assert(tm_abbrev[0:2]=="31")

def test_losses(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    tm_abbrev = tm_tuple[team_index][ovr_loc]
    assert(tm_abbrev[3:5]=="45") 
    
def test_OTL_losses(itd):
    tm_fn = itd
    tm_tuple = tm_fn(season_year,start_datetime,end_datetime)
    tm_abbrev = tm_tuple[team_index][ovr_loc]
    assert(tm_abbrev[6:8]=="6") 

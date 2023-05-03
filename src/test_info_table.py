
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

itf = info_table_data(season_year,start_datetime,end_datetime)[0:3]


@pytest.mark.parametrize('itd', info_table_data(season_year,start_datetime,end_datetime)[0:3])   
def test_dimensioned(itd):
    tm_tuple = itd
    assert(len(tm_tuple)==10) #each entry has 10 items

def test_team_tuple(itf):
    tm_tuple = itf
    tm_abbrev = tm_tuple[team_index][0]
    assert(tm_abbrev=="MTL")

def test_wins(itf):
    tm_tuple = itf
    tm_abbrev = tm_tuple[team_index][ovr_loc]
    assert(tm_abbrev[0:2]=="31")

def test_losses(itf):
    tm_tuple = itf
    tm_abbrev = tm_tuple[team_index][ovr_loc]
    assert(tm_abbrev[3:5]=="45") 

@pytest.mark.skip 
def test_OTL_losses(itf):
    tm_tuple = itf
    tm_abbrev = tm_tuple[team_index][ovr_loc]
    assert(tm_abbrev[6:8]=="6") 


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

@pytest.fixture
def itd():
    return info_table_data(season_year,start_datetime,end_datetime)

class BasicRecordsCheck:
    def test_team_tuple():
        tm_tuple = itd[team_index]
        tm_abbrev = tm_tuple[0]
        assert(tm_abbrev=="MTL")

    def test_wins():
        tm_tuple = itd[team_index]
        tm_abbrev = tm_tuple[6]
        assert(tm_abbrev=="MTL")

    def test_losses():
        tm_tuple = itd[team_index]
        tm_abbrev = tm_tuple[6]
        assert(tm_abbrev=="MTL")

    def test_OTL_losses():
        #itd = info_table_data(season_year,start_datetime,end_datetime)
        tm_tuple = itd[team_index]
        tm_abbrev = tm_tuple[6]
        assert(tm_abbrev=="MTL")


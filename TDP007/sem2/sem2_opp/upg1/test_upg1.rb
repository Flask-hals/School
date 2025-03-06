require './upg1del1.rb'
require './upg1del2.rb'

require 'test/unit'


class Test_Football < Test::Unit::TestCase
    

    def setup
        football_data = read_file("football.txt")
        @teams = parse_teams(football_data)
    end

    def test_initial_team_list
        expected = [
        {:goal_diff=>43, :team=>"Arsenal"},
        {:goal_diff=>37, :team=>"Liverpool"},
        {:goal_diff=>42, :team=>"Manchester_U"},
        {:goal_diff=>22, :team=>"Newcastle"},
        {:goal_diff=>16, :team=>"Leeds"},
        {:goal_diff=>28, :team=>"Chelsea"},
        {:goal_diff=>9, :team=>"West_Ham"},
        {:goal_diff=>1, :team=>"Aston_Villa"},
        {:goal_diff=>4, :team=>"Tottenham"},
        {:goal_diff=>4, :team=>"Blackburn"},
        {:goal_diff=>8, :team=>"Southampton"},
        {:goal_diff=>12, :team=>"Middlesbrough"},
        {:goal_diff=>8, :team=>"Fulham"},
        {:goal_diff=>11, :team=>"Charlton"},
        {:goal_diff=>12, :team=>"Everton"},
        {:goal_diff=>18, :team=>"Bolton"},
        {:goal_diff=>22, :team=>"Sunderland"},
        {:goal_diff=>23, :team=>"Ipswich"},
        {:goal_diff=>30, :team=>"Derby"},
        {:goal_diff=>34, :team=>"Leicester"}]

        
        assert_equal(expected, @teams)
    end

    def test_sorted_team_list
        sorted_teams = sort_teams(@teams) 
        expected = [
        {:goal_diff=>1, :team=>"Aston_Villa"},
        {:goal_diff=>4, :team=>"Tottenham"},
        {:goal_diff=>4, :team=>"Blackburn"},
        {:goal_diff=>8, :team=>"Southampton"},
        {:goal_diff=>8, :team=>"Fulham"},
        {:goal_diff=>9, :team=>"West_Ham"},
        {:goal_diff=>11, :team=>"Charlton"},
        {:goal_diff=>12, :team=>"Middlesbrough"},
        {:goal_diff=>12, :team=>"Everton"},
        {:goal_diff=>16, :team=>"Leeds"},
        {:goal_diff=>18, :team=>"Bolton"},
        {:goal_diff=>22, :team=>"Newcastle"},
        {:goal_diff=>22, :team=>"Sunderland"},
        {:goal_diff=>23, :team=>"Ipswich"},
        {:goal_diff=>28, :team=>"Chelsea"},
        {:goal_diff=>30, :team=>"Derby"},
        {:goal_diff=>34, :team=>"Leicester"},
        {:goal_diff=>37, :team=>"Liverpool"},
        {:goal_diff=>42, :team=>"Manchester_U"},
        {:goal_diff=>43, :team=>"Arsenal"}]
        assert_equal(expected, sorted_teams)
    end

    def test_team_with_smallest_goal_diff
        min_team = min_goal_diff(@teams) 
        assert_equal({ team: "Aston_Villa", goal_diff: 1 }, min_team)
    end
end


class Test_Weather < Test::Unit::TestCase

    

    def setup
        weather_data = read_file("weather.txt")
        @weather_data = parse_weather(weather_data)
    end

    def test_parse_weather
        expected = [
        {:day=>1, :temp_diff=>29},
        {:day=>2, :temp_diff=>16},
        {:day=>3, :temp_diff=>22},
        {:day=>4, :temp_diff=>18},
        {:day=>5, :temp_diff=>24},
        {:day=>6, :temp_diff=>20},
        {:day=>7, :temp_diff=>16},
        {:day=>8, :temp_diff=>21},
        {:day=>9, :temp_diff=>54},
        {:day=>10, :temp_diff=>20},
        {:day=>11, :temp_diff=>32},
        {:day=>12, :temp_diff=>15},
        {:day=>13, :temp_diff=>11},
        {:day=>14, :temp_diff=>2},
        {:day=>15, :temp_diff=>9},
        {:day=>16, :temp_diff=>20},
        {:day=>17, :temp_diff=>24},
        {:day=>18, :temp_diff=>30},
        {:day=>19, :temp_diff=>20},
        {:day=>20, :temp_diff=>27},
        {:day=>21, :temp_diff=>27},
        {:day=>22, :temp_diff=>26},
        {:day=>23, :temp_diff=>22},
        {:day=>24, :temp_diff=>13},
        {:day=>25, :temp_diff=>18},
        {:day=>26, :temp_diff=>33},
        {:day=>27, :temp_diff=>19},
        {:day=>28, :temp_diff=>16},
        {:day=>29, :temp_diff=>22},
        {:day=>30, :temp_diff=>45}]
        assert_equal(expected, @weather_data)
    end

    def test_sorted_team_list
        expected = [
        {:day=>14, :temp_diff=>2},
        {:day=>15, :temp_diff=>9},
        {:day=>13, :temp_diff=>11},
        {:day=>24, :temp_diff=>13},
        {:day=>12, :temp_diff=>15},
        {:day=>2, :temp_diff=>16},
        {:day=>7, :temp_diff=>16},
        {:day=>28, :temp_diff=>16},
        {:day=>4, :temp_diff=>18},
        {:day=>25, :temp_diff=>18},
        {:day=>27, :temp_diff=>19},
        {:day=>6, :temp_diff=>20},
        {:day=>10, :temp_diff=>20},
        {:day=>16, :temp_diff=>20},
        {:day=>19, :temp_diff=>20},
        {:day=>8, :temp_diff=>21},
        {:day=>3, :temp_diff=>22},
        {:day=>23, :temp_diff=>22},
        {:day=>29, :temp_diff=>22},
        {:day=>5, :temp_diff=>24},
        {:day=>17, :temp_diff=>24},
        {:day=>22, :temp_diff=>26},
        {:day=>20, :temp_diff=>27},
        {:day=>21, :temp_diff=>27},
        {:day=>1, :temp_diff=>29},
        {:day=>18, :temp_diff=>30},
        {:day=>11, :temp_diff=>32},
        {:day=>26, :temp_diff=>33},
        {:day=>30, :temp_diff=>45},
        {:day=>9, :temp_diff=>54}]
        assert_equal(expected, sort_weathers(@weather_data))
    end

    def test_team_with_smallest_goal_diff
        min_temp_day = min_temp_diff(@weather_data) 
        assert_equal({ day: 14, temp_diff: 2 }, min_temp_day)
    end
end
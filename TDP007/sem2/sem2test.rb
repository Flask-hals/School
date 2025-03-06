#!/bin/env ruby

require './sem2.rb'
require 'test/unit'

class TestFirst < Test::Unit::TestCase
    def test_football
        file = File.read("football.txt")
        result = diff(file, true)
        counter = 0
        for x in result
            if x == result.last
                break
            else
                counter += 1
            assert_false(x[1] > result[counter][1])
            end
        end

        assert_equal([["Team2", 0], ["Team3", 1], ["Team1", 5]], diff("1. Team1 123 123 123 123 5  -  0  123 123
                                                                            2. Team2 123 123 123 123 2  -  2  123 123
                                                                            3. Team3 123 123 123 123 2  -  3  123 123", true))

    end

    def test_weather
        file = File.read("weather.txt")
        result = diff(file, false)
        counter = 0
        for x in result
            if x == result.last
                break
            else
                counter += 1
            assert_false(x[1] > result[counter][1])
            end
        end

        assert_equal([["2", 0],["3", 3],["1", 99]], diff(" 1 100 1 74 53.8 0.00 F 280 9.6 270  17  1.6  93 23 1004.5
                                2  1 1 74 53.8 0.00 F 280  9.6 270  17  1.6  93 23 1004.5
                                3  5 2 74 53.8 0.00 F 280  9.6 270  17  1.6  93 23 1004.5", false))

    end
end


class TestSecond < Test::Unit::TestCase
    def test_lst
        lst = MyListener.new
        file = URI.open("https://www.ida.liu.se/~TDP007/current/material/seminarie2/events.html") {|f| f.read}
        REXML::Document.parse_stream(file,lst)
        # Testar den givna filen
        assert_equal(8, lst.get_list.length)
        
        lst = MyListener.new
        file = File.open("test.html") {|f| f.read}
        REXML::Document.parse_stream(file,lst)
        
        # Testar test.html vilket följer strukturen av den givna filen med några uttänkta fel
        # som inte borde fångas upp av parsern.
        assert_equal(3, lst.get_list.length)
        arr = lst.get_list

        for elem in arr
            assert_equal("Summary", elem.get_summary)
            assert_equal("Date", elem.get_start)
            assert_equal("User", elem.get_user)
            assert_equal("Description", elem.get_description)
            assert_equal("Locality", elem.get_location)
            assert_equal("Region", elem.get_region)
            assert_equal("Street", elem.get_address)
        end        
    end

end

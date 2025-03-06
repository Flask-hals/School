require 'test/unit'
require 'rexml/document'
require './upg2.rb'  

class Test_Events < Test::Unit::TestCase

    

    def setup
        @events = find_event("events.html")
    end

    def test_parse_events
        
        assert_equal "The Dark Carnival - 101.9FM", @events.first[:summary]
        assert_equal "\"The Dark Carnival is two hours of spooky goodness. Every week, expect the best goth, industrial, and other dark music, as well as news and reviews from the wider world of goth culture. Embrace the darkness! Fridays, from 10 PM until the Witching Hour.\"", @events.first[:description]
        assert_equal "2008-01-04 10:00pm EST", @events.first[:dtstart]
    end

    def test_data


        expected_events = [
        {:description=>"\"The Dark Carnival is two hours of spooky goodness. Every week, expect the best goth, industrial, and other dark music, as well as news and reviews from the wider world of goth culture. Embrace the darkness! Fridays, from 10 PM until the Witching Hour.\"",
       :dtstart=>"2008-01-04 10:00pm EST",
       :summary=>"The Dark Carnival - 101.9FM"},
      {:description=>"Gothic, Industrial, Dark Alternative w/ DJ LunaSlave",
       :dtstart=>"2008-01-06",
       :summary=>"Sinister Sundays"},
      {:description=>
        "\"The Dark Carnival is two hours of spooky goodness. Every week, expect the best goth, industrial, and other dark music, as well as news and reviews from the wider world of goth culture. Embrace the darkness! Fridays, from 10 PM until the Witching Hour.\"",
       :dtstart=>"2008-01-11 10:00pm EST",
       :summary=>"The Dark Carnival - 101.9FM"},
      {:description=>"Gothic, Industrial, Dark Alternative w/ DJ LunaSlave",
       :dtstart=>"2008-01-13",
       :summary=>"Sinister Sundays"},
      {:description=>
        "\"The Dark Carnival is two hours of spooky goodness. Every week, expect the best goth, industrial, and other dark music, as well as news and reviews from the wider world of goth culture. Embrace the darkness! Fridays, from 10 PM until the Witching Hour.\"",
       :dtstart=>"2008-01-18 10:00pm EST",
       :summary=>"The Dark Carnival - 101.9FM"},
      {:description=>"Gothic, Industrial, Dark Alternative w/ DJ LunaSlave",
       :dtstart=>"2008-01-20",
       :summary=>"Sinister Sundays"},
      {:description=>
        "\"The Dark Carnival is two hours of spooky goodness. Every week, expect the best goth, industrial, and other dark music, as well as news and reviews from the wider world of goth culture. Embrace the darkness! Fridays, from 10 PM until the Witching Hour.\"",
       :dtstart=>"2008-01-25 10:00pm EST",
       :summary=>"The Dark Carnival - 101.9FM"},
      {:description=>"Gothic, Industrial, Dark Alternative w/ DJ LunaSlave",
       :dtstart=>"2008-01-27",
       :summary=>"Sinister Sundays"}]

        assert_equal(expected_events, @events)
    end
end

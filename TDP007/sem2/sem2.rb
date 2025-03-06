# Uppgift 1

#true_or_false = true för football, false för weather
def diff(file, true_or_false)
    if true_or_false
      arr = file.scan(/\d+[.] (\w+).*\s(\d+  -  \d+)/)
    else
      arr = file.scan(/^\W+(\d+)\W+(\d+)\W+(\d+)/)
    end
    res = Hash.new
    for x in arr
      if true_or_false 
        tmp = x[1].split('  -  ')
        res[x[0]] = (tmp[0].to_i - tmp[1].to_i).abs
      else
        res[x[0]] = x[1].to_i - x[2].to_i
      end
    end
    return res.sort_by(&:last)
end

res = diff("football.txt", true)

#Uppgift 2

require 'open-uri.rb'
require 'rexml/streamlistener'
require 'rexml/document'

file = URI.open("https://www.ida.liu.se/~TDP007/current/material/seminarie2/events.html") {|f| f.read}

class Event
  def initialize
    @summary = ""
    @description = ""
    @start = ""
    @location = ""
    @address = ""
    @region = ""
    @user = ""
  end

  def set_description(text)
    @description = text
  end

  def get_description
    return @description
  end

  def set_summary(text)
    @summary = text
  end

  def get_summary
    return @summary
  end

  def set_start(text)
    @start = text
  end

  def get_start
    return @start
  end

  def set_location(text)
    @location = text
  end

  def get_location
    return @location
  end

  def set_address(text)
    @address = text
  end

  def get_address
    return @address
  end

  def set_user(text)
    @user = text
  end

  def get_user
    return @user
  end

  def set_region(text)
    @region = text
  end

  def get_region
    return @region
  end
end

class MyListener
  include REXML::StreamListener
  def initialize
    @search = false # bool checked by text-listener for deciding if it should act or not
    @open = false # Opens when a div tag contains class="vevent", used to check if we should read tags
    @searchDesc = false
    @currentEvent # Event that is to be created
    @events = Array.new # Array of all events created during parsing
    @name # Name of the tag class
    @steps = 0
  end

  
  def tag_start(name, attrs)
    if name == "div" && attrs["class"] == "vevent"
      @currentEvent = Event.new
      @open = true
    elsif @open && name == "td" && attrs["class"] == "description"
      @searchDesc = true
    elsif @open && @searchDesc && name == "p"
      @search = true
      @name = "description"
    elsif @open && (name == "span" && (attrs["class"] == "summary" || attrs["class"] == "dtstart" || 
          attrs["class"] == "locality" || attrs["class"] == "street-address" || 
          attrs["class"] == "region"))
        @search = true
        @name = attrs["class"]
    elsif @open && (name == "a" && attrs["class"] == "userLink ")
      @search = true
      @name = attrs["class"]
    elsif @open && name == "div"
      @steps += 1
    end
  end

  def tag_end(name)
    if name == "div" && @open && @steps == 0
      @events.insert(0, @currentEvent)
      @open = false
    elsif name == "div" && @steps != 0
      @steps -= 1
    end
    
  end

  def text(text)
    if @search && @open
      if @name == "description" && @searchDesc 
        @currentEvent.set_description(text)
        @searchDesc = false
      else
        case @name
        when "summary"
          @currentEvent.set_summary(text)
        when "dtstart"
          @currentEvent.set_start(text)
        when "locality"
          @currentEvent.set_location(text)
        when "street-address"
          @currentEvent.set_address(text)
        when "region"
          @currentEvent.set_region(text)
        when "userLink "
          @currentEvent.set_user(text)
        end
        @search = false
      end
    end
  end

  def print()
    for element in @events
      puts "Summary: " + element.get_summary
      puts "Description: " + element.get_description
      puts "Start: " + element.get_start
      puts "Location: " + element.get_location + ", " + element.get_region
      puts "Street-address: " + element.get_address
      puts "Posted by: " + element.get_user
      puts ""
    end
  end

  def get_list
    return @events
  end
end

# lst = MyListener.new
# #src = File.new(file)
# REXML::Document.parse_stream(file,lst)

# lst.print
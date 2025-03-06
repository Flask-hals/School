require 'rexml/document'

def find_event(filename)


    src = File.open(filename)
    doc = REXML::Document.new(src)
    
    events = []

    doc.elements.each("//div[@class = 'vevent']/") do |event|


        summary = event.elements[".//span[@class = 'summary']"].text
        description = event.elements[".//td[@class = 'description']//p"].text
        dtstart = event.elements[".//span[@class = 'dtstart']"].text
        


        events << {summary: summary, description: description, dtstart: dtstart}
    end

    return events

end

def print_events(events)

    events.each_with_index do |event, index|

        puts " "
        puts "#{event[:summary]}"
        #puts " "
        puts "#{event[:description]}"
        puts "#{event[:dtstart]}"


    end


end


events = find_event("events.html")
print_events(events)








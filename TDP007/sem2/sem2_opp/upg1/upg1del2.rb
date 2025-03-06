def read_file(filename)
    File.read(filename)
end


def parse_weather(data)

    data.each_line.map do |line|


        match_data = line.match(/^\s*(\d+)\s+(\d+\*?)\s+(\d+\*?)/)
        next unless match_data

        {day: match_data[1].to_i, temp_diff: (match_data[2].delete("*").to_i - match_data[3].delete("*").to_i).abs}
  
    end.compact

end


def min_temp_diff(weathers) 

    weathers.min_by { |weather| weather[:temp_diff]}

end

def sort_weathers(weathers)

    weathers.sort_by { |weather| weather[:temp_diff]}

end


def print_result(min_temp, sorted_weather)

    puts "Mins skillnad i temp: #{min_temp[:day]} med #{min_temp[:temp_diff]} temp skillnad"

    puts "\nLista efter tempskillnad: " 
    sorted_weather.each_with_index do |temp, index|

        puts "#{index + 1}. #{temp[:day]} - #{temp[:temp_diff]} temp"

    end

end

weather_data = read_file("weather.txt")
weather = parse_weather(weather_data)
min_diff_weather = min_temp_diff(weather)
sorted_weather = sort_weathers(weather)

print_result(min_diff_weather, sorted_weather)
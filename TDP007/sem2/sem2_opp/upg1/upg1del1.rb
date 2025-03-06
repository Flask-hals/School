def read_file(filename)
    File.read(filename)
end


def parse_teams(data)

    data.each_line.map do |line|


        match_data = line.match(/^\s*\d+.\s*([\w]+)\s*\d+\s*\d+\s*\d+\s*\d+\s*(\d+)\s*-\s*(\d+)/)
        next unless match_data

        {team: match_data[1], goal_diff: (match_data[2].to_i - match_data[3].to_i).abs}
  
    end.compact

end


def min_goal_diff(teams) 

    teams.min_by { |team| team[:goal_diff]}

end

def sort_teams(teams)

    teams.sort_by { |team| team[:goal_diff]}

end


def print_result(min_team, sorted_teams)

    puts "Mins skillnad i antal mål: #{min_team[:team]} med #{min_team[:goal_diff]} mål"

    puts "\nLista efter målskillnad: " 
    sorted_teams.each_with_index do |team, index|

        puts "#{index + 1}. #{team[:team]} - #{team[:goal_diff]} målskillnad"

    end

end

football_data = read_file("football.txt")
teams = parse_teams(football_data)
min_diff_team = min_goal_diff(teams)
sorted_teams = sort_teams(teams)

print_result(min_diff_team, sorted_teams)

# teams = []
# football_data.each_line do |line|
#   match_data = line.match(/^\s*\d+.\s*([\w]+)\s*\d+\s*\d+\s*\d+\s*\d+\s*(\d+)\s*-\s*(\d+)/)
#   next unless match_data
  
#   team = match_data[1]
#   f = match_data[2].to_i
#   a = match_data[3].to_i
#   goal_diff = (f - a).abs

#   teams << { team: team, goal_diff: goal_diff }
# end


# min_difference_team = teams.min_by { |team| team[:goal_diff] }


# sorted_teams = teams.sort_by { |team| team[:goal_diff] }


# puts "Lag med minst skillnad i mål: #{min_difference_team[:team]} (#{min_difference_team[:goal_diff]} mål)"
# puts "\nRangordning av lag efter målskillnad:"
# sorted_teams.each_with_index do |team, index|
#   puts "#{index + 1}. #{team[:team]} - #{team[:goal_diff]} målskillnad"
# end
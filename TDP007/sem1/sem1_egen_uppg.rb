#!/bin/env ruby

=begin
Skapa ett program som tar in ett filnamn som kommandoordsargument och antingen räknar
upp antalet unika ord och visar resultatet i terminalen, eller byter ut ett ord med ett annat (inte case-sensitive).

Utöver filnamnet ska programmet ta in argumentet "count" för uppräkningen, och
argumentet "replace" samt det ord som ska bytas ut med ett annat enligt formatet <old>=<new> (exklusive pilarna).

Felhantering för icke-existerande fil, fel format eller fel antal ord vid argumentet "replace", samt vid inga argument alls ska finnas.

Syftet med denna uppgift är att gå igenom enklare fil- och texthantering samt terminalsargument i ruby.
Vidare tränar man på att skapa ett enklare program med felhantering.

Denna uppgift är enligt oss bra för syftet då det berör många olika koncept som:
fil- och texthantering, regex, inargument till ett program vid start samt felhantering.
Det är även likt tidigare uppgifter vi haft vilket borde göra det enkelt att komma igång med.

=end

# Lösningsförslag
input_array = ARGV

begin
    file_data = File.read(input_array[0])
rescue
    puts "Filename not found."
else
    if input_array[1] == "count"
        counter = Hash.new(0)
        new_array = file_data.split
        for x in new_array
            counter[x] += 1
        end
        puts counter

    elsif input_array[1] == "replace"
        if input_array.length == 3
            replacer = input_array[2].split('=') if input_array[2].include? ('=')
            if replacer == nil || replacer.length != 2 || replacer[0] == ""
                puts "Cant replace. Must give argument of format <to_be_replaced>=<replace_word> after replace."
            else
            new_string = file_data.gsub(/\b#{replacer[0]}\b/, replacer[1])
            puts new_string
            end
        else
            puts "To few arguments"
        end
    else
        puts "Need to give argument 'count' or 'replace'"
    end
end
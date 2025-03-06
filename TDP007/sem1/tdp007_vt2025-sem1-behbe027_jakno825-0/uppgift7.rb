require 'open-uri.rb'

# Skapa en funktion count, funktionen ska ta in två parametrar, första är en variabel med strängar 
# och andra är endast en sträng. Din funktion ska sedan skriva ut framkomsten av din enkla 
# sträng(andra parameter) i variabeln.
#
# >> require 'open-uri.rb'
# => true
# >> new_file = File.open("uppgift7.txt", "r")
# >> Text = File.read(new_file)
# => "Lorem ipsum dolor sit amet...."
# >> count(Text, "Lorem")
# => Lorem 1
#
# Givet till frågan:


new_file = File.open("uppgift7.txt", "r")
text = File.read(new_file)


def count(text, string)
    index = 0
    words = text.split
    for word in words
        if word == string
            index += 1
        end
    end
    if index > 0
        return "#{string} #{index}"
    else
        return "no match"
    end
end

# count(text, "Lorem") 
#! /bin/env ruby


# ----- Avsnitt 1 -----

# Uppg 1
def n_times(n)
    n.times {yield}
end

# n_times(3) { puts "Hello!" }

class Repeat
    def initialize(number)
        @number = number
    end

    def each
        @number.times {yield}
    end
end

# resultat = Repeat.new(3)
# resultat.each { puts "Hooray!" }

# Uppg 2
def find_it(arr)
    a = arr[0]
    for x in arr
        a = yield(a, x) ? a : x
    end
    return a
end

# find_it(["apelsin", "banan","citron"]) { |a,b| a.length < b.length }


# ----- Avsnitt 2 -----

# Uppg 3
class Integer
    def fib
        f1 = 1
        f2 = 1
        if self <= 0
            return 0
        end
        if self == 1 || self == 2
            return f1
        end
        
        counter = 2
        while counter < self
            f3 = f1 + f2
            f1 = f2
            f2 = f3
            counter += 1
        end
        return f2
    end
end

# puts 19.fib

# Uppgift 4
class Array
    def rotate_left(n)
        self.rotate(n)
    end
end

# restultat = [1, 2, 3].rotate_left(1)
# print restultat

# ----- Avsnitt 3 -----

# Uppg 5
require 'open-uri.rb'

html = URI.open("http://www.google.com") {|f| f.read}

def tag_names(file)
    matches = file.scan(/<([a-z]+)/)
    arr = Array.new
    for x in matches
            arr.push(x) if not arr.include? (x)
    end
    arr
end

#print tag_names(html)

#Uppg 6

#[A-Z]{3}\d{1,3}[A-Z]{1}
def regnr(reg)
    old_reg = reg.match(/(\b[A-Z]{3}\d{3}\b)/)
    if old_reg == nil
        new_reg = reg.match(/(\b[A-Z]{3}\d{2}[A-Z]{1}\b)/)
        if new_reg == nil
            return false
        end
        return new_reg[0]
    end
    return old_reg[0]
end

# puts regnr("Mitt reg är FMA358")
# puts regnr("FMA358")


# puts regnr("Mitt regnr. är FAM35B")

# puts regnr("ABCD2222")


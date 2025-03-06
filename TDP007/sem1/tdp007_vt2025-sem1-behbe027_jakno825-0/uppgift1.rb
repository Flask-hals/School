#!/bin/env ruby -w

def n_times(n, &block)
    1.upto(n) { || block.call()}  
    return n 
end

# n_times(3) { puts "Hello!"}


class Repeat
    def initialize(n)
        @n = n 
    end

    def each(&block)
        n_times(@n, &block)
    end
end

# do_three = Repeat.new(3)

# do_three.each { puts "Hooray!" }


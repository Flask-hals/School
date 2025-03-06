#!/bin/env ruby -w

class Integer
    def fib(n)
        n1 = 1
        n2 = 1
        if (n == 1 ) 
            return 1
        end
        n-=2
        for _ in 0...n
            total = n2+n1
            n1 = n2
            n2 = total
        end
        return total      
    end
end

# 0.fib(5)

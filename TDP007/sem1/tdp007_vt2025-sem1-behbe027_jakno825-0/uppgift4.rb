#!/bin/env ruby -w

class Array
    def rotate_left(n=1)
        return self.rotate(n)
    end
end
# p [1,2,3]
# p [1,2,3].rotate_left
# p [1,2,3].rotate_left(3)

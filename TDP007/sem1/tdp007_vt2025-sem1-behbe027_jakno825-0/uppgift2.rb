#!/bin/env ruby -w

def find_it(arr, &block)
    current = arr.first
    for element in arr
        if block.call(element, current)
            current = element
        end
    end
    return current
end






# find_it(["apelsin", "banan", "citron"]) { |a,b| a.length > b.length }
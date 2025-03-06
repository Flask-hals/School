#!/bin/env ruby -w

def tag_names(html)
    return html.scan(/[<]([a-zA-Z]{1,})[>]/).uniq
end
require 'open-uri.rb'
html = URI.open("http://www.google.com/") { |f| f.read }

# tag_names(html)

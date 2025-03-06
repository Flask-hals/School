#!/bin/env ruby -w
def regnr(text)
    if /[A-HJ-PR-UW-Z]{3}\d{3}/.match(text)
        reg = /[A-HJ-PR-UW-Z]{3}\d{3}/.match(text)
        return reg.to_s
    else
        return "false"
    end
end
# regnr("Min bil heter GGF297.")
# regnr("XQT784")

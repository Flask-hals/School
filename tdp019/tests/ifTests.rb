#!/usr/bin/env ruby

require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_if
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "ifTest.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)

        assert_equal(2, ctml["stmts"][5].arg.eval(ctml).val)
        assert_equal(10, ctml["stmts"][7].arg.eval(ctml).val)
    end
end
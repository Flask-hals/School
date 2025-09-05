#!/usr/bin/env ruby

require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_while
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "whileTest.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)

        assert_equal(11, ctml["stmts"][3].arg.eval(ctml).val)
        assert_equal(999, ctml["stmts"][4].arg.eval(ctml).val)
        assert_equal(1, ctml["stmts"][7].arg.eval(ctml).val)
    end
end
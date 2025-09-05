#!/usr/bin/env ruby

require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_class
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "classTest.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)

        ctml["stmts"][0].eval(ctml)
        ctml["stmts"][1].eval(ctml)
        ctml["stmts"][2].eval(ctml)
        ctml["stmts"][3].eval(ctml)
        assert_equal(100, ctml["stmts"][4].arg.eval(ctml).val)
        assert_equal(30, ctml["stmts"][5].arg.eval(ctml).val)
        assert_equal(130, ctml["stmts"][6].arg.eval(ctml).val)
    end
end
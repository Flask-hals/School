#!/usr/bin/env ruby

require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_func
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "funcTest.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)

        ctml["stmts"][0].eval(ctml)
        ctml["stmts"][1].eval(ctml)
        ctml["stmts"][2].eval(ctml)
        assert_equal(1, ctml["stmts"][3].arg.eval(ctml).val)
        ctml["stmts"][4].eval(ctml)
        ctml["stmts"][5].eval(ctml)
        assert_equal(2, ctml["stmts"][6].arg.eval(ctml).val)
        ctml["stmts"][7].eval(ctml)
        ctml["stmts"][8].eval(ctml)
        assert_equal(3, ctml["stmts"][9].arg.eval(ctml).val)
        ctml["stmts"][10].eval(ctml)
        ctml["stmts"][11].eval(ctml)
        assert_equal(4, ctml["stmts"][12].arg.eval(ctml).val)
    end
end
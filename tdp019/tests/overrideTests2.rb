#!/usr/bin/env ruby

require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_override2
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "overrideTest2.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)

        ctml["stmts"][0].eval(ctml)
        ctml["stmts"][1].eval(ctml)
        ctml["stmts"][2].eval(ctml)
        ctml["stmts"][3].eval(ctml)
        ctml["stmts"][4].eval(ctml)
        ctml["stmts"][5].eval(ctml)
        ctml["stmts"][6].eval(ctml)
        ctml["stmts"][7].eval(ctml)
        assert_equal(101, ctml["stmts"][8].arg.eval(ctml).val)
        assert_equal(201, ctml["stmts"][9].arg.eval(ctml).val)
        assert_equal(410, ctml["stmts"][10].arg.eval(ctml).val)
        assert_equal(151, ctml["stmts"][11].arg.eval(ctml).val)
    end
end
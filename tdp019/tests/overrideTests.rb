#!/usr/bin/env ruby

require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_override
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "overrideTest.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)

        ctml["stmts"][0].eval(ctml)
        ctml["stmts"][1].eval(ctml)
        ctml["stmts"][2].eval(ctml)
        ctml["stmts"][3].eval(ctml)
        ctml["stmts"][4].eval(ctml)
        ctml["stmts"][5].eval(ctml)
        ctml["stmts"][6].eval(ctml)
        ctml["stmts"][7].eval(ctml)
        assert_equal(111, ctml["stmts"][8].arg.eval(ctml).val)
        assert_equal(222, ctml["stmts"][9].arg.eval(ctml).val)
        assert_equal(333, ctml["stmts"][10].arg.eval(ctml).val)
        assert_equal(444, ctml["stmts"][11].arg.eval(ctml).val)
        assert_equal(999, ctml["stmts"][12].arg.eval(ctml).val)
        assert_equal(999, ctml["stmts"][13].arg.eval(ctml).val)
        assert_equal(999, ctml["stmts"][14].arg.eval(ctml).val)
        assert_equal(999, ctml["stmts"][15].arg.eval(ctml).val)
    end
end
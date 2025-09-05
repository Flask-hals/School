#!/usr/bin/env ruby

require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_llist
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "llistTest.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)

        ctml["stmts"][0].eval(ctml)
        assert_equal(1, ctml["stmts"][1].arg.eval(ctml).val)
        ctml["stmts"][2].eval(ctml)
        assert_equal(5, ctml["stmts"][3].arg.eval(ctml).val)
        ctml["stmts"][4].eval(ctml)
        assert_equal(1, ctml["stmts"][5].arg.eval(ctml).val)
        ctml["stmts"][6].eval(ctml)
        assert_equal(2, ctml["stmts"][7].arg.eval(ctml).val)
        assert_equal(1, ctml["stmts"][8].arg.eval(ctml).val)
    end
end
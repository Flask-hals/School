#!/usr/bin/env ruby

require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_rec
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "recursiveTest.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)

        ctml["stmts"][0].eval(ctml)
        ctml["stmts"][1].eval(ctml)
        assert_equal(3628800, ctml["stmts"][2].arg.eval(ctml).val)
        ctml["stmts"][3].eval(ctml)
        ctml["stmts"][4].eval(ctml)
        assert_equal(10, ctml["stmts"][5].arg.eval(ctml).val)
    end
end
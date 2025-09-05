#!/usr/bin/env ruby


require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_bool_diff
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "boolTest.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)
        
        assert_equal(1, ctml["stmts"][0].eval(ctml).val)
        assert_equal(0, ctml["stmts"][1].eval(ctml).val)
        assert_equal(1, ctml["stmts"][2].eval(ctml).val)
        assert_equal(0, ctml["stmts"][3].eval(ctml).val)
        assert_equal(1, ctml["stmts"][4].eval(ctml).val)
        assert_equal(1, ctml["stmts"][5].eval(ctml).val)
        assert_equal(0, ctml["stmts"][6].eval(ctml).val)
        assert_equal(0, ctml["stmts"][7].eval(ctml).val)
        assert_equal(0, ctml["stmts"][8].eval(ctml).val)
        assert_equal(1, ctml["stmts"][9].eval(ctml).val)
        assert_equal(1, ctml["stmts"][10].eval(ctml).val)
        assert_equal(0, ctml["stmts"][11].eval(ctml).val)
        assert_equal(1, ctml["stmts"][12].eval(ctml).val)
        assert_equal(0, ctml["stmts"][13].eval(ctml).val)

    end
end
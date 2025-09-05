#!/usr/bin/env ruby

# .out only for testing (printNode has no return value)


require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_print
        baseBath = File.dirname(__FILE__)
        filePath = File.join(baseBath, "testFiles", "printTest.ctml")
        ctml = Ctml.new.parser(true, nil, filePath)
        
        ctml["stmts"][0].eval(ctml)
        assert_equal(50.0, ctml["stmts"][1].arg.eval(ctml).val)
        assert_equal(100.0, ctml["stmts"][2].arg.eval(ctml).val)
        ctml["stmts"][3].eval(ctml)
        assert_equal(52, ctml["stmts"][4].arg.eval(ctml).val)
        assert_equal(2, ctml["stmts"][5].arg.eval(ctml).val)
        assert_equal(1, ctml["stmts"][6].arg.eval(ctml).val)
        ctml["stmts"][7].eval(ctml)
        assert_equal(20, ctml["stmts"][8].arg.eval(ctml).val)

        
        # assert_raise(Parser::ParseError) do
        #     ctml["stmts"][6].eval(ctml)
        # end
    end
end
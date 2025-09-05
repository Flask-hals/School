#!/usr/bin/env ruby


require 'test/unit'
require_relative '../parser.rb'

class TestFirst < Test::Unit::TestCase
    def test_addition
        ctml = Ctml.new
      
        assert_equal(7, ctml.parser(true, "<5 + 2/>"))
        assert_equal(5.1, ctml.parser(true, "<3.1 + 2/>"))
        assert_equal(5, ctml.parser(true, "<3.0 + 2.0/>"))
        assert_equal(300, ctml.parser(true, "<100 + 200/>"))
        assert_equal(-95, ctml.parser(true, "<-100 + 5/>"))
        assert_equal(5.1, ctml.parser(true, "<.1 + 5/>"))
        assert_equal(6.0, ctml.parser(true, "<1. + 5/>"))
    end
    
    def test_subtraction
      ctml = Ctml.new

      assert_equal(30, ctml.parser(true, "<35-5/>"))
      assert_equal(-4, ctml.parser(true, "<1-5/>"))
      assert_equal(0, ctml.parser(true, "<1-1/>"))
    end

    def test_multiplication
      ctml = Ctml.new
    
      assert_equal(10,ctml.parser(true, "<5 * 2/>"))
      assert_equal(6, ctml.parser(true, "<3 * 2/>"))
      assert_equal(200, ctml.parser(true, "<100 * 2/>"))
      assert_equal(400, ctml.parser(true, "<100 * 2 * 2/>"))
    end

    def test_division
      ctml = Ctml.new
    
      assert_equal(5, ctml.parser(true, "<10 / 2/>"))
      assert_equal(3, ctml.parser(true, "<9 / 3/>"))
      assert_equal(50, ctml.parser(true, "<100 / 2/>"))
      assert_equal(1, ctml.parser(true, "<10 / 5 / 2/>"))
    end

    def test_exponential
        ctml = Ctml.new
      
        assert_equal(25, ctml.parser(true, "<5 ^ 2/>"))
        assert_equal(1000000, ctml.parser(true, "<10 ^ 6/>"))
        assert_equal(1, ctml.parser(true, "<123 ^ 0/>"))
        assert_equal(256, ctml.parser(true, "<2 ^ 2 ^ 3/>"))
    end

    def test_mod
      ctml = Ctml.new
    
      assert_equal(0, ctml.parser(true, "<100 % 10/>"))
      assert_equal(1, ctml.parser(true, "<9 % 2/>"))
      assert_equal(2, ctml.parser(true, "<5 % 3/>"))  
      assert_equal(0, ctml.parser(true, "<5 % 3 % 2/>"))
      assert_equal(1, ctml.parser(true, "<10 % 7 % 2/>"))
  end
    
    def test_expressions
      ctml = Ctml.new
      
      assert_equal(30, ctml.parser(true, "<2 * (5 + 10)/>"))
      assert_equal(52, ctml.parser(true, "<2 + 5 * 10/>"))
      assert_equal(6, ctml.parser(true, "<2 * 6 / 2/>"))
      assert_equal(0, ctml.parser(true, "<2 - 10 / 5/>"))
      assert_equal(37, ctml.parser(true, "<1 + 5 + 50 - 25 + 2 * 3/>"))
      assert_equal(2, ctml.parser(true, "<5 + 2 + 5 - 10/>"))
      assert_equal(-16, ctml.parser(true, "<2 + 3 * 4 - 5 * 6/>"))
      assert_equal(2, ctml.parser(true, "<(2 ^ 2) ^ 2 ^ 2 % 1 * 2 / 4 + 2 - 2/>"))
      assert_equal(1, ctml.parser(true, "<0 + true/>"))
      assert_equal(0, ctml.parser(true, "<0 + false/>"))
      assert_equal(1, ctml.parser(true, "<true + false/>"))
    end
end
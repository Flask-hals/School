require './upg1.rb'
require './upg2.rb'
require 'test/unit'

class TestFirst < Test::Unit::TestCase
  def test_upg1
    p0 = Person.new("BMW", 58937, 0, "M", 18)
    assert_equal(p0.evaluate_policy("policy.rb"), 18.45)
    
    p1 = Person.new("Citroen", 58726, 1, "Male", 25)
    assert_equal(p1.evaluate_policy("policy.rb"), 14.85)
    
    p2 = Person.new("Fiat", "61152", 2, "F", 28)
    assert_equal(p2.evaluate_policy("policy.rb"), 12)

    p3 = Person.new("Ford", "61172", 3, "Female", 35)
    assert_equal(p3.evaluate_policy("policy.rb"), 13.5)
    
    p4 = Person.new("Saab", "58933", "4", "Male", 63)
    assert_equal(p4.evaluate_policy("policy.rb"), 10.5)

    p5 = Person.new("Flygplan", "59232", 5, "Male", "75")
    assert_equal(p5.evaluate_policy("policy.rb"), 8.5)
    
    p6 = Person.new("Volvo", 58937, 0, "M", 18)
    assert_equal(p6.evaluate_policy("policy.rb"), 22.14)
  end
end

class TestSecond < Test::Unit::TestCase
  def test_upg2
    logicCalc = LogicCalc.new
    # Test for main logic
    assert_true(logicCalc.calc(true, "(and true true)"))
    assert_false(logicCalc.calc(true, "(and true false)"))
    assert_false(logicCalc.calc(true, "(and false false)"))
    assert_false(logicCalc.calc(true, "(and false true)"))

    assert_true(logicCalc.calc(true, "(or true false)"))
    assert_true(logicCalc.calc(true, "(or true true)"))
    assert_true(logicCalc.calc(true, "(or false true)"))
    assert_false(logicCalc.calc(true, "(or false false)"))

    assert_true(logicCalc.calc(true, "(not false)"))
    assert_false(logicCalc.calc(true, "(not true)"))

    # Test for nestled statements
    assert_true(logicCalc.calc(true, "(and true (not false))"))
    assert_true(logicCalc.calc(true, "(or (not true) (and true (or true false)))"))

    # Test for variables
    assert_true(logicCalc.calc(true, "(set varA true)"))
    assert_false(logicCalc.calc(true, "(set varB false)"))
    assert_true(logicCalc.calc(true, "(set var12abc varA)"))

    assert_false(logicCalc.calc(true, "(not varA)"))
    assert_true(logicCalc.calc(true, "(not varB)"))
    assert_false(logicCalc.calc(true, "(not var12abc)"))

    assert_true(logicCalc.calc(true, "(and varA varA)"))
    assert_false(logicCalc.calc(true, "(and varA varB)"))
    assert_true(logicCalc.calc(true, "(or varA varB)"))
    
    assert_false(logicCalc.calc(true, "(set varA varB)"))
    assert_false(logicCalc.calc(true, "(or varA varB)"))
    assert_true(logicCalc.calc(true, "(set varB true)"))
    assert_true(logicCalc.calc(true, "(not varA)"))
    assert_false(logicCalc.calc(true, "(not varB)"))

    assert_equal("Not allowed variable name! Can't be 'true' or 'false'", logicCalc.calc(true, "(set true true)"))
    assert_equal("Not allowed variable name! Can't be 'true' or 'false'", logicCalc.calc(true , "(set false true)"))
  end
end
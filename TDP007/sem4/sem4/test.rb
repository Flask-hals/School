require './constraint_networks.rb'
require './constraint-parser.rb'
require 'test/unit'

class TestFirst < Test::Unit::TestCase
    def test_adder
        a = Connector.new("a")
        b = Connector.new("b")
        c = Connector.new("c")
        Adder.new(a, b, c)
        # A + B = C
        a.user_assign 5
        b.user_assign 10
        assert_equal(15, c.value)

        # C - B = A
        a.forget_value "user"
        c.user_assign 20
        assert_equal(10, a.value)

        # C - A = B
        b.forget_value "user"
        a.user_assign 10
        assert_equal(10, b.value)
    end
    
    def test_sub
      a = Connector.new("a")
      b = Connector.new("b")
      c = Connector.new("c")
      Adder.new(a, b, c)
      
      a.user_assign 5
      
      c.user_assign 2

      assert_equal(-3, b.value)
    end

    def test_multiplier
      a = Connector.new("a")
      b = Connector.new("b")
      c = Connector.new("c")
      Multiplier.new(a, b, c)
      a.user_assign(10)
      b.user_assign(5)
      assert_equal(50, c.value)

      a.forget_value "user"
      c.user_assign(20)
      assert_equal(4, a.value)
    end

    def test_celsiusFahrenheit
      c, f = celsius2fahrenheit
      c.user_assign 100
      assert_equal(f.value, 212)

      c.user_assign 0
      assert_equal(f.value, 32)

      c.forget_value "user"
      assert_equal(f.value, false)
      assert_equal(c.value, false)

      f.user_assign 100
      assert_equal(c.value, 37)

      f.forget_value "user"
      assert_equal(f.value, false)
    end
end

class TestSecond < Test::Unit::TestCase
  def test_parser
    cp=ConstraintParser.new
    c,f=cp.parse "9*c=5*(f-32)"
    f.user_assign 0

    assert_equal(-18, c.value)
    
    f.user_assign 100 
    assert_equal(37, c.value)

    c,f = cp.parse "9+c=5+f"
    c.user_assign 1
    assert_equal(5, f.value)

    c,f = cp.parse "9+c=5+(1+f)"
    c.user_assign 1
    assert_equal(4, f.value)

    c,f = cp.parse "9+c=5+(1+(f))"
    c.user_assign 1
    assert_equal(4, f.value)

    c,f = cp.parse "(9)+(6-c)=2*(1+(f))"
    c.user_assign 1
    assert_equal(6, f.value)

    c,f = cp.parse "6-c=5+f"
    f.user_assign 1
    assert_equal(0, c.value)
  end
end
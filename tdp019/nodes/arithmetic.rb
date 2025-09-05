class Number 
  attr_reader :val
  def initialize(i)
    if i == false
      @val = 0
    elsif i == true
      @val = 1
    else
      @val = i
    end
  end

  def eval(scope)
    self
  end
end


class IntNode < Number
end


class FloatNode < Number
end


class ArithmeticNode 
  attr_reader :a, :b
  def initialize(a, b, op)
      @a = a
      @b = b
      @op = op
  end

  def eval(scope)
    left = @a.eval(scope)
    right = @b.eval(scope)

    if left.is_a?(FloatNode) || right.is_a?(FloatNode)
      return FloatNode.new(left.val.send(@op, right.val))
    else
      return IntNode.new(left.val.send(@op, right.val))
    end
  end
end
        

class AdditionNode < ArithmeticNode
end

class SubtractionNode < ArithmeticNode
end

class MultiplicationNode < ArithmeticNode
end

class DivisionNode < ArithmeticNode
end

class ExponentialNode < ArithmeticNode
end

class ModNode < ArithmeticNode
end


class NegateNode
  def initialize(a)
    @a = a
  end

  def eval(scope)
    IntNode.new(-@a.eval(scope).val)
  end
end
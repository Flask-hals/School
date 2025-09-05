require_relative "./arithmetic.rb"
require_relative "../runtime.rb"

class NotNode 
  def initialize(a)
    @a = a
  end

  def eval(scope)
    IntNode.new(!intToBool(@a.eval(scope).val))
  end
end


class BoolExprNode 
  def initialize(a, b)
    @a = a
    @b = b
  end
end


class AndNode < BoolExprNode
  def eval(scope)
    IntNode.new(intToBool(@a.eval(scope).val) && intToBool(@b.eval(scope).val))
  end
end


class OrNode < BoolExprNode
  def eval(scope)
    IntNode.new(intToBool(@a.eval(scope).val) || intToBool(@b.eval(scope).val))
  end
end


class DiffExprNode < ArithmeticNode
end
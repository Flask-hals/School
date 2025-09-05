class ReturnNode
  attr_reader :val
  def initialize(val)
    @val = val
  end

  def eval(scope)
    @val.eval(scope)
  end
end
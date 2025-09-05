require_relative "./arithmetic.rb"
require_relative"./boolean.rb"
require_relative "../runtime.rb"

class AssignNode
  attr_reader :name, :type
  def initialize(val, name, type)
    if reservedNames(name)
      @name = name
    end
    
    @type = caseType(type)

    @val = val
  end

  def addVal(expr)
    @val = expr
  end

  def eval(scope)
    node = @val.eval(scope)
    if node.class == @type
      scope["vars"][@name] = node
      return node
    elsif @type <= Number && node # If node is false, node is a void function
      node = intFloatConverter(node, @type)
    else
      raise Error::TypeError, "Can't assign #{node.class} as #{@type}."
    end

    scope["vars"][@name] = node
    node
  end
end

class VarChangeNode
  def initialize(var, val)
    @var = var
    @val = val
  end

  def eval(scope)    
    varScope = findScope(scope, @var.name)
    privateConst(varScope, scope, @var)

    if @val.class == VarNode
      valScope = findScope(scope, @val.name)
      privateConst(valScope, scope, @val)
    else
      valScope = scope
    end

    type = nil
    case varScope["vars"][@var.name]
    when IntNode
      type = :int
    when FloatNode
      type = :float
    end
    AssignNode.new(@val.eval(valScope), @var.name, type).eval(varScope)
  end
end

class VarNode
  attr_reader :name
  def initialize(name)
    @name = name
  end

  def eval(scope)
    if reservedNames(@name)
      newScope = findScope(scope, @name)
      privateConst(newScope, scope, self)

      return newScope["vars"][@name]
    end
  end
end
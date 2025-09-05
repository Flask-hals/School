require_relative "./arithmetic.rb"
require_relative "../runtime.rb"

class LListNode
  attr_accessor :start
  def initialize(name, start)
    @name = name
    @start = start
  end

  def eval(scope)
    scope["vars"][@name] = self
  end
end

class LListItemNode
  attr_accessor :nextNode, :node
  def initialize(nextNode, node)
    @nextNode = nextNode
    @node = node
  end

  def eval(scope)
    @node.eval(scope)
  end
end

class LListAccessNode
  def initialize(name, index)
    @name = name
    @index = index.flatten
  end

  def eval(scope, change=nil)
    current = scope["vars"][@name].start
    steps = 0
    for i in @index
      i = intFloatConverter(i.eval(scope), IntNode).val
      steps += 1
      counter = 0
      while counter != i
        counter = counter + 1
        if current.nextNode == nil
          raise Parser::ParseError, "Index #{i} out of range for linked list #{@name}."
        else
          current = current.nextNode
        end
      end
      if current.node.is_a?(LListNode) && steps != @index.length
        current = current.node.start
      end
    end

    if current.node.is_a?(LListNode)
      return current.node
    elsif change
      return current
    else
      return current.eval(scope)
    end
  end
end

class LListChangeNode
  def initialize(node, value)
    @node = node
    @value = value
  end
  
  def eval(scope)
    itemNode = @node.eval(scope, true)
    itemNode.node = @value
  end
end

class LListPushFront
  def initialize(name, val)
    @name = name
    @val = val
  end

  def eval(scope)
    if !(@val.class <= Number)
      raise Error::ValueError, "Can't push #{@val} to llist."
    else
      scope = findScope(scope, @name)
      list = scope["vars"][@name]
      list.start = LListItemNode.new(list.start, @val)
    end
  end
end

class LListPopFront
  def initialize(name)
    @name = name
  end

  def eval(scope)true
    scope = findScope(scope, @name)
    list = scope["vars"][@name]
    if list.start == nil
      nil #raise Parser::ParseError, "List #{@name} empty, can't pop element."
    else
      list.start = list.start.nextNode
      nil
    end
  end
end
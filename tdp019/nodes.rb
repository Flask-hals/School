require_relative './runtime.rb'

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


class PrintNode 
  attr_reader :arg
  def initialize(a)
    @arg = a
  end

  def eval(scope)
    node = @arg.eval(scope)
    if node.is_a?(LListNode)
      printLList(node, scope)
    else
      puts node.val
    end
  end
end

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
    if @val.class == VarNode
      valScope = findScope(scope, @val.name)
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
      scope = findScope(scope, @name)
      return scope["vars"][@name]
    end
  end
end

class IfNode
  def initialize(expr, block)
    @expr = expr
    @blockScope = {"parent" => nil, "stmts" => block, "vars" => {}}
  end

  def eval(scope)
    boolexpr = intToBool(@expr.eval(scope).val)
    if boolexpr
      @blockScope["parent"] = scope
      for node in @blockScope["stmts"]
        if node.class == ReturnNode # Break and return the node if return
          return node
        else
          nestledNode = node.eval(@blockScope)
          if nestledNode.class == ReturnNode # In case nestled if or while statements
            return nestledNode
          end
        end
      end
    end
  end
end

class WhileNode
  def initialize(expr, block)
    @expr = expr
    @blockScope = {"parent" => nil, "stmts" => block, "vars" => {}}
  end

  def eval(scope)
    tmp = @expr.dup
    boolexpr = intToBool(tmp.eval(scope).val)
    @blockScope["parent"] = scope 
    while boolexpr
      for node in @blockScope["stmts"]
        if node.class == ReturnNode # Break and return the node if return
          return node
        else
          nestledNode = node.eval(@blockScope)
          if nestledNode.class == ReturnNode # In case nestled if or while statements
            return nestledNode
          end
        end
      end
      tmp = @expr.dup
      boolexpr = intToBool(tmp.eval(scope).val)
    end
  end
end

class FuncDeclarationNode # Gets params as a list of AssignNodes
  attr_reader :params, :name, :block, :callScope
  attr_accessor :virtual, :override
  def initialize(type, name, params, block, endname)
    if name != endname
      raise Parser::ParseError, "End tag #{endname} must match start tag #{name}"
    else
      @typeName = type #For correct error message for bool
      @type = caseType(type)
      @name = name
      @params = params
      @block = block
      @virtual = false
      @override = false
      #@classScope = nil
    end
  end

  def call(args, callScope)
    blockScope = {"parent" => callScope, "stmts" => @block, "vars" => {}}
    ret = nil
    if args != nil
      for index in (0..@params.length-1) # evaluate arguments first
        argValue = args[index].eval(callScope)
        @params[index].addVal(argValue)
        @params[index].eval(blockScope)
      end
    end
    for node in blockScope["stmts"] # evaluate statement nodes after
      if node.class == ReturnNode
        ret = node
        break
      else
        tmp = node.eval(blockScope)
        if tmp.class == ReturnNode
          return ret = tmp.eval(blockScope)
        end
      end
    end
    if ret != nil
      returnNode = ret.eval(blockScope) # finally evaluate return
      if @type != :void
        if returnNode.class == @type
          return returnNode
        else
          return intFloatConverter(returnNode, @type)
        end
      elsif returnNode.val == 0
        return returnNode
      else
        raise Error::RuntimeError, "Void function '#{@name}' should not return a value."
      end
    elsif ret == nil && @type == :void
      return IntNode.new(0)
    else
      if @typeName == :bool
        raise Error::ValueError, "BoolNode function '#{@name}' must return a value."
      else
        raise Error::ValueError, "#{@type} function '#{@name}' must return a value."
      end
    end
  end

  def recursive(func)
    recursive = false
    func.block.each do |items|
      if items.is_a?(ReturnNode)
        if !items.val.is_a?(IntNode)
          if items.val.is_a?(VarNode)
            recursive = items.val.name == @name
          elsif items.val.a.is_a?(FuncCall)
            recursive = items.val.a.name == @name
          elsif items.val.b.is_a?(FuncCall)
            recursive = items.val.b.name == @name
          end
        end
      end
    end
    return recursive
  end

  def eval(scope)
    #@callScope = scope
    scope["vars"][@name] = self
  end
end

class FuncCall # Gets args as a list of expression nodes
  attr_reader :name, :dynamic
  def initialize(name, args, dynamic=false)
    @name = name
    @args = args
    @dynamic = dynamic
  end

  def eval(scope) # kanske måste kolla om det ens är en function

    newScope = findScope(scope, @name)
    func = newScope["vars"][@name]
    if newScope.has_key?("vtable")
      inVtable = newScope["vtable"].has_key?(@name)
      if inVtable && newScope["vtable"][@name][0].override
        newScope = newScope["vtable"][@name][1]
        func = newScope["vtable"][@name][0]
      end
    end

    if func.recursive(func)# || func.callScope == newScope
      newScope = scope
    end

    if newScope.has_key?("private")
      currentScope = scope
      while currentScope["private"] == nil
        currentScope = currentScope["parent"]
      end
      if !(newScope["stmts"].include?(func) || newScope["name"] == currentScope["name"])
        raise Error::TypeError, "Function #{@name} is private."
      end
    end

    if func.is_a?(FuncDeclarationNode)
      if func.params != nil
        if func.params.length != @args.length # kollar om längden av argument är samma (vet inte om detta behövs nu eftersom funktioner inte kan dela namn)
          raise Error::ArgumentError, 
            "Function '#{@name}' has #{func.params.length} arguments, but #{@args.length} were given."
        end
      end
      if newScope.has_key?("private")
          func.call(@args, newScope)
      else
        func.call(@args, scope) 
      end
    else
      raise Error::TypeError, "Function #{@name} not found."
    end    
  end
end

class ReturnNode
  attr_reader :val
  def initialize(val)
    @val = val
  end

  def eval(scope)
    @val.eval(scope)
  end
end

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

class ClassNode
  attr_reader :name, :baseClassName, :allSTMTS
  attr_accessor :classScope, :block, :baseClass, :derived
  def initialize(name, baseClassName=nil, priv, pub, endname)
    # @vtable = {}
    #@derived = nil
    if baseClassName == ""
      @baseClassName = nil
    else
      @baseClassName = baseClassName #[private/public, name]
    end
    if priv == ""
      @priv = []
    else
      @priv = priv
    end
    if pub == ""
      @pub = []
    else
      @pub = pub
    end
    if name != endname
      raise Parser::ParseError, "End tag #{endname} must match start tag #{name}"
    else
      @name = name
    end
    @classScope = {"name" => name, "parent" => Ctml.globalScope, "stmts" => @pub, "private" => @priv, "vars" => {}, "vtable" => {}, "derived" => nil} #Ta bort derived
    @baseClass
    @allSTMTS = @pub.concat(@priv)
    @allSTMTS.each do |items|
      if items.class != FuncDeclarationNode
          next
      elsif items.virtual
        @classScope["vtable"][items.name] = [items, @classScope]
      end
    end
  end

  def eval(scope)
    if @baseClassName
      @baseClass = scope["userClasses"][@baseClassName[1]]
      @classScope["parent"] = @baseClass.classScope
      @allSTMTS.each do |items|
        if items.class != FuncDeclarationNode
          next
        elsif !items.override
          next
        elsif !@baseClass.classScope["vtable"].has_key?(items.name) # To see if the virtual function in baseclass and the override functions has the same name
          raise Error::LogicError, "Name for override function '#{items.name}' must match a virtual function."
        elsif !items.params && !@baseClass.classScope["vtable"][items.name][0].params
          @classScope["vtable"][items.name] = [items, @classScope]
        elsif !items.params && @baseClass.classScope["vtable"][items.name][0].params || !@baseClass.classScope["vtable"][items.name][0].params && items.params
          raise Error::LogicError, "Params for override function '#{items.name}' must match its virtual function."
        elsif items.params.length() != @baseClass.classScope["vtable"][items.name][0].params.length()
          raise Error::LogicError, "#{items.params.length} params were given for function '#{items.name}' but must be #{@baseClass.classScope["vtable"][items.name][0].params.length()}."
        else
          index = 0
          while index < items.params.length()
            if items.params[index].type != @baseClass.classScope["vtable"][items.name][0].params[index].type
              raise Error::LogicError, "Param at index #{index} for override function '#{items.name}' must be of type '#{@baseClass.classScope["vtable"][items.name][0].params[index].type}'
                                        but was '#{items.params[index].type}'"
            else
              index += 1
            end
          end
          @classScope["vtable"][items.name] = [items, @classScope]
        end
      end
    elsif !@baseClassName
      @allSTMTS.each do |items|
        if items.class != FuncDeclarationNode
          next
        elsif items.override
          raise Error::DeclarationError, "Cannot declare override without matching virtual function in base class."
        end
      end
    end
    scope["userClasses"][@name] = self
  end
end

class ClassFuncCall
  def initialize(objectVar, funcName, args=nil)
    @objectVar = objectVar
    @funcName = funcName
    @args = args
  end

  def eval(scope)
    obj = @objectVar.eval(scope)
    newScope = nil
    funcNode = nil

    inVtable = obj.classScope["vtable"].has_key?(@funcName)
    if inVtable
      value = obj.classScope["vtable"][@funcName]
      newScope = value[1]
      funcNode = value[0]
    else
      newScope = findScope(obj.classScope, @funcName)
      funcNode = newScope["vars"][@funcName]
    end
    if (obj.baseClassName && obj.baseClassName[0] == :private && newScope != obj.classScope) || newScope["private"].include?(funcNode)      
      # if function is a private class member
      raise Error::ValueError, "Function '#{@funcName}' is private in class '#{newScope["name"]}'"
    else
      return funcNode.call(@args, newScope)
    end
  end
end

class ObjectDeclaration
  attr_reader :typeName
  def initialize(className, objectName, typeName=nil)
    @className = className
    @objectName = objectName
    @typeName = typeName
  end
  

  def eval(scope)
    classObj = Marshal.load(Marshal.dump(Ctml.globalScope["userClasses"][@className]))

    #classObj.classScope = classObj.classScope.dup
    
    if @typeName
      child = false
      childClass = Ctml.globalScope["userClasses"][@typeName]
      while childClass
        if childClass.name == @className
          child = true
        end
        childClass = childClass.baseClass
      end

      if child
        puts "#{@typeName} is a child to #{@className}"
        derivedClassObj = Marshal.load(Marshal.dump(Ctml.globalScope["userClasses"][@typeName]))
        classObj.classScope["derived"] = derivedClassObj
      else
        raise Error::LogicError, "#{@typeName} is a not child to #{@className}"
      end
    end
    superClass = classObj
    if superClass
      while superClass
        if superClass.classScope["private"].length() != 0
          for declaration in superClass.classScope["private"]
            declaration.eval(superClass.classScope)
          end
        end
        if superClass.classScope["stmts"].length() != 0
          for declaration in superClass.classScope["stmts"]
            declaration.eval(superClass.classScope)
          end
        end
        superClass = superClass.baseClass
      end
    end

    # if derived exists, evaluate it and all its super classes untill it reaches the base class
    # that was evaluted in the previous loop
    superClass = derivedClassObj
    if superClass
      while superClass.baseClass != nil
        if superClass.classScope["private"].length() != 0
          for declaration in superClass.classScope["private"]
            declaration.eval(superClass.classScope)
          end
        end
        if superClass.classScope["stmts"].length() != 0
          for declaration in superClass.classScope["stmts"]
              declaration.eval(superClass.classScope)
          end
        end
        # Updates vtable with override functions
        for key, value in superClass.classScope["vtable"]
          if superClass != derivedClassObj
            if classObj.classScope["vtable"][key][0].override
              next
            end
          else
            classObj.classScope["vtable"][key] = [value[0], superClass.classScope]
          end
        end
        superClass = superClass.baseClass
      end
      superClass.classScope["parent"] = classObj.classScope
    end   

    scope["vars"][@objectName] = classObj
  end
end
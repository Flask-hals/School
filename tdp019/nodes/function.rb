require_relative "./return.rb"
require_relative "./arithmetic.rb"
require_relative "./variable.rb"
require_relative "../runtime.rb"

class FuncDeclarationNode # Gets params as a list of AssignNodes
  attr_reader :params, :name, :block, :callScope
  attr_accessor :virtual, :override
  def initialize(type, name, params, block, endname)
    if name != endname
      raise Parser::ParseError, "End tag #{endname} must match start tag #{name}"
    else
      @typeName = type #For correct error message for bool
      @type = caseType(type)
      if reservedNames(name.to_sym)
        @name = name
      end
      @params = params
      @block = block
      @virtual = false
      @override = false
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

  def eval(scope)
    newScope = findScope(scope, @name)
    func = newScope["vars"][@name]

    if newScope.has_key?("vtable")
      inVtable = newScope["vtable"].has_key?(@name)
      if inVtable && newScope["vtable"][@name][0].override
        newScope = newScope["vtable"][@name][1]
        func = newScope["vtable"][@name][0]
      end
    end

    if func.recursive(func)
      newScope = scope
    end


    privateConst(newScope, scope, func)

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
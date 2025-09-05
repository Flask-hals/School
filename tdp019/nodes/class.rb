require_relative "./function.rb"
require_relative "../runtime.rb"

class ClassNode
  attr_reader :name, :baseClassName, :allSTMTS
  attr_accessor :classScope, :block, :baseClass
  def initialize(name, baseClassName=nil, priv, pub, endname)
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
    @classScope = {"name" => name, "parent" => Ctml.globalScope, "stmts" => @pub, "private" => @priv, "vars" => {}, "vtable" => {}}
    @baseClass
    
    @allSTMTS = []
    @allSTMTS.concat(@pub)
    @allSTMTS.concat(@priv)

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

        else
          itemClass = findScope(@baseClass.classScope, items.name)

          if !itemClass["vtable"].has_key?(items.name) # To see if the virtual function in baseclass and the override functions has the same name
            raise Error::LogicError, "Name for override function '#{items.name}' must match a virtual function."
          elsif !items.params && !itemClass["vtable"][items.name][0].params
            @classScope["vtable"][items.name] = [items, @classScope]
          elsif !items.params && itemClass["vtable"][items.name][0].params || !itemClass["vtable"][items.name][0].params && items.params
            raise Error::LogicError, "Params for override function '#{items.name}' must match its virtual function."
          elsif items.params.length() != itemClass["vtable"][items.name][0].params.length()
            raise Error::LogicError, "#{items.params.length} params were given for function '#{items.name}' but must be #{itemClass["vtable"][items.name][0].params.length()}."
          else
            index = 0
            while index < items.params.length()
              if items.params[index].type != itemClass["vtable"][items.name][0].params[index].type
                raise Error::LogicError, "Param at index #{index} for override function '#{items.name}' must be of type '#{itemClass["vtable"][items.name][0].params[index].type}'
                                          but was '#{items.params[index].type}'"
              else
                index += 1
              end
            end
            @classScope["vtable"][items.name] = [items, @classScope]
          end
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
        # puts "#{@typeName} is a child to #{@className}"
        derivedClassObj = Marshal.load(Marshal.dump(Ctml.globalScope["userClasses"][@typeName]))
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
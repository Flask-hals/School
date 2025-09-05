def reservedNames(name)
    reserved = [:if, :true, :false, :print, :arg, :float, :int, :not, :bool, :endif, :while, :endwhile, :void, :return, :list, :push_front, :pop_front]
    if reserved.include?(name)
        raise Error::NameError, "#{name} is a reserved name and can't be used as a varname"
    else
        return true
    end
end

def findScope(scope, name)
    currentScope = scope
    while currentScope["parent"] != nil
        if currentScope["vars"][name]
            return currentScope
        else
          currentScope = currentScope["parent"]
        end
      end 
    if currentScope["parent"] == nil
        if currentScope["vars"][name]
            return currentScope
        end
    end
    raise Error::NameError, "Variable #{name} hasn't been declared yet"
end

def intToBool(val)
    if val.is_a?(Integer) || val.is_a?(Float)
        if val == 0
            return false
        end
        return val
    else
        raise Error::TypeError, "Cant convert #{val.class} to bool"
    end
end

def intFloatConverter(node, type)
    if node.is_a?(Number) && type <= Number
        if type == IntNode
            return IntNode.new(node.val.to_i)
        else
            return FloatNode.new(node.val.to_f)
        end
    else
        raise Error::TypeError, "Invalid class for #{node}, can't convert to #{type}"
    end
end

def caseType(type)
    case type
    when :int, :bool # bool is recognized as int
      return IntNode
    when :float
      return FloatNode
    when :void
      return  type
    when :llist
        return LListNode
    end
end

def printLList(node, scope)
    str = "{"
    current = node.start
    prevNodes = []
    while current != nil
        if current.node.is_a?(LListNode)
            prevNodes << current
            current = current.node.start
            str += "{"
        else          
            str += current.eval(scope).val.to_s + ", "
            if current.nextNode == nil && !prevNodes.empty?
            current = prevNodes.pop
            while current.nextNode == nil && !prevNodes.empty?
                current = prevNodes.pop
                str = str.delete_suffix(", ")
                str += "}, "
            end
            str = str.delete_suffix(", ")
            str += "}, "
            end
            current = current.nextNode
        end
    end
    str = str.delete_suffix(", ")
    puts str += "}"
end

class Error
    class ValueError < RuntimeError
    end

    class TypeError < RuntimeError
    end

    class NameError < RuntimeError
    end

    class ArgumentError < RuntimeError
    end

    class RuntimeError < RuntimeError
    end

    class DeclarationError < RuntimeError
    end

    class LogicError < RuntimeError
    end
end
require_relative "./return.rb"
require_relative "../runtime.rb"

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
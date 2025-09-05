require_relative "./return.rb"
require_relative "../runtime.rb"


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
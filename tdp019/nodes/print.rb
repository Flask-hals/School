require_relative "./llist.rb"
require_relative "../runtime.rb"

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
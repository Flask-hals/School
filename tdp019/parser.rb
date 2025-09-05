#!/usr/bin/env ruby

require_relative './rdparse.rb'
require_relative './nodes.rb'

class Ctml

  
  @@globalScope = {"parent" => nil, "stmts" => [], "vars" => {}, "userClasses" => {}}

  #@@globalScope = {"parent" => nil, "stmts" => [], "vars" => {}, "userClasses" => {}, "datatypes => IntNode,  }

  def self.globalScope
    @@globalScope
  end

  def initialize
    @ctmlParser = Parser.new("CTML++") do
      token(/\s+/)
      token(/\d+\.\d*/) {|m| m.to_f } # ex 1.
      token(/\d*\.\d+/) {|m| m.to_f } # ex .1
      token(/\d+/) {|m| m.to_i }
      token(/print/) {:print}
      token(/arg/) {:arg}
      token(/true/) {:true}
      token(/false/) {:false}
      token(/float /) {:float}
      token(/int /) {:int}
      token(/bool /) {:bool}
      token(/<while /) {:while}
      token(/<\/while>/) {:endwhile}
      token(/<if /) {:if}
      token(/<\/if>/) {:endif}
      token(/void /) {:void}
      token(/ret/) {:return}
      token(/llist /) {:llist}
      token(/push_front/) {:push_front}
      token(/pop_front/) {:pop_front}
      token(/class /) {:class}
      token(/<private\/>/) {:private}
      token(/<public\/>/) {:public}
      token(/<\/private>/) {:endpriv}
      token(/<\/public>/) {:endpub}
      token(/virtual/) {:virtual}
      token(/override/) {:override}
      token(/_*[a-zA-Z]+\w*/) {|m| m}
      token(/(<=|>=|<\/|\/>|<|>|\!=|==|=|\(|\)|\-|\+|\*|\^|\%|\/|\|\||\&\&|,|{|}|\[|\]|.|!)/) {|m| m}

      start :start do
        match(:start, :classdec) {|_, a|
          if a.class == ReturnNode
            raise Parser::ParseError, "ReturNode can't be used in global"
          else
            @@globalScope["stmts"].append(a)
            @@globalScope
          end
        }
        
        match(:classdec) {|a|
          if a.class == ReturnNode
            raise Parser::ParseError, "ReturNode can't be used in global"
          else
            @@globalScope["stmts"].append(a)
            @@globalScope
          end
        }
      end

      rule :classdec do
        # match("<", :class, :varname, :heritage, "/>", :classblock, "</", :varname, ">") {|_, _, name, base, _, block, _, endname, _| ClassNode.new(name, base, "", block, endname)}
        match("<", :class, :varname, :heritage, "/>", :priv, :pub, "</", :varname, ">") {|_, _, name, base, _, priv, pub, _, endname, _| ClassNode.new(name, base, priv, pub, endname)}
        match("<", :class, :varname, :heritage, "/>", :pub, :priv, "</", :varname, ">") {|_, _, name, base, _, pub, priv, _, endname, _| ClassNode.new(name, base, priv, pub, endname)}
        match("<", :class, :varname, :heritage, "/>", :pub, "</", :varname, ">") {|_, _, name, base, _, pub, _, endname, _| ClassNode.new(name, base, nil, pub, endname)}
        match("<", :class, :varname, :heritage, "/>", :priv, "</", :varname, ">") {|_, _, name, base,  _, priv, _, endname, _| ClassNode.new(name, base, priv, nil, endname)}
        #match("<", :class, :varname, ":", :heritage, :varname, "/>", :classblock, "</", :varname, ">") {|_, _, name, _, _, base, _, block, _, endname, _| ClassNode.new(name, base, block, endname)}
        match(:funcdec)
      end

      rule :priv do
        match(:private, :classblock, :endpriv) {|_, block, _| block}
        match() {""}
      end

      rule :pub do
        match(:public, :classblock, :endpub) {|_, block, _| block}
        match() {""}
      end

      rule :heritage do
        match(":", "public", :varname) {|_, public, name| [:public, name]}
        match(":", "private", :varname) {|_, private, name| [:private, name]}
        match() {""}
      end

      rule :classblock do      
        match(:classblock, :polyfuncdec) {|a, b| a << b}
        match(:polyfuncdec) {|a| [a]}
        match() {""}
      end

      rule :funcdec do
        match("<", :void, :varname, "(", :params, ")", "/>", :block, "</", :varname, ">") {|_, type, name, _, params, _, _, block, _, endname, _| 
          FuncDeclarationNode.new(type, name, params, block, endname)}

        match("<", :void, :varname, "(", ")", "/>", :block, "</", :varname, ">") {|_, type, name, _, _, _, block, _, endname, _| 
          FuncDeclarationNode.new(type, name, nil, block, endname)}

        match("<", :type, :varname, "(", :params, ")", "/>", :block, "</", :varname, ">") {|_, type, name, _, params, _, _, block, _, endname, _| 
          FuncDeclarationNode.new(type, name, params, block, endname)}

        match("<", :type, :varname, "(", ")", "/>", :block, "</", :varname, ">") {|_, type, name, _, _, _, block, _, endname, _| 
          FuncDeclarationNode.new(type, name, nil, block, endname)}
        
        match(:sections)
      end

      rule :classfuncdec do # In a class, you can only use function declarations; therefore, we cannot proceed to sections like :funcdec.
        match("<", :void, :varname, "(", :params, ")", "/>", :block, "</", :varname, ">") {|_, type, name, _, params, _, _, block, _, endname, _| 
          FuncDeclarationNode.new(type, name, params, block, endname)}

        match("<", :void, :varname, "(", ")", "/>", :block, "</", :varname, ">") {|_, type, name, _, _, _, block, _, endname, _| 
          FuncDeclarationNode.new(type, name, nil, block, endname)}

        match("<", :type, :varname, "(", :params, ")", "/>", :block, "</", :varname, ">") {|_, type, name, _, params, _, _, block, _, endname, _| 
          FuncDeclarationNode.new(type, name, params, block, endname)}

        match("<", :type, :varname, "(", ")", "/>", :block, "</", :varname, ">") {|_, type, name, _, _, _, block, _, endname, _| 
          FuncDeclarationNode.new(type, name, nil, block, endname)}

        match("<", :type, :varname, "=", :boolexpr, "/>") {|_, type, name, _, val, _| AssignNode.new(val, name, type)}

        match("<", :llist, :varname, "=", "{", :llistTerm, "}", "/>") {|_, _, name, _, _, items, _, _|
          LListNode.new(name, items)}

        #match("<", :varname, :varname, "=", :varname, "/>") {|_, className, objectName, _, typeName, _| ObjectDeclaration.new(className, objectName, typeName)}
        #match("<", :varname, :varname, "/>") {|_, className, objectName, _| ObjectDeclaration.new(className, objectName)}
      end

      rule :polyfuncdec do
        # match("<", :virtual, :void, :varname, "(", :params, ")", "/>", :block, "</", :varname, ">") {|_, _, type, name, _, params, _, _, block, _, endname, _| 
        #   VirtualFuncNode.new(type, name, params, block, endname)} #BÖR VARA FUNCDECLARATIONODE MEN ORKADE INTE FIXA DE NU NÄR JAG TESTAR, för alla dessa

        # match("<", :virtual, :void, :varname, "(", ")", "/>", :block, "</", :varname, ">") {|_, _, type, name, _, _, _, block, _, endname, _| 
        #   VirtualFuncNode.new(type, name, nil, block, endname)}

        # match("<", :virtual, :type, :varname, "(", :params,        match()ndname)}

        # match("<", :void, :varname, "(", ")", :override, "/>", :block, "</", :varname, ">") {|_, type, name, _, _, _, _, block, _, endname, _| 
        #   OverrideFuncNode.new(type, name, nil, block, endname)}

        # match("<", :type, :varname, "(", :params, ")", :override, "/>", :block, "</", :varname, ">") {|_, type, name, _, params, _, _, _, block, _, endname, _| 
        #   OverrideFuncNode.new(type, name, params, block, endname)}

        # match("<", :type, :varname, "(", ")", :override, "/>", :block, "</", :varname, ">") {|_, type, name, _, _, _, _, block, _, endname, _| 
        #   OverrideFuncNode.new(type, name, nil, block, endname)}

        match("<", :virtual, "/>", :classfuncdec) {|_, _, _, func| func.virtual = true; func}
        match("<", :override, "/>", :classfuncdec) {|_, _, _, func| func.override = true; func}
        
        match(:classfuncdec)
      end

      rule :block do      
        match(:block, :sections) {|a, b| a << b}
        match(:sections) {|a| [a]}
        match() {""}
      end

      rule :sections do
        match(:printer)
        match(:while, :boolexpr, "/>", :block, :endwhile) {|_, expr, _, block, _| WhileNode.new(expr, block)}
        match(:if, :boolexpr, "/>", :block, :endif) {|_, expr, _, block, _| IfNode.new(expr, block)}
        #match("<", :llist, "<", :llistType, ">", :varname, "=", "{", :llistTerm, "}", "/>") {|_, _, _, type, _, name, _, _, items, _, _|
        #  LListNode.new(type, name, items)}
        match("<", :llist, :varname, "=", "{", :llistTerm, "}", "/>") {|_, _, name, _, _, items, _, _|
          LListNode.new(name, items)}
        #match("<", :return, :boolexpr, "/>") {|_, _, value, _| ReturnNode.new(value)}
        match("<", :return, :boolexpr, "/>") {|_, _, value, _| ReturnNode.new(value)}
        match("<", :return, "/>") {|_, _, _| ReturnNode.new(IntNode.new(0))}
        
        # från Assign bara för att testa !!!!!!!!!!!!
        match("<", :type, :varname, "=", :boolexpr, "/>") {|_, type, name, _, val, _| AssignNode.new(val, name, type)}
        match("<", :vars, "=", :boolexpr, "/>") {|_, var, _, val, _| VarChangeNode.new(var, val)}
        match("<", :listAccess, "=", :boolexpr, "/>") {|_, node, _, val, _| 
          LListChangeNode.new(node, val)}
        match("<", :varname, ".", :push_front, "(", :boolexpr, ")", "/>") {|_,name, _, _, _, val, _, _| LListPushFront.new(name, val)}
        # match("<", :varname, ".", :push_back, "(", :boolexpr, ")", "/>") {|_,name, _, _, _, val, _, _| LListPushBack.new(name, val)}
        # match("<", :varname, ".", :pop_back, "(", :boolexpr, ")", "/>") {|_,name, _, _, _, val, _, _| LListPushBack.new(name, val)}
        match("<", :varname, ".", :pop_front, "(", ")", "/>") {|_,name, _, _, _, _, _| LListPopFront.new(name)}
        match("<", :boolexpr, "/>") {|_,a,_| a}
        match("<", :varname, :varname, "=", :varname, "/>") {|_, className, objectName, _, typeName, _| ObjectDeclaration.new(className, objectName, typeName)}
        match("<", :varname, :varname, "/>") {|_, className, objectName, _| ObjectDeclaration.new(className, objectName)}

        # match(:assign)
      end

      rule :llistTerm do
        match(:llistItem, ",", :llistTerm) {|val, _, nextNode| LListItemNode.new(nextNode, val)}
        match(:llistItem) {|val| LListItemNode.new(nil, val)}
      end

      rule :llistItem do
        match(:boolexpr) {|val| val }
        match("{", :llistTerm, "}") {|_, val, _| LListNode.new(nil, val) }
      end

      rule :funcCallArgs do
        match(:funcCallArgs, ",", :boolexpr) {|a, _, expr| a << expr} # skicka upp en lista med exprs och använd AssignNode.addVal sen för att lägga till de
        match(:boolexpr) {|expr| [expr]}
      end

      rule :params do
        match(:params, ",", :type, :varname) {|a, _, type, name| a << AssignNode.new(nil, name, type)} # skapa AssignNodes utan värde (lägg till värde med addVal sen)
        match(:type, :varname) {|type, name| [AssignNode.new(nil, name, type)]}
      end

      rule :boolexpr do
        match("!", :boolexpr) {|_, a| NotNode.new(a)}
        match(:andorexpr)
      end

      rule :andorexpr do
        match(:diff, "&&", :boolexpr) {|a, _, b| AndNode.new(a, b)}
        match(:diff, "||", :boolexpr) {|a, _, b| OrNode.new(a, b)}
        match(:diff)
      end

      rule :diff do
        match(:expr, :diffops, :expr) { |a, op, b| DiffExprNode.new(a, b, op)}
        match(:expr)
      end

      rule :diffops do
        match("==") 
        match("!=")
        match("<")
        match(">")
        match(">=")
        match("<=")
      end

      # rule :assign do
      #   match("<", :type, :varname, "=", :boolexpr, "/>") {|_, type, name, _, val, _| AssignNode.new(val, name, type)}
      #   match("<", :vars, "=", :boolexpr, "/>") {|_, var, _, val, _| VarChangeNode.new(var, val)}
      #   match("<", :listAccess, "=", :boolexpr, "/>") {|_, node, _, val, _| 
      #     LListChangeNode.new(node, val)}
      #   match("<", :varname, ".", :push_front, "(", :boolexpr, ")", "/>") {|_,name, _, _, _, val, _, _| LListPushFront.new(name, val)}
      #   # match("<", :varname, ".", :push_back, "(", :boolexpr, ")", "/>") {|_,name, _, _, _, val, _, _| LListPushBack.new(name, val)}
      #   # match("<", :varname, ".", :pop_back, "(", :boolexpr, ")", "/>") {|_,name, _, _, _, val, _, _| LListPushBack.new(name, val)}
      #   match("<", :varname, ".", :pop_front, "(", ")", "/>") {|_,name, _, _, _, _, _| LListPopFront.new(name)}
      #   match("<", :varname, :varname, "/>") {|_, className, objectName, _| ObjectDeclaration.new(className, objectName)}

      # end

      rule :type do
        match(:int)
        match(:float)
        match(:bool)
        match(:llist)
        #match(:varname)
      end

      rule :varname do
        match(/_*[a-zA-Z]+\w*/)
      end

      rule :printer do
        match("<", :print, "(", :boolexpr, ")", "/>") {|_, _, _, a, _, _| PrintNode.new(a)}
      end
      
      rule :expr do 
        match(:expr, "+", :mulDiv) {|a, _, c| AdditionNode.new(a, c, :+)}
        match(:expr, "-", :mulDiv) {|a, _, c| SubtractionNode.new(a, c, :-)}
        match(:mulDiv)
      end
      
      rule :mulDiv do
        match(:mulDiv, "*", :ex) {|a, _, c| MultiplicationNode.new(a, c, :*)}
        match(:mulDiv, "/", :ex) {|a, _, c| DivisionNode.new(a, c, :/)}
        match(:ex)
      end

      rule :ex do
        match(:term, "^", :ex) {|a, _, c| ExponentialNode.new(a, c, :**)}
        match(:ex, "%", :term) {|a, _, c| ModNode.new(a, c, :%)}
        match(:negate)
      end

      rule :negate do
        match("+", :negate) {|_, a| a}
        match("-", :negate) {|_, a| NegateNode.new(a)}
        match(:term)
      end

      rule :term do
        match(:true) {IntNode.new(1)}
        match(:false) {IntNode.new(0)}
        match(Integer) {|i| IntNode.new(i)}
        match(Float) {|f| FloatNode.new(f)}
        
        match(:this, ".", :varname, "(", :funcCallArgs, ")") {|_, _, name, _, args, _| FuncCall.new(name, args, true)}
        match(:this, ".", :varname, "(", ")") {|_, _, name, _, _| FuncCall.new(name, nil, true)}

        match(:varname, "(", :funcCallArgs, ")") {|name, _, args, _| FuncCall.new(name, args)}
        match(:varname, "(", ")") {|name, _, _| FuncCall.new(name, nil)}
        
        
        # match(:vars, :varname) {|className, objectName| ObjectDeclaration.new(className, objectName)}
        match(:vars, ".", :varname, "(", :funcCallArgs, ")") {|objectVar, _, funcName, _, args, _| ClassFuncCall.new(objectVar, funcName, args)}
        match(:vars, ".", :varname, "(", ")") {|objectVar, _, funcName, _, _| ClassFuncCall.new(objectVar, funcName)}
        match(:listAccess)
        # match(:return, :boolexpr) {|_, value| ReturnNode.new(value)}
        # match(:return) {|_| ReturnNode.new(IntNode.new(0))}
        
        match('(', :boolexpr, ')') {|_, a, _| a}
        match(:vars)
        match()
      end

      rule :listAccess do
        match(:varname, :llistIndex) {|name, index| LListAccessNode.new(name, index)}
      end

      rule :llistIndex do
        match("[", :boolexpr, "]", :llistIndex) {|_, firstIndex, _, innerIndex| [firstIndex] << innerIndex}
        match("[", :boolexpr, "]") {|_, inner, _| [inner]}
      end

      rule :vars do
        match(/_*[a-zA-Z]+\w*/) {|a| VarNode.new(a)}
      end
    end
  end

  # -----------------------------------------------------------------------------------------------------------------------------------------
  
  def done(str)
    ["quit","exit","bye","done",""].include?(str.chomp)
  end
  
  def parser(test=false, str=nil, path=nil)
    log(false)
    if str && path
      puts "Can't parse file and string at the same time"
    else
      if test
        if !str && !path
          puts "No code provided"
        elsif !str && path
          puts "Test: No string"
          file = File.read(path)
          if !file
            puts "File not found"
            return
          else
            @treeNode = @ctmlParser.parse file
            for items in @treeNode["stmts"] # uncomment if running file directly outside tests
              items.eval(@@globalScope)
            end
            return @treeNode
          end
        else
          puts "Test: No path"
          @treeNode = @ctmlParser.parse str
          #tmpReturn = @treeNode["stmts"][0].eval(@@globalScope).val
          @@globalScope = {"stmts" => [], "vars" => {}}
          return @treeNode["stmts"][0].eval(@@globalScope).val # Uncomment .val if problem
        end
      else
        # log(false)
        if !str && path
          puts "No test, No string = interactive"
          file = File.read(path)
          if !file
            puts "File not found"
            return
          else
            @treeNode = @ctmlParser.parse file
            for items in @treeNode["stmts"] # uncomment if running file directly outside tests
              items.eval(@@globalScope)
            end
            return @treeNode
          end
        else
          puts "Interactive"
          print "[ctml++] "
          str = gets
          if done(str) then
            puts "Bye."
          else
            begin
              @treeNode = @ctmlParser.parse str
              # for items in @treeNode["stmts"]
              #   items.eval(@@globalScope)
              # end
              @treeNode["stmts"][-1].eval(@@globalScope)
            rescue Parser::ParseError => e
              puts "Error: #{e.message}"
            end
            #@@globalScope = {"stmts" => [], "vars" => {}}
            parser
          end
        end
      end
    end
  end

  def log(state = true)
    if state
      @ctmlParser.logger.level = Logger::DEBUG
    else
      @ctmlParser.logger.level = Logger::WARN
    end
  end
end


if ARGV.length() > 0
  require 'find'

  targetFilename = ARGV[0]
  foundPath = nil

  Find.find(Dir.pwd) do |path|
    if File.file?(path) && File.basename(path) == targetFilename
      foundPath = path
      break
    end
  end

  if foundPath
    if foundPath.end_with?(".rb")
      system("ruby #{foundPath}")
    else
      Ctml.new.parser(true, nil, foundPath)
    end
  else
    puts "Filen hittades inte."
  end

elsif __FILE__ == "parser.rb"
  #Ctml.new.parser() #Interaktivt
  #Ctml.new.parser(true, nil, "./tests/testFiles/classTest.ctml") #För testning
  Ctml.new.parser(true, nil, "./tests/testFiles/fileTest.ctml")
  #Ctml.new.parser(true, nil, "./tests/testFiles/overrideTest.ctml")
end
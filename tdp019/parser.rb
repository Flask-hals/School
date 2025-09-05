#!/usr/bin/env ruby

require_relative './rdparse.rb'
Dir[File.join(__dir__ , "nodes", "*.rb")].each {|file| require file}

class Ctml
  @@globalScope = {"parent" => nil, "stmts" => [], "vars" => {}, "userClasses" => {}}

  def self.globalScope
    @@globalScope
  end

  def initialize
    @ctmlParser = Parser.new("CTML++") do
      token(/\s+/)
      token(/\d+\.\d*/) {|m| m.to_f } # ex 1.
      token(/\d*\.\d+/) {|m| m.to_f } # ex .1
      token(/\d+/) {|m| m.to_i }
      token(/\bprint\b/) {:print}
      token(/\barg\b/) {:arg}
      token(/\btrue\b/) {:true}
      token(/\bfalse\b/) {:false}
      token(/\bfloat\b/) {:float}
      token(/\bint\b/) {:int}
      token(/\bbool\b/) {:bool}
      token(/\bwhile\b/) {:while}
      token(/\bif\b/) {:if}
      token(/\bvoid\b/) {:void}
      token(/\bret\b/) {:return}
      token(/\bllist\b/) {:llist}
      token(/\bclass\b/) {:class}
      token(/\bprivate\b/) {:private}
      token(/\bpublic\b/) {:public}
      token(/\bvirtual\b/) {:virtual}
      token(/\boverride\b/) {:override}
      token(/[a-zA-Z\w]+/) {|m| m}
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
        match("<", :class, :varname, :heritage, "/>", :priv, :pub, "</", :varname, ">") {|_, _, name, base, _, priv, pub, _, endname, _| ClassNode.new(name, base, priv, pub, endname)}
        match("<", :class, :varname, :heritage, "/>", :pub, :priv, "</", :varname, ">") {|_, _, name, base, _, pub, priv, _, endname, _| ClassNode.new(name, base, priv, pub, endname)}
        match("<", :class, :varname, :heritage, "/>", :pub, "</", :varname, ">") {|_, _, name, base, _, pub, _, endname, _| ClassNode.new(name, base, nil, pub, endname)}
        match("<", :class, :varname, :heritage, "/>", :priv, "</", :varname, ">") {|_, _, name, base,  _, priv, _, endname, _| ClassNode.new(name, base, priv, nil, endname)}
        match(:funcdec)
      end

      rule :priv do
        match("<", :private, "/>", :classblock, "</", :private, ">") {|_,_,_, block, _, _, _| block}
        match() {""}
      end

      rule :pub do
        match("<", :public, "/>", :classblock, "</", :public, ">") {|_,_,_, block, _,_,_| block}
        match() {""}
      end

      rule :heritage do
        match(":", :public, :varname) {|_, public, name| [:public, name]}
        match(":", :private, :varname) {|_, private, name| [:private, name]}
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
      end

      rule :polyfuncdec do
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
        match("<", :while, :boolexpr, "/>", :block, "</", :while, ">") {|_,_, expr, _, block, _, _, _| WhileNode.new(expr, block)}
        match("<", :if, :boolexpr, "/>", :block, "</", :if, ">") {|_,_, expr, _, block, _,_,_| IfNode.new(expr, block)}
        match("<", :llist, :varname, "=", "{", :llistTerm, "}", "/>") {|_, _, name, _, _, items, _, _|
          LListNode.new(name, items)}
        match("<", :return, :boolexpr, "/>") {|_, _, value, _| ReturnNode.new(value)}
        match("<", :return, "/>") {|_, _, _| ReturnNode.new(IntNode.new(0))}
        
        match("<", :type, :varname, "=", :boolexpr, "/>") {|_, type, name, _, val, _| AssignNode.new(val, name, type)}
        match("<", :type, :varname, "/>") {|_, type, name, _|
              if type == :int || type == :float || type == :bool
                AssignNode.new(IntNode.new(0), name, type)
              elsif type == :llist
                AssignNode.new(LListNode.new(name, nil), name, type)
              end}

        match("<", :vars, "=", :boolexpr, "/>") {|_, var, _, val, _| VarChangeNode.new(var, val)}
        match("<", :listAccess, "=", :boolexpr, "/>") {|_, node, _, val, _| 
          LListChangeNode.new(node, val)}
        match("<", :varname, ".", "push_front", "(", :boolexpr, ")", "/>") {|_,name, _, _, _, val, _, _| LListPushFront.new(name, val)}
        match("<", :varname, ".", "pop_front", "(", :boolexpr, ")", "/>") {|_,name, _, _, _, _, _, _| raise }
        match("<", :varname, ".", "pop_front", "(", ")", "/>") {|_,name, _, _, _, _, _| LListPopFront.new(name)}
        match("<", :boolexpr, "/>") {|_,a,_| a}
        match("<", :varname, :varname, "=", :varname, "/>") {|_, className, objectName, _, typeName, _| ObjectDeclaration.new(className, objectName, typeName)}
        match("<", :varname, :varname, "/>") {|_, className, objectName, _| ObjectDeclaration.new(className, objectName)}
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
        match(:params, ",", :type, :varname) {|a, _, type, name| a << AssignNode.new(nil, name, type)}
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

      rule :type do
        match(:int)
        match(:float)
        match(:bool)
        match(:llist)
      end

      rule :varname do
        match(/[a-zA-Z\w]+/)
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
        match(:varname, "(", :funcCallArgs, ")") {|name, _, args, _| FuncCall.new(name, args)}
        match(:varname, "(", ")") {|name, _, _| FuncCall.new(name, nil)} 
        match(:vars, ".", :varname, "(", :funcCallArgs, ")") {|objectVar, _, funcName, _, args, _| ClassFuncCall.new(objectVar, funcName, args)}
        match(:vars, ".", :varname, "(", ")") {|objectVar, _, funcName, _, _| ClassFuncCall.new(objectVar, funcName)}
        match(:listAccess)
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
        match(/[a-zA-Z\w]+/) {|a| VarNode.new(a)}
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
            for items in @treeNode["stmts"]
              items.eval(@@globalScope)
            end
            return @treeNode
          end
        else
          puts "Test: No path"
          @treeNode = @ctmlParser.parse str
          @@globalScope = {"stmts" => [], "vars" => {}}
          return @treeNode["stmts"][0].eval(@@globalScope).val
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
            for items in @treeNode["stmts"]
              items.eval(@@globalScope)
            end
            return @treeNode
          end
        else
          print "[ctml++] "
          str = gets
          if done(str) then
            puts "Bye."
          else
            begin
              @treeNode = @ctmlParser.parse str
              @treeNode["stmts"][-1].eval(@@globalScope)
            rescue Parser::ParseError => e
              puts "Error: #{e.message}"
            end
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
  Ctml.new.parser() #Interactive
end
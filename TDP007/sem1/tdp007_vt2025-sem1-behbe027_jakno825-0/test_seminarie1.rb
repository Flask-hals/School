require './uppgift1'
require './uppgift2'
require './uppgift3'
require './uppgift4'
require './uppgift5'
require './uppgift6'
require './uppgift7'
require 'test/unit'

class TestFaculty < Test::Unit::TestCase
    def test_uppgift1_n_times
      assert_equal(3, n_times(3) { puts "Hello!"})
      assert_equal(5,n_times(5) { puts "Hello!"})
      assert_not_equal(3,n_times(2) {puts "Hello!"})
      assert_raise do #Raises Error, so assertion succeeds
        n_times("hej") {puts "Hello!"} 
      end
    end
    def test_uppgift1_Repeat
        do_three = Repeat.new(3)
        assert_equal(3, do_three.each {puts "Hooray!"})
        do_two = Repeat.new(2)
        assert_not_equal(2, do_three.each{puts "Yay!"})
        assert_equal(2, do_two.each{puts "Yay!"})
        do_string = Repeat.new("Hej")
        assert_raise do #Raises Error, so assertion succeeds
            do_string.each{puts "Hej"} 
          end
    end

    def test_uppgift2_find_it
        assert_equal("apelsin", find_it(["apelsin", "banan", "citron"]) { |a,b| a.length > b.length })
        assert_equal("apelsin", find_it(["apelsin", "bananer", "citron"]) { |a,b| a.length > b.length }) #samma längd, sparar första värdet
        assert_not_equal("apelsin", find_it(["apelsin", "bananer", "citroner"]) { |a,b| a.length > b.length })
    end

    def test_uppgift3_Integer
        assert_equal(2,0.fib(3))
        assert_equal(8,1.fib(6))
        assert_not_equal(2, 2.fib(2))
        assert_raise do 
            a.fib(2)
          end
        assert_raise do 
            1.fib("hej")
          end  
    end

    def test_uppgift4_Array
        assert_equal([2,3,1], [1,2,3].rotate_left)
        assert_not_equal([3,1,2], [1,2,3].rotate_left)
        assert_equal([3,1,2], [1,2,3].rotate_left(-1))
        assert_equal([4,1,2,3], [1,2,3,4].rotate_left(3))
        assert_raise do 
            [1,2,3,4].rotate_left("three")
        end  
    end

    def test_uppgift5_Tag_names
        require 'open-uri.rb'
        html = URI.open("http://www.google.com/") { |f| f.read }

        assert_equal([["head"], ["title"], ["style"],
                    ["nobr"], ["u"], ["center"], ["br"]],
                    tag_names(html))
        assert_match(/[<]([a-zA-Z]{1,})[>]/, "<title>")
        assert_not_match(/[<]([a-zA-Z]{1,})[>]/, "title")
        assert_raise do
            tag_names(10)
        end
    end

    def test_uppgift6_regnr
        assert_equal("ABC123", regnr("Min bil heter ABC123"))
        assert_equal("MBW983", regnr("MBW983"))
        assert_equal("false", regnr("Min bil har QWE234"))
        assert_raise do
            regnr(ABC123)
        end
    end

    def test_uppgift7_count
        new_file = File.open("uppgift7.txt", "r")
        text = File.read(new_file)
        
        assert_equal("och 2", count(text, "och"))
        assert_equal("no match", count(text, 3))
        assert_equal("no match", count(text,["hej"]))
        assert_equal("no match", count(text, 0.3))

    end
  end
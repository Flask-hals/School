#!/bin/env ruby

require './sem1.rb'
require 'test/unit'

class TestFirst < Test::Unit::TestCase
    def test_n_times
        assert_equal(3, n_times(3) { puts "Hello!" })
        assert_not_equal(2, n_times(3) { puts "Hello!" })
    end

    def test_repeat
        res = Repeat.new(3)
        assert_equal(3, res.each { puts "Hooray!" })
        assert_not_equal(2, res.each { puts "Hooray!" })
    end

    def test_find_it
        assert_equal("banan", find_it(["apelsin", "banan", "citron"]) { |a,b| a.length < b.length })
        assert_equal("apelsin", find_it(["apelsin", "banan", "citron"]) { |a,b| a.length > b.length })
        assert_equal(nil, find_it([]) { |a,b| a.length > b.length })
    end
end

class TestSecond < Test::Unit::TestCase
    def test_fib
        assert_equal(4181, 19.fib)
        assert_equal(0, 0.fib)
        assert_equal(1, 1.fib)
        assert_equal(1, 2.fib)
        assert_equal(0, (-1).fib)
    end

    def test_rotate_left
        assert_equal([2,3,1], [1,2,3].rotate_left(1))
        assert_equal([3,1,2], [1,2,3].rotate_left(2))
        assert_equal([1,2,3], [1,2,3].rotate_left(3))
        assert_equal([], [].rotate_left(10))
    end
end

class TestThird < Test::Unit::TestCase
    def test_tag_names
        assert_equal([["html"], ["a"]], tag_names("<html class = test>asd</html><a></a><a>"))
        assert_equal([["html"], ["head"], ["a"]], tag_names("<html> <head> hej <a>"))
        assert_equal([["html"], ["a"]], tag_names("<html> <22> hej <a>"))
        assert_equal([], tag_names("html <22> hej <55>"))
    end

    def test_regnr
        assert_equal("FMA123", regnr("FMA123"))
        assert_equal("FMA123", regnr("Mitt regnr. är FMA123"))
        assert_false(regnr("FFFMA123"))
        assert_false(regnr("FMA123333"))
        assert_false(regnr("FMA123333"))
        assert_false(regnr(""))
    end
end

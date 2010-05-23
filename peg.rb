module Peg
  class Result
    attr_accessor :status, :rest

    def initialize(status, rest)
      @status, @rest = status, rest
    end
  end

  class ParsingExpression
  end

  class Sequence < ParsingExpression
  end

  class ParsingExpression
    def parse(str)
      raise NotImplementedError
    end

    def >>(other)
      Sequence.new(self, other)
    end

    def /(other)
      OrderedChoice.new(self, other)
    end

    def zero_or_more
      ZeroOrMore.new(self)
    end

    def one_or_more
      OneOrMore.new(self)
    end
    alias :+@ :one_or_more

    def optional
      Optional.new(self)
    end
    alias :-@ :optional
  end

  class Any < ParsingExpression
    def inspect
      '.'
    end

    def parse(str)
      if str.empty?
        Result.new(false, str)
      else
        Result.new(true, str[1 .. -1])
      end
    end
  end

  class Char < ParsingExpression
    def initialize(char)
      @char = char
    end

    def inspect
      "'#{@char}'"
    end

    def parse(str)
      if (not str.empty?) and str[0, 1] == @char
        Result.new(true, str[1 .. -1])
      else
        Result.new(false, str)
      end
    end
  end

  class Range < ParsingExpression
    def initialize(first, last)
      @first, @last = first, last
    end

    def inspect
      "[#{@first}-#{@last}]"
    end

    def parse(str)
      if !str.empty? and str[0, 1] >= @first and str[0, 1] <= @last
        Result.new(true, str[1 .. -1])
      else
        Result.new(false, str)
      end
    end
  end

  class Sequence < ParsingExpression
    def initialize(lhs, rhs)
      @lhs, @rhs = lhs, rhs
    end

    def inspect
      "#{@lhs.inspect} #{@rhs.inspect}"
    end

    def parse(src)
      result = @lhs.parse(src)
      if result.status
        result = @rhs.parse(result.rest)
        return result if result.status
      end
      Result.new(false, src)
    end
  end

  class OrderedChoice < ParsingExpression
    def initialize(lhs, rhs)
      @lhs, @rhs = lhs, rhs
    end

    def inspect
      "#{@lhs.inspect} / #{@rhs.inspect}"
    end

    def parse(src)
      result = @lhs.parse(src)
      if !result.status
        result = @rhs.parse(result.rest)
      end
      result
    end
  end

  class ZeroOrMore < ParsingExpression
    def initialize(pe)
      @pe = pe
    end

    def inspect
      "#{@pe.inspect}*"
    end

    def parse(src)
      result = @pe.parse(src)
      while !result.rest.empty? and result.status
        result = @pe.parse(result.rest)
      end
      result.status = true
      result
    end
  end

  class OneOrMore < ParsingExpression
    def initialize(pe)
      @pe = pe
    end

    def inspect
      "#{@pe.inspect}+"
    end

    def parse(src)
      result = @pe.parse(src)
      return result unless result.status
      while !result.rest.empty? and result.status
        result = @pe.parse(result.rest)
      end
      result.status = true
      result
    end
  end

  class Optional < ParsingExpression
    def initialize(pe)
      @pe = pe
    end

    def inspect
      "#{@pe.inspect}?"
    end

    def parse(src)
      result = @pe.parse(src)
      result.status = true
      result
    end
  end

  class AndPredicate < ParsingExpression
    def initialize(pe)
      @pe = pe
    end

    def inspect
      "&#{@pe.inspect}"
    end

    def parse(src)
      result = @pe.parse(src)
      result.rest = src
      result
    end
  end

  class NotPredicate < ParsingExpression
    def initialize(pe)
      @pe = pe
    end

    def inspect
      "!#{@pe.inspect}"
    end

    def parse(src)
      result = @pe.parse(src)
      result.status = !result.status
      result.rest = src
      result
    end
  end

  def any
    @any ||= Any.new
  end
  module_function :any

  def char(ch)
    (@char = {})[ch] ||= Char.new(ch)
  end
  module_function :char

  def str(s)
    (@str = {})[s] ||= String.new(s)
  end
  module_function :str

  def range(first, last)
    (@range ||= {})[[first, last]] ||= Range.new(first, last)
  end
  module_function :range

  def optional(pe)
    Optional.new(pe)
  end
  module_function :optional

  def and(pe)
    AndPredicate.new(pe)
  end
  module_function :and

  def not(pe)
    NotPredicate.new(pe)
  end
  module_function :not
end

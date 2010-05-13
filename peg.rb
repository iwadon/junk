module Peg
  class Result
    attr_reader :status, :rest

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

  def any
    @any ||= Any.new
  end
  module_function :any

  def char(char)
    (@char = {})[char] ||= Char.new(char)
  end
  module_function :char

  def range(first, last)
    (@range ||= {})[[first, last]] ||= Range.new(first, last)
  end
  module_function :range
end

require 'test/unit'
require './peg'

class PegTest < Test::Unit::TestCase
  def test_inspect
    # any
    assert_equal(".", Peg::any.inspect())

    # char
    assert_equal("'a'", Peg::char("a").inspect())

    # range
    assert_equal("[a-z]", Peg::range("a", "z").inspect())

    # sequence
    assert_equal("'a' 'b'", (Peg::char("a") >> Peg::char("b")).inspect())
  end

  def peg_assert(obj, src, status, match, rest)
    result = obj.parse(src)
    assert_equal(rest, result.rest)
    assert_equal(status, result.status)
  end

  def test_parse
    # any
    peg_assert(Peg::any, "foo", true, "f", "oo")

    # char
    peg_assert(Peg::char("a"), "abc", true, "a", "bc")
    peg_assert(Peg::char("o"), "foo", false, "", "foo")

    # range
    peg_assert(Peg::range("0", "9"), "123", true, "1", "23")

    # sequence
    peg_assert(Peg::char("f") >> Peg::char("o"), "foo", true, "fo", "o")
  end
end

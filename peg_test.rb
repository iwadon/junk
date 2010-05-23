require 'test/unit'
require 'peg'

class PegTest < Test::Unit::TestCase
  def test_inspect
    # any
    assert_equal(".", Peg::any.inspect)

    # char
    assert_equal("'a'", Peg::char("a").inspect)

    # string
    assert_equal('"abc"', Peg::str("abc").inspect)

    # range
    assert_equal("[a-z]", Peg::range("a", "z").inspect)

    # sequence
    assert_equal("'a' 'b'", (Peg::char("a") >> Peg::char("b")).inspect)

    # ordered choice
    assert_equal("'a' / 'b'", (Peg::char("a") / Peg::char("b")).inspect)

    # zero-or-more
    #assert_equal("'a'*", (*Peg::char("a")).inspect)
    assert_equal("'a'*", (Peg::char("a").zero_or_more).inspect)

    # one-or-more
    assert_equal("'a'+", (+Peg::char("a")).inspect)
    assert_equal("'a'+", (Peg::char("a").one_or_more).inspect)

    # optional
    assert_equal("'a'\?", (-Peg::char("a")).inspect)
    assert_equal("'a'\?", (Peg::optional(Peg::char("a"))).inspect)

    # and-predicate
    assert_equal("&'a'", (Peg::and(Peg::char("a"))).inspect)

    # not-predicate
    assert_equal("!'a'", (Peg::not(Peg::char("a"))).inspect)

    # rule
    a_or_b = Peg::char("a") / Peg::char("b")
    assert_equal("'a' / 'b'", a_or_b.inspect)
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

    # sequence
    peg_assert(Peg::char("f") / Peg::char("b"), "foo", true, "f", "oo")
    peg_assert(Peg::char("f") / Peg::char("b"), "bar", true, "b", "ar")
    peg_assert(Peg::char("a") / Peg::char("z"), "baz", false, "", "baz")
    peg_assert((Peg::char("a") >> Peg::char("b")) / (Peg::char("a") >> Peg::char("c")), "abc", true, "ab", "c")
    peg_assert((Peg::char("a") >> Peg::char("b")) / (Peg::char("a") >> Peg::char("c")), "acd", true, "ac", "d")

    # zero-or-more
    peg_assert(Peg::char("a").zero_or_more, "aabbcc", true, "aa", "bbcc")
    peg_assert(Peg::char("a").zero_or_more, "bbccdd", true, "", "bbccdd")

    # one-or-more
    peg_assert(Peg::char("a").one_or_more, "aabbcc", true, "aa", "bbcc")
    peg_assert(Peg::char("a").one_or_more, "bbccdd", false, "", "bbccdd")
    peg_assert(+Peg::char("a"), "aabbcc", true, "aa", "bbcc")
    peg_assert(+Peg::char("a"), "bbccdd", false, "", "bbccdd")

    # optional
    peg_assert(Peg::char("a").optional, "aaa", true, "a", "aa")
    peg_assert(Peg::char("a").optional, "bbb", true, "", "bbb")
    peg_assert((Peg::char("a") >> Peg::char("b")).optional, "acd", true, "", "acd")
    peg_assert(-Peg::char("a"), "aaa", true, "a", "aa")
    peg_assert(-Peg::char("a"), "bbb", true, "", "bbb")
    peg_assert(-(Peg::char("a") >> Peg::char("b")), "acd", true, "", "acd")

    # and predicate
    peg_assert(Peg::and(Peg::char("a")) >> Peg::any.one_or_more, "abc", true, "abc", "")
    peg_assert(Peg::and(Peg::char("a")) >> Peg::any.one_or_more, "cba", false, "", "cba")

    # not predicate
    peg_assert(Peg::not(Peg::char("a")) >> Peg::any.one_or_more, "abc", false, "", "abc")
    peg_assert(Peg::not(Peg::char("a")) >> Peg::any.one_or_more, "cba", true, "cba", "")
  end
end

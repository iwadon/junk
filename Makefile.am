AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libsequencer.a

libsequencer_a_SOURCES = peg.cpp peg.hpp \
			 variable_length_value.cpp variable_length_value.hpp \
			 volume.hpp
libsequencer_a_CPPFLAGS = $(BOOST_CPPFLAGS)

check_PROGRAMS = sequencer_test
TESTS = $(check_PROGRAMS)

sequencer_test_SOURCES = test_main.cpp function_test.cpp peg_test.cpp variable_length_value_test.cpp volume_test.cpp
sequencer_test_CPPFLAGS = $(CPPUNIT_CFLAGS) $(BOOST_CPPFLAGS)
sequencer_test_LDFLAGS = libsequencer.a $(CPPUNIT_LIBS)

AM_CXXFLAGS = -Wall -O2 -g

gcov: check
	gcov -l -p *.gcda

gcov-clean:
	rm -f *.gcda *.gcno *.gcov

AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = s2

lib_LIBRARIES = libsequencer.a

libsequencer_a_SOURCES = peg.cpp peg.hpp \
			 variable_length_value.cpp variable_length_value.hpp \
			 volume.hpp
libsequencer_a_CPPFLAGS = $(BOOST_CPPFLAGS)

check_PROGRAMS = sequencer_test point_test vector_test
TESTS = $(check_PROGRAMS) peg_test.sh

sequencer_test_SOURCES = test_main.cpp function_test.cpp peg_test.cpp variable_length_value_test.cpp volume_test.cpp
sequencer_test_CPPFLAGS = $(CPPUNIT_CFLAGS) $(BOOST_CPPFLAGS)
sequencer_test_LDADD = libsequencer.a $(CPPUNIT_LIBS)

s2_SOURCES = s2.cpp
s2_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
s2_LDADD = $(SDL_LIBS) $(BOOST_LIBS)

point_test_SOURCES = test_main.cpp point_test.cpp
point_test_CPPFLAGS = $(CPPUNIT_CFLAGS)
point_test_LDADD = $(CPPUNIT_LIBS)

vector_test_SOURCES = test_main.cpp vector_test.cpp
vector_test_CPPFLAGS = $(CPPUNIT_CFLAGS)
vector_test_LDADD = $(CPPUNIT_LIBS)

AM_CXXFLAGS = -Wall -O2 -g

gcov: check
	gcov -l -p *.gcda

gcov-clean:
	rm -f *.gcda *.gcno *.gcov

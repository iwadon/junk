AUTOMAKE_OPTIONS = foreign

#bin_PROGRAMS = oscillator_sample s2
bin_PROGRAMS = s2

#oscillator_sample_SOURCES = oscillator_sample.cpp
#oscillator_sample_CPPFLAGS = $(SDL_CFLAGS)
#oscillator_sample_LDADD = libsequencer.a $(SDL_LIBS)

s2_SOURCES = s2.cpp
s2_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
s2_LDADD = $(SDL_LIBS) $(BOOST_LIBS)

lib_LIBRARIES = libpeg.a libsequencer.a

libpeg_a_SOURCES = peg.cpp peg.hpp
libpeg_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libsequencer_a_SOURCES = oscillator.cpp oscillator.hpp \
			 smf_track.cpp smf_track.hpp \
			 variable_length_value.cpp variable_length_value.hpp \
			 volume.hpp
libsequencer_a_CPPFLAGS = $(BOOST_CPPFLAGS)

check_PROGRAMS = peg_test \
		 point_test \
		 sequencer_test \
		 vector_test
TESTS = $(check_PROGRAMS) peg_test.sh

peg_test_SOURCES = test_main.cpp \
		   peg_test.cpp
peg_test_CPPFLAGS = $(CPPUNIT_CFLAGS)
peg_test_LDADD = libpeg.a $(CPPUNIT_LIBS)

sequencer_test_SOURCES = test_main.cpp \
			 function_test.cpp \
			 oscillator_test.cpp \
			 smf_track_test.cpp \
			 variable_length_value_test.cpp \
			 volume_test.cpp
sequencer_test_CPPFLAGS = $(CPPUNIT_CFLAGS) $(BOOST_CPPFLAGS)
sequencer_test_LDADD = libsequencer.a $(CPPUNIT_LIBS)

point_test_SOURCES = test_main.cpp point_test.cpp
point_test_CPPFLAGS = $(CPPUNIT_CFLAGS)
point_test_LDADD = $(CPPUNIT_LIBS)

vector_test_SOURCES = test_main.cpp vector_test.cpp
vector_test_CPPFLAGS = $(CPPUNIT_CFLAGS)
vector_test_LDADD = $(CPPUNIT_LIBS)

AM_CXXFLAGS = -Wall -Wextra

gcov: check
	gcov -l -p *.gcda

gcov-clean:
	rm -f *.gcda *.gcno *.gcov

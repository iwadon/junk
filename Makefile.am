AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = oscillator_sample s2

oscillator_sample_SOURCES = oscillator_sample.cpp
oscillator_sample_CPPFLAGS = $(SDL_CFLAGS)
oscillator_sample_LDADD = libsdlapp.a $(SDL_LIBS)

s2_SOURCES = s2.cpp
s2_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
s2_LDADD = libsdlapp.a $(SDL_LIBS) $(BOOST_LIBS)

lib_LIBRARIES = libpeg.a libsdlapp.a libsequencer.a

libpeg_a_SOURCES = peg.cpp peg.hpp
libpeg_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libsdlapp_a_SOURCES = font.cpp font.hpp \
		      fps.cpp fps.hpp \
		      sdl_app.cpp sdl_app.hpp \
		      texture.cpp texture.hpp \
		      texture_pool.cpp texture_pool.hpp
libsdlapp_a_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)

libsequencer_a_SOURCES = oscillator.cpp oscillator.hpp \
			 smf_track.cpp smf_track.hpp \
			 variable_length_value.cpp variable_length_value.hpp \
			 volume.hpp
libsequencer_a_CPPFLAGS = $(BOOST_CPPFLAGS)

check_PROGRAMS = peg_test \
		 point_test \
		 sequencer_test \
		 sdlapp_test \
		 vector_test
TESTS = $(check_PROGRAMS) peg_test.sh

peg_test_SOURCES = test_main.cpp \
		   peg_test.cpp
peg_test_CPPFLAGS = $(CPPUNIT_CFLAGS)
peg_test_LDADD = libpeg.a $(CPPUNIT_LIBS)

sdlapp_test_SOURCES = test_main.cpp \
		      font_test.cpp \
		      fps_test.cpp \
		      texture_test.cpp \
		      texture_pool_test.cpp
sdlapp_test_CPPFLAGS = $(CPPUNIT_CFLAGS) $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
sdlapp_test_LDADD = libsdlapp.a $(CPPUNIT_LIBS) $(BOOST_LIBS)

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

all-local:
	test -d $(builddir)/data || ln -s $(top_srcdir)/data $(builddir)/

distclean-local:
	test ! -L $(builddir)/data || rm $(builddir)/data

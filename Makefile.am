AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = oscillator_sample c1 s1 s2

c1_SOURCES = c1.cpp

oscillator_sample_SOURCES = oscillator_sample.cpp
oscillator_sample_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
oscillator_sample_LDFLAGS = -framework OpenGL
oscillator_sample_LDADD = libsdlapp.a $(SDL_LIBS) $(BOOST_LIBS)

s1_SOURCES = s1.cpp

s2_SOURCES = s2.cpp
s2_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
s2_LDFLAGS = -framework OpenGL
s2_LDADD = libsdlapp.a $(SDL_LIBS) $(BOOST_LIBS)

lib_LIBRARIES = libpeg.a libsdlapp.a libsequencer.a

libpeg_a_SOURCES = peg.cpp peg.hpp
libpeg_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libsdlapp_a_SOURCES = font.cpp font.hpp \
		      fps.cpp fps.hpp \
		      logger.cpp logger.hpp \
		      sdl_app.cpp sdl_app.hpp \
		      sprite.cpp sprite.hpp \
		      texture.cpp texture.hpp \
		      texture_pool.cpp texture_pool.hpp
libsdlapp_a_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)

libsequencer_a_SOURCES = oscillator.cpp oscillator.hpp \
			 smf_track.cpp smf_track.hpp \
			 variable_length_value.cpp variable_length_value.hpp \
			 volume.hpp
libsequencer_a_CPPFLAGS = $(BOOST_CPPFLAGS)

check_PROGRAMS = logger_test \
		 peg_test \
		 point_test \
		 sequencer_test \
		 sdlapp_test \
		 vector_test
TESTS = $(check_PROGRAMS) peg_test.sh

logger_test_SOURCES = test_main.cpp \
		      logger_test.cpp
logger_test_CPPFLAGS = $(CPPUNIT_CFLAGS) $(BOOST_CPPFLAGS)
logger_test_LDADD = libsdlapp.a $(CPPUNIT_LIBS) $(BOOST_LIBS)

peg_test_SOURCES = test_main.cpp \
		   peg_test.cpp
peg_test_CPPFLAGS = $(CPPUNIT_CFLAGS)
peg_test_LDADD = libpeg.a $(CPPUNIT_LIBS)

sdlapp_test_SOURCES = test_main.cpp \
		      font_test.cpp \
		      fps_test.cpp \
		      sprite_test.cpp \
		      texture_test.cpp \
		      texture_pool_test.cpp
sdlapp_test_CPPFLAGS = $(CPPUNIT_CFLAGS) $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
sdlapp_test_LDFLAGS = -framework OpenGL
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

AM_CFLAGS = -Wall -Wextra $(COVERAGE_CFLAGS)
AM_CXXFLAGS = -Wall -Wextra $(COVERAGE_CXXFLAGS)

OBJECTS = $(c1_OBJECTS) \
	  $(libpeg_a_OBJECTS) \
	  $(libsdlapp_a_OBJECTS) \
	  $(libsequencer_a_OBJECTS) \
	  $(logger_test_OBJECTS) \
	  $(oscillator_sample_OBJECTS) \
	  $(peg_test_OBJECTS) \
	  $(point_test_OBJECTS) \
	  $(s1_OBJECTS) \
	  $(s2_OBJECTS) \
	  $(sdlapp_test_OBJECTS) \
	  $(sequencer_test_OBJECTS) \
	  $(vector_test_OBJECTS)

TEST_OBJECTS = $(libpeg_a_OBJECTS) \
	  $(libsdlapp_a_OBJECTS) \
	  $(libsequencer_a_OBJECTS) \
	  $(logger_test_OBJECTS) \
	  $(peg_test_OBJECTS) \
	  $(point_test_OBJECTS) \
	  $(sdlapp_test_OBJECTS) \
	  $(sequencer_test_OBJECTS) \
	  $(vector_test_OBJECTS)

CLEANFILES = $(OBJECTS:.o=.gcda)
DISTCLEANFILES = $(OBJECTS:.o=.gcno) app.info

GCOV = gcov -l -p
LCOV = lcov
GENHTML = genhtml
lcovdir = $(builddir)/lcov

gcov: check
	$(GCOV) $(TEST_OBJECTS:.o=.gcda)

.PHONY: lcov
lcov:
	$(LCOV) -z -d $(srcdir)
	$(MAKE) check
	$(LCOV) -c -d $(srcdir) -o $(builddir)/app.info
	$(GENHTML) --demangle-cpp --html-prolog $(srcdir)/lcov_prolog.html --html-epilog $(srcdir)/lcov_epilog.html -o $(lcovdir) $(builddir)/app.info -p $(abs_srcdir)

all-local:
	test -d $(builddir)/data || ln -s $(top_srcdir)/data $(builddir)/

distclean-local:
	test ! -L $(builddir)/data || rm $(builddir)/data
	test ! -d $(lcovdir) || rm -r $(lcovdir)

DOXYFILE = $(builddir)/Doxyfile

.PHONY: dox clean-dox
dox: $(DOXYFILE)
	test -d $(builddir)/dox || $(MKDIR_P) $(builddir)/dox
	$(DOXYGEN) $(DOXYFILE)
clean-dox:
	rm -rf $(builddir)/dox

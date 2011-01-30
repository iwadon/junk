AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = oscillator_sample c1 s1 s2 smf_play

c1_SOURCES = c1.cpp

oscillator_sample_SOURCES = oscillator_sample.cpp
oscillator_sample_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
oscillator_sample_LDFLAGS = -framework OpenGL
oscillator_sample_LDADD = libsequencer.a libsdlapp.a liblogger.a $(SDL_LIBS) $(BOOST_LIBS)

s1_SOURCES = s1.cpp

s2_SOURCES = s2.cpp
s2_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
s2_LDFLAGS = -framework OpenGL
s2_LDADD = libsdlapp.a liblogger.a $(SDL_LIBS) $(BOOST_LIBS)

#smf_dump_SOURCES = smf_dump.cpp
#smf_dump_CPPFLAGS = $(BOOST_CPPFLAGS)
#smf_dump_LDADD = libsequencer.a liblogger.a $(BOOST_LIBS)

smf_play_SOURCES = smf_play.cpp
smf_play_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
smf_play_LDADD = libsequencer.a libsdlapp.a liblogger.a $(SDL_LIBS) $(BOOST_LIBS)

lib_LIBRARIES = liblogger.a libpeg.a libsdlapp.a libsequencer.a libtest_main.a

liblogger_a_SOURCES = logger.cpp logger.hpp
liblogger_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libpeg_a_SOURCES = peg.cpp peg.hpp
libpeg_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libsdlapp_a_SOURCES = controller.cpp controller.hpp \
		      frame_wait_timer.cpp frame_wait_timer.hpp \
		      font.cpp font.hpp \
		      fps.cpp fps.hpp \
		      sdl_app.cpp sdl_app.hpp \
		      sprite.cpp sprite.hpp \
		      texture.cpp texture.hpp \
		      texture_pool.cpp texture_pool.hpp
libsdlapp_a_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)

libsequencer_a_SOURCES = audio_stream.hpp \
			 channel.cpp channel.hpp \
			 filter.cpp filter.hpp \
			 instrument.cpp instrument.hpp \
			 oscillator.cpp oscillator.hpp \
			 oscillator_factory.cpp oscillator_factory.hpp \
			 oscillator_stream.cpp oscillator_stream.hpp \
			 patch.cpp patch.hpp \
			 pseudo_triangle_wave_oscillator.cpp pseudo_triangle_wave_oscillator.hpp \
			 sampler.cpp sampler.hpp \
			 sine_wave_oscillator.cpp sine_wave_oscillator.hpp \
			 triangle_wave_oscillator.cpp triangle_wave_oscillator.hpp \
			 smf.cpp smf.hpp \
			 smf_track.cpp smf_track.hpp \
			 variable_length_value.cpp variable_length_value.hpp \
			 voice.cpp voice.hpp \
			 volume.hpp
libsequencer_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libtest_main_a_SOURCES = test_main.cpp
libtest_main_a_CPPFLAGS = $(CPPUNIT_CFLAGS) $(BOOST_CPPFLAGS)
libtest_main_a_LIBADD = liblogger.a

check_PROGRAMS = logger_test \
		 lot_box_test \
		 oscillator_stream_test \
		 peg_test \
		 point_test \
		 sequencer_test \
		 sdlapp_test \
		 vector_test
TESTS = $(check_PROGRAMS) peg_test.sh
TEST_CPPFLAGS = $(CPPUNIT_CFLAGS) $(BOOST_CPPFLAGS)
TEST_LIBS = libtest_main.a liblogger.a $(CPPUNIT_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB)

oscillator_stream_test_SOURCES = oscillator_stream_test.cpp
oscillator_stream_test_CPPFLAGS = $(TEST_CPPFLAGS)
oscillator_stream_test_LDADD = libsequencer.a $(TEST_LIBS)

logger_test_SOURCES = logger_test.cpp
logger_test_CPPFLAGS = $(TEST_CPPFLAGS)
logger_test_LDADD = $(TEST_LIBS)

lot_box_test_SOURCES = lot_box_test.cpp
lot_box_test_CPPFLAGS = $(TEST_CPPFLAGS)
lot_box_test_LDADD = $(TEST_LIBS)

peg_test_SOURCES = peg_test.cpp
peg_test_CPPFLAGS = $(TEST_CPPFLAGS)
peg_test_LDADD = libpeg.a $(TEST_LIBS)

sdlapp_test_SOURCES = font_test.cpp \
		      fps_test.cpp \
		      object_test.cpp \
		      sprite_test.cpp \
		      texture_test.cpp \
		      texture_pool_test.cpp
sdlapp_test_CPPFLAGS = $(SDL_CFLAGS) $(TEST_CPPFLAGS)
sdlapp_test_LDFLAGS = -framework OpenGL
sdlapp_test_LDADD = libsdlapp.a $(TEST_LIBS)

sequencer_test_SOURCES = audio_stream_test.cpp \
			 channel_test.cpp \
			 filter_test.cpp \
			 function_test.cpp \
			 instrument_test.cpp \
			 observer_test.cpp \
			 oscillator_test.cpp \
			 oscillator_factory_test.cpp \
			 patch_test.cpp \
			 pseudo_triangle_wave_oscillator_test.cpp \
			 sampler_test.cpp \
			 sine_wave_oscillator_test.cpp \
			 smf_test.cpp \
			 smf_track_test.cpp \
			 triangle_wave_oscillator_test.cpp \
			 variable_length_value_test.cpp \
			 voice_test.cpp \
			 volume_test.cpp
sequencer_test_CPPFLAGS = $(TEST_CPPFLAGS)
sequencer_test_LDADD = libsequencer.a $(TEST_LIBS)

point_test_SOURCES = point_test.cpp
point_test_CPPFLAGS = $(TEST_CPPFLAGS)
point_test_LDADD = $(TEST_LIBS)

vector_test_SOURCES = vector_test.cpp
vector_test_CPPFLAGS = $(TEST_CPPFLAGS)
vector_test_LDADD = $(TEST_LIBS)

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

CLEANFILES = $(OBJECTS:.o=.gcda) \
	     dox-warning.txt
DISTCLEANFILES = $(OBJECTS:.o=.gcno) app.info

GCOV = gcov -l -p
LCOV = lcov
GENHTML = genhtml
lcovdir = $(builddir)/lcov
DOXYFILE = $(builddir)/Doxyfile
doxdir = $(builddir)/dox

gcov: check
	$(GCOV) $(TEST_OBJECTS:.o=.gcda)

.PHONY: lcov
lcov:
	$(LCOV) -z -d $(srcdir)
	$(MAKE) check
	$(LCOV) -c -d $(srcdir) -o $(builddir)/app.info
	$(LCOV) -r $(builddir)/app.info "*/boost/*" -o $(builddir)/app.info
	$(LCOV) -r $(builddir)/app.info "*/cppunit/*" -o $(builddir)/app.info
	$(LCOV) -r $(builddir)/app.info "*/include/*" -o $(builddir)/app.info
	$(GENHTML) --demangle-cpp --html-prolog $(srcdir)/lcov_prolog.html --html-epilog $(srcdir)/lcov_epilog.html -o $(lcovdir) $(builddir)/app.info -p $(abs_srcdir)

all-local:
	test -d $(builddir)/data || ln -s $(top_srcdir)/data $(builddir)/

distclean-local:
	test ! -L $(builddir)/data || rm $(builddir)/data
	test ! -d $(lcovdir) || rm -r $(lcovdir)
	test ! -d $(doxdir) || rm -r $(doxdir)

.PHONY: dox clean-dox
dox: $(DOXYFILE)
	(test -d $(doxdir) || $(MKDIR_P) $(doxdir)) && $(DOXYGEN) $(DOXYFILE)
clean-dox:
	rm -r $(doxdir)

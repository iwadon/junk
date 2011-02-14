AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = benchmark_sample \
	       c1 \
	       map_benchmark \
	       oscillator_sample \
	       pcap_sample \
	       s1 \
	       s2 \
	       sdl_event_sample \
	       sdl_event_sample2 \
	       smf_play \
	       vector_length_benchmark

benchmark_sample_SOURCES = benchmark_sample.cpp
benchmark_sample_CPPFLAGS = $(BOOST_CPPFLAGS)

c1_SOURCES = c1.cpp

map_benchmark_SOURCES = map_benchmark.cpp
map_benchmark_CPPFLAGS = $(BOOST_CPPFLAGS)

oscillator_sample_SOURCES = oscillator_sample.cpp
oscillator_sample_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
oscillator_sample_LDFLAGS = -framework OpenGL
oscillator_sample_LDADD = libsequencer.a libsdlapp.a liblogger.a $(SDL_LIBS)

pcap_sample_SOURCES = pcap_sample.cpp

s1_SOURCES = s1.cpp

s2_SOURCES = s2.cpp
s2_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
s2_LDFLAGS = -framework OpenGL
s2_LDADD = libsdlapp.a liblogger.a $(SDL_LIBS)

sdl_event_sample_SOURCES = sdl_event_sample.c
sdl_event_sample_CPPFLAGS = $(SDL_CFLAGS)
sdl_event_sample_LDADD = $(SDL_LIBS)

sdl_event_sample2_SOURCES = sdl_event_sample2.m
#sdl_event_sample2_OBJCFLAGS = -framework Cocoa
sdl_event_sample2_CPPFLAGS = $(SDL_CFLAGS)
sdl_event_sample2_LDFLAGS = -framework Cocoa
sdl_event_sample2_LDADD = $(SDL_LIBS)

#smf_dump_SOURCES = smf_dump.cpp
#smf_dump_CPPFLAGS = $(BOOST_CPPFLAGS)
#smf_dump_LDADD = libsequencer.a liblogger.a

smf_play_SOURCES = smf_play.cpp
smf_play_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
smf_play_LDADD = libsequencer.a libsdlapp.a liblogger.a $(SDL_LIBS)

lib_LIBRARIES = liblogger.a libpeg.a libsdlapp.a libsequencer.a libtest_main.a

liblogger_a_SOURCES = logger.cpp logger.hpp
liblogger_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libpeg_a_SOURCES = peg.cpp peg.hpp
libpeg_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libsdlapp_a_SOURCES = controller.cpp controller.hpp \
		      frame_wait_timer.cpp frame_wait_timer.hpp \
		      font.cpp font.hpp \
		      fps.cpp fps.hpp \
		      load_time.cpp load_time.hpp \
		      sdl_app.cpp sdl_app.hpp \
		      sprite.cpp sprite.hpp \
		      texture.cpp texture.hpp \
		      texture_pool.cpp texture_pool.hpp
libsdlapp_a_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)

libsequencer_a_SOURCES = audio_stream.hpp \
			 channel.cpp channel.hpp \
			 circular_buffer.hpp \
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
libsequencer_a_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)

libtest_main_a_SOURCES = test_main.cpp
libtest_main_a_CPPFLAGS = $(CPPUNIT_CFLAGS) $(BOOST_CPPFLAGS)
libtest_main_a_LIBADD = liblogger.a

vector_length_benchmark_SOURCES = vector_length_benchmark.cpp
vector_length_benchmark_CPPFLAGS = $(BOOST_CPPFLAGS)

check_PROGRAMS = all_tests
TESTS = $(check_PROGRAMS) peg_test.sh

all_tests_SOURCES = \
	audio_stream_test.cpp \
	channel_test.cpp \
	circular_buffer_test.cpp \
	filter_test.cpp \
	font_test.cpp \
	fps_test.cpp \
	function_test.cpp \
	instrument_test.cpp \
	load_time_test.cpp \
	logger_test.cpp \
	lot_box_test.cpp \
	object_test.cpp \
	observer_test.cpp \
	oscillator_factory_test.cpp \
	oscillator_stream_test.cpp \
	oscillator_test.cpp \
	patch_test.cpp \
	peg_test.cpp \
	point_2d_test.cpp \
	pseudo_triangle_wave_oscillator_test.cpp \
	rect_test.cpp \
	sampler_test.cpp \
	sine_wave_oscillator_test.cpp \
	smf_test.cpp \
	smf_track_test.cpp \
	sprite_test.cpp \
	texture_pool_test.cpp \
	texture_test.cpp \
	triangle_wave_oscillator_test.cpp \
	variable_length_value_test.cpp \
	vector_2d_test.cpp \
	voice_test.cpp \
	volume_test.cpp
all_tests_CPPFLAGS = $(CPPUNIT_CFLAGS) $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
all_tests_LDFLAGS = -framework OpenGL
all_tests_LDADD = libpeg.a libsdlapp.a libsequencer.a libtest_main.a liblogger.a $(CPPUNIT_LIBS) $(SDL_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB)

AM_CFLAGS = -Wall -Wextra $(COVERAGE_CFLAGS)
AM_CXXFLAGS = -Wall -Wextra $(COVERAGE_CXXFLAGS)
AM_OBJCFLAGS = -Wall -Wextra $(COVERAGE_OBJCFLAGS)

OBJECTS = $(all_tests_OBJECTS) \
	  $(benchmark_sample_OBJECTS) \
	  $(c1_OBJECTS) \
	  $(liblogger_a_OBJECTS) \
	  $(libpeg_a_OBJECTS) \
	  $(libsdlapp_a_OBJECTS) \
	  $(libsequencer_a_OBJECTS) \
	  $(libtest_main_a_OBJECTS) \
	  $(map_benchmark_OBJECTS) \
	  $(oscillator_sample_OBJECTS) \
	  $(s1_OBJECTS) \
	  $(s2_OBJECTS) \
	  $(smf_play_OBJECTS) \
	  $(vector_length_benchmark_OBJECTS)

TEST_OBJECTS = $(all_tests_OBJECTS) \
	  $(liblogger_a_OBJECTS) \
	  $(libpeg_a_OBJECTS) \
	  $(libsdlapp_a_OBJECTS) \
	  $(libsequencer_a_OBJECTS) \
	  $(libtest_main_a_OBJECTS)

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

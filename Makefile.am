AUTOMAKE_OPTIONS = foreign

noinst_PROGRAMS = benchmark_sample \
	boost_program_options_sample \
	c1 \
	g1 \
	line_segment_2d_benchmark \
	map_benchmark \
	observer_benchmark \
	oscillator_sample \
	pcap_sample \
	peg_sample \
	peg_sample2 \
	s1 \
	s2 \
	sdl_event_sample \
	sdl_event_sample2 \
	sdl_opengl_sample \
	smf_play \
	udp_sample \
	vector_length_benchmark

benchmark_sample_SOURCES = benchmark_sample.cpp
benchmark_sample_CPPFLAGS = $(BOOST_CPPFLAGS)

boost_program_options_sample_SOURCES = boost_program_options_sample.cpp
boost_program_options_sample_CPPFLAGS = $(BOOST_CPPFLAGS)
boost_program_options_sample_LDFLAGS = $(BOOST_LDFLAGS)
boost_program_options_sample_LDADD = $(BOOST_PROGRAM_OPTIONS_LIB)

c1_SOURCES = c1.cpp

g1_SOURCES = g1.cpp
g1_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
g1_LDFLAGS = $(OPENGL_FRAMEWORK) $(BOOST_LDFLAGS)
g1_LDADD = libsdlapp.a liblogger.a $(SDL_LIBS) $(BOOST_SYSTEM_LIB)

line_segment_2d_benchmark_SOURCES = line_segment_2d_benchmark.cpp
line_segment_2d_benchmark_CPPFLAGS = $(BOOST_CPPFLAGS) $(SDL_CFLAGS)
line_segment_2d_benchmark_LDADD = libsdlapp.a $(SDL_LIBS)

map_benchmark_SOURCES = map_benchmark.cpp
map_benchmark_CPPFLAGS = $(BOOST_CPPFLAGS)

observer_benchmark_SOURCES = observer_benchmark.cpp
observer_benchmark_CPPFLAGS = $(BOOST_CPPFLAGS)

oscillator_sample_SOURCES = oscillator_sample.cpp
oscillator_sample_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
oscillator_sample_LDFLAGS = $(OPENGL_FRAMEWORK) $(BOOST_LDFLAGS)
oscillator_sample_LDADD = libsequencer.a libsdlapp.a liblogger.a $(SDL_LIBS) $(BOOST_SYSTEM_LIB)

pcap_sample_SOURCES = pcap_sample.cpp
pcap_sample_LDADD = $(PCAP_LIBS)

peg_sample_SOURCES = peg_sample.cpp
peg_sample_CPPFLAGS = $(GTEST_CPPFLAGS) $(BOOST_CPPFLAGS)
peg_sample_LDADD = libpeg.a liblogger.a $(GTEST_LIBS)

peg_sample2_SOURCES = peg_sample2.cpp
peg_sample2_CPPFLAGS = $(GTEST_CPPFLAGS) $(BOOST_CPPFLAGS)
peg_sample2_LDADD = libpeg.a liblogger.a $(GTEST_LIBS)

s1_SOURCES = s1.cpp

s2_SOURCES = s2.cpp
s2_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
s2_LDFLAGS = $(OPENGL_FRAMEWORK) $(BOOST_LDFLAGS)
s2_LDADD = libsdlapp.a liblogger.a $(SDL_LIBS) $(BOOST_SYSTEM_LIB)

sdl_event_sample_SOURCES = sdl_event_sample.c
sdl_event_sample_CPPFLAGS = $(SDL_CFLAGS)
sdl_event_sample_LDADD = liblogger.a $(SDL_LIBS)

sdl_event_sample2_SOURCES = sdl_event_sample2.m
sdl_event_sample2_CPPFLAGS = $(SDL_CFLAGS)
sdl_event_sample2_LDFLAGS = $(COCOA_FRAMEWORK)
sdl_event_sample2_LDADD = $(SDL_LIBS)

sdl_opengl_sample_SOURCES = sdl_opengl_sample.cc
sdl_opengl_sample_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
sdl_opengl_sample_LDFLAGS = $(OPENGL_FRAMEWORK) $(BOOST_LDFLAGS)
sdl_opengl_sample_LDADD = libsdlapp.a liblogger.a $(SDL_LIBS) $(BOOST_SYSTEM_LIB)

#smf_dump_SOURCES = smf_dump.cpp
#smf_dump_CPPFLAGS = $(BOOST_CPPFLAGS)
#smf_dump_LDADD = libsequencer.a liblogger.a

smf_play_SOURCES = smf_play.cpp
smf_play_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
smf_play_LDFLAGS = $(BOOST_LDFLAGS)
smf_play_LDADD = libsequencer.a libsdlapp.a liblogger.a $(SDL_LIBS) $(BOOST_SYSTEM_LIB)

udp_sample_SOURCES = udp_sample.c

noinst_LIBRARIES = liblogger.a libpeg.a libsdlapp.a libsequencer.a libtest_main.a libgtest.a

liblogger_a_SOURCES = logger_c.c logger.h logger_cpp.cpp logger.hpp
liblogger_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libpeg_a_SOURCES = peg.cpp peg.hpp
libpeg_a_CPPFLAGS = $(BOOST_CPPFLAGS)

libsdlapp_a_SOURCES = frame_wait_timer.cpp frame_wait_timer.hpp \
		      font.cpp font.hpp \
		      fps.cpp fps.hpp \
		      load_time.cpp load_time.hpp \
		      pad.cpp pad.hpp \
		      point_2d.cpp point_2d.hpp \
		      sdl_app.cpp sdl_app.hpp \
		      sprite.cpp sprite.hpp \
		      texture.cpp texture.hpp \
		      texture_pool.cpp texture_pool.hpp \
		      vector_2d.cpp vector_2d.hpp
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
			 sample_voice.cpp sample_voice.hpp \
			 sine_wave_oscillator.cpp sine_wave_oscillator.hpp \
			 song.cpp song.hpp \
			 sound.cpp sound.hpp \
			 triangle_wave_oscillator.cpp triangle_wave_oscillator.hpp \
			 smf.cpp smf.hpp \
			 smf_track.cpp smf_track.hpp \
			 variable_length_value.cpp variable_length_value.hpp \
			 voice.cpp voice.hpp \
			 volume.hpp \
			 voice_base.hpp \
			 wav.cpp
libsequencer_a_CPPFLAGS = $(SDL_CFLAGS) $(BOOST_CPPFLAGS)

libtest_main_a_SOURCES = test_main.cpp
libtest_main_a_CPPFLAGS = $(CPPUNIT_CFLAGS) $(BOOST_CPPFLAGS)
libtest_main_a_LIBADD = liblogger.a

vector_length_benchmark_SOURCES = vector_length_benchmark.cpp
vector_length_benchmark_CPPFLAGS = $(BOOST_CPPFLAGS)

noinst_DATA = data/sound_data_sample.bin

data/sound_data_sample.bin: data/sound_data_sample.s
	$(NASM) -o data/sound_data_sample.bin data/sound_data_sample.s

check_PROGRAMS = all_gtests memory_allocator_test serial_number_test
TESTS = $(check_PROGRAMS) peg_test.sh

GTEST_DIR = $(top_srcdir)/gtest-1.6.0
GTEST_CPPFLAGS = -I$(GTEST_DIR)/include -I$(GTEST_DIR)
GTEST_LIBS = -L$(builddir) libgtest.a

libgtest_a_SOURCES = $(GTEST_DIR)/src/gtest-all.cc $(GTEST_DIR)/src/gtest_main.cc
libgtest_a_CPPFLAGS = $(GTEST_CPPFLAGS)

GMOCK_DIR = $(builddir)/gmock

all_gtests_SOURCES = \
	audio_stream_test.cpp \
	channel_test.cpp \
	circle_2d_test.cpp \
	circular_buffer_test.cpp \
	filter_test.cpp \
	font_test.cpp \
	fps_test.cpp \
	function_test.cpp \
	function_test2.cpp \
	instrument_test.cpp \
	line_segment_2d_test.cpp \
	load_time_test.cpp \
	logger_test.cpp \
	lot_box_test.cpp \
	object_test.cpp \
	object_counter_test.cpp \
	observer_test.cpp \
	oscillator_factory_test.cpp \
	oscillator_stream_test.cpp \
	oscillator_test.cpp \
	patch_test.cpp \
	pad_test.cpp \
	peg_test.cpp \
	point_2d_test.cpp \
	property_test.cpp \
	pseudo_triangle_wave_oscillator_test.cpp \
	rect_test.cpp \
	sampler_test.cpp \
	sine_wave_oscillator_test.cpp \
	smf_test.cpp \
	smf_track_test.cpp \
	song_test.cpp \
	sound_test.cpp \
	sprite_test.cpp \
	texture_pool_test.cpp \
	texture_test.cpp \
	triangle_wave_oscillator_test.cpp \
	variable_length_value_test.cpp \
	vector_2d_test.cpp \
	volume_test.cpp \
	voice_test.cpp
all_gtests_CXXFLAGS =
all_gtests_CPPFLAGS = -I$(GTEST_DIR)/include -I$(GMOCK_DIR)/include $(SDL_CFLAGS) $(BOOST_CPPFLAGS)
all_gtests_LDFLAGS = $(OPENGL_FRAMEWORK) $(BOOST_LDFLAGS)
all_gtests_LDADD = libpeg.a libsequencer.a libsdlapp.a liblogger.a $(GTEST_LIBS) $(SDL_LIBS) $(BOOST_SYSTEM_LIB)

memory_allocator_test_SOURCES = \
	memalloc_test.cpp \
	memalloc.c memalloc.h \
	memory_allocator_test.cpp \
	memory_allocator.cpp memory_allocator.hpp
memory_allocator_test_CPPFLAGS = -I$(GTEST_DIR)/include
memory_allocator_test_LDADD = $(GTEST_LIBS)

serial_number_test_SOURCES = \
	serial_number_test.cpp
serial_number_test_CPPFLAGS = -I$(GTEST_DIR)/include
serial_number_test_LDADD = $(GTEST_LIBS)

AM_CFLAGS = -Wall -Wextra $(COVERAGE_CFLAGS)
AM_CXXFLAGS = -Wall -Wextra $(COVERAGE_CXXFLAGS)
AM_OBJCFLAGS = -Wall -Wextra $(COVERAGE_OBJCFLAGS)

OBJECTS = $(all_gtests_OBJECTS) \
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

TEST_OBJECTS = \
	  $(all_gtests_OBJECTS) \
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

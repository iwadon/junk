srcdir = ..
builddir = .
CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -g
OBJC = gcc
OBJCFLAGS = -Wall -Wextra -O2 -g
CPPFLAGS = -DHAVE_CONFIG_H -I. -I$(srcdir) -I/Users/don/local/include/SDL -I/Users/don/local/include
LDFLAGS = -g -L/Users/don/local/lib
LDADD =

$(builddir)/%.o: $(srcdir)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
$(builddir)/%.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
$(builddir)/%.o: $(srcdir)/%.m
	$(OBJC) $(OBJCFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: all
all: $(builddir)/benchmark_sample $(builddir)/boost_program_options_sample $(builddir)/c1 \
    $(builddir)/map_benchmark $(builddir)/oscillator_sample $(builddir)/pcap_sample $(builddir)/s1 $(builddir)/s2 \
    $(builddir)/sdl_event_sample $(builddir)/sdl_event_sample2 $(builddir)/smf_play \
    $(builddir)/liblogger.a $(builddir)/libpeg.a $(builddir)/libsdlapp.a $(builddir)/libsequencer.a $(builddir)/libtest_main.a \
    $(builddir)/vector_length_benchmark

$(builddir)/benchmark_sample.o: $(srcdir)/benchmark_sample.cpp
$(builddir)/benchmark_sample: $(builddir)/benchmark_sample.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD)

$(builddir)/boost_program_options_sample.o: $(srcdir)/boost_program_options_sample.cpp
$(builddir)/boost_program_options_sample: $(builddir)/boost_program_options_sample.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD) -lboost_program_options-mt

$(builddir)/c1.o: $(srcdir)/c1.cpp
$(builddir)/c1: $(builddir)/c1.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD)

$(builddir)/map_benchmark.o: $(srcdir)/map_benchmark.cpp
$(builddir)/map_benchmark: $(builddir)/map_benchmark.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD)

$(builddir)/oscillator_sample.o: $(srcdir)/oscillator_sample.cpp
$(builddir)/oscillator_sample: $(builddir)/oscillator_sample.o \
    $(builddir)/libsequencer.a $(builddir)/libsdlapp.a $(builddir)/liblogger.a
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD) -lSDL -lSDL_image

$(builddir)/pcap_sample.o: $(srcdir)/pcap_sample.cpp
$(builddir)/pcap_sample: $(builddir)/pcap_sample.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD) -lpcap

$(builddir)/s1.o: $(srcdir)/s1.cpp
$(builddir)/s1: $(builddir)/s1.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD) -lSDL -lSDL_image

$(builddir)/s2.o: $(srcdir)/s2.cpp
$(builddir)/s2: $(builddir)/s2.o $(builddir)/libsdlapp.a $(builddir)/liblogger.a
	$(CXX) $(LDFLAGS) -framework OpenGL -o $@ $^ $(LDADD) -lSDL -lSDL_image

$(builddir)/sdl_event_sample.o: $(srcdir)/sdl_event_sample.c
$(builddir)/sdl_event_sample: $(builddir)/sdl_event_sample.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDADD) -lSDL

$(builddir)/sdl_event_sample2.o: $(srcdir)/sdl_event_sample2.m
$(builddir)/sdl_event_sample2: $(builddir)/sdl_event_sample2.o
	$(OBJC) $(LDFLAGS) -framework Cocoa -o $@ $^ $(LDADD) -lSDL

$(builddir)/smf_play.o: $(srcdir)/smf_play.cpp
$(builddir)/smf_play: $(builddir)/smf_play.o $(builddir)/libsequencer.a $(builddir)/libsdlapp.a $(builddir)/liblogger.a
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD) -lSDL

$(builddir)/vector_length_benchmark.o: $(srcdir)/vector_length_benchmark.cpp
$(builddir)/vector_length_benchmark: $(builddir)/vector_length_benchmark.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD)

$(builddir)/logger.o: $(srcdir)/logger.cpp
$(builddir)/liblogger.a: $(builddir)/logger.o
	ar crs $@ $^

$(builddir)/peg.o: $(srcdir)/peg.cpp
$(builddir)/libpeg.a: $(builddir)/peg.o
	ar crs $@ $^

$(builddir)/controller.o: $(srcdir)/controller.cpp
$(builddir)/frame_wait_timer.o: $(srcdir)/frame_wait_timer.cpp
$(builddir)/font.o: $(srcdir)/font.cpp
$(builddir)/fps.o: $(srcdir)/fps.cpp
$(builddir)/load_time.o: $(srcdir)/load_time.cpp
$(builddir)/sdl_app.o: $(srcdir)/sdl_app.cpp
$(builddir)/sprite.o: $(srcdir)/sprite.cpp
$(builddir)/texture.o: $(srcdir)/texture.cpp
$(builddir)/texture_pool.o: $(srcdir)/texture_pool.cpp
$(builddir)/libsdlapp.a: $(builddir)/controller.o \
    $(builddir)/frame_wait_timer.o \
    $(builddir)/font.o \
    $(builddir)/fps.o \
    $(builddir)/load_time.o \
    $(builddir)/sdl_app.o \
    $(builddir)/sprite.o \
    $(builddir)/texture.o \
    $(builddir)/texture_pool.o
	ar crs $@ $^

$(builddir)/channel.o: $(srcdir)/channel.cpp
$(builddir)/filter.o: $(srcdir)/filter.cpp
$(builddir)/instrument.o: $(srcdir)/instrument.cpp
$(builddir)/oscillator.o: $(srcdir)/oscillator.cpp
$(builddir)/oscillator_factory.o: $(srcdir)/oscillator_factory.cpp
$(builddir)/oscillator_stream.o: $(srcdir)/oscillator_stream.cpp
$(builddir)/patch.o: $(srcdir)/patch.cpp
$(builddir)/pseudo_triangle_wave_oscillator.o: $(srcdir)/pseudo_triangle_wave_oscillator.cpp
$(builddir)/sampler.o: $(srcdir)/sampler.cpp
$(builddir)/sine_wave_oscillator.o: $(srcdir)/sine_wave_oscillator.cpp
$(builddir)/song.o: $(srcdir)/song.cpp
$(builddir)/triangle_wave_oscillator.o: $(srcdir)/triangle_wave_oscillator.cpp
$(builddir)/smf.o: $(srcdir)/smf.cpp
$(builddir)/smf_track.o: $(srcdir)/smf_track.cpp
$(builddir)/variable_length_value.o: $(srcdir)/variable_length_value.cpp
$(builddir)/voice.o: $(srcdir)/voice.cpp
$(builddir)/libsequencer.a: $(builddir)/channel.o \
    $(builddir)/filter.o \
    $(builddir)/instrument.o \
    $(builddir)/oscillator.o \
    $(builddir)/oscillator_factory.o \
    $(builddir)/oscillator_stream.o \
    $(builddir)/patch.o \
    $(builddir)/pseudo_triangle_wave_oscillator.o \
    $(builddir)/sampler.o \
    $(builddir)/sine_wave_oscillator.o \
    $(builddir)/song.o \
    $(builddir)/triangle_wave_oscillator.o \
    $(builddir)/smf.o \
    $(builddir)/smf_track.o \
    $(builddir)/variable_length_value.o \
    $(builddir)/voice.o
	ar crs $@ $^

$(builddir)/test_main.o: $(srcdir)/test_main.cpp
$(builddir)/libtest_main.a: $(builddir)/test_main.o
	ar crs $@ $^

.PHONY: check
check: $(builddir)/all_tests
	$(builddir)/all_tests

$(builddir)/audio_stream_test.o: $(srcdir)/audio_stream_test.cpp
$(builddir)/channel_test.o: $(srcdir)/channel_test.cpp
$(builddir)/circle_2d_test.o: $(srcdir)/circle_2d_test.cpp
$(builddir)/circular_buffer_test.o: $(srcdir)/circular_buffer_test.cpp
$(builddir)/filter_test.o: $(srcdir)/filter_test.cpp
$(builddir)/font_test.o: $(srcdir)/font_test.cpp
$(builddir)/fps_test.o: $(srcdir)/fps_test.cpp
$(builddir)/function_test.o: $(srcdir)/function_test.cpp
$(builddir)/instrument_test.o: $(srcdir)/instrument_test.cpp
$(builddir)/line_segment_2d_test.o: $(srcdir)/line_segment_2d_test.cpp
$(builddir)/load_time_test.o: $(srcdir)/load_time_test.cpp
$(builddir)/logger_test.o: $(srcdir)/logger_test.cpp
$(builddir)/lot_box_test.o: $(srcdir)/lot_box_test.cpp
$(builddir)/object_test.o: $(srcdir)/object_test.cpp
$(builddir)/observer_test.o: $(srcdir)/observer_test.cpp
$(builddir)/oscillator_factory_test.o: $(srcdir)/oscillator_factory_test.cpp
$(builddir)/oscillator_stream_test.o: $(srcdir)/oscillator_stream_test.cpp
$(builddir)/oscillator_test.o: $(srcdir)/oscillator_test.cpp
$(builddir)/patch_test.o: $(srcdir)/patch_test.cpp
$(builddir)/peg_test.o: $(srcdir)/peg_test.cpp
$(builddir)/point_2d_test.o: $(srcdir)/point_2d_test.cpp
$(builddir)/pseudo_triangle_wave_oscillator_test.o: $(srcdir)/pseudo_triangle_wave_oscillator_test.cpp
$(builddir)/rect_test.o: $(srcdir)/rect_test.cpp
$(builddir)/sampler_test.o: $(srcdir)/sampler_test.cpp
$(builddir)/sine_wave_oscillator_test.o: $(srcdir)/sine_wave_oscillator_test.cpp
$(builddir)/smf_test.o: $(srcdir)/smf_test.cpp
$(builddir)/smf_track_test.o: $(srcdir)/smf_track_test.cpp
$(builddir)/song_test.o: $(srcdir)/song_test.cpp
$(builddir)/sprite_test.o: $(srcdir)/sprite_test.cpp
$(builddir)/texture_pool_test.o: $(srcdir)/texture_pool_test.cpp
$(builddir)/texture_test.o: $(srcdir)/texture_test.cpp
$(builddir)/triangle_wave_oscillator_test.o: $(srcdir)/triangle_wave_oscillator_test.cpp
$(builddir)/variable_length_value_test.o: $(srcdir)/variable_length_value_test.cpp
$(builddir)/vector_2d_test.o: $(srcdir)/vector_2d_test.cpp
$(builddir)/voice_test.o: $(srcdir)/voice_test.cpp
$(builddir)/volume_test.o: $(srcdir)/volume_test.cpp
$(builddir)/all_tests: \
    $(builddir)/audio_stream_test.o \
    $(builddir)/channel_test.o \
    $(builddir)/circle_2d_test.o \
    $(builddir)/circular_buffer_test.o \
    $(builddir)/filter_test.o \
    $(builddir)/font_test.o \
    $(builddir)/fps_test.o \
    $(builddir)/function_test.o \
    $(builddir)/instrument_test.o \
    $(builddir)/line_segment_2d_test.o \
    $(builddir)/load_time_test.o \
    $(builddir)/logger_test.o \
    $(builddir)/lot_box_test.o \
    $(builddir)/object_test.o \
    $(builddir)/observer_test.o \
    $(builddir)/oscillator_factory_test.o \
    $(builddir)/oscillator_stream_test.o \
    $(builddir)/oscillator_test.o \
    $(builddir)/patch_test.o \
    $(builddir)/peg_test.o \
    $(builddir)/point_2d_test.o \
    $(builddir)/pseudo_triangle_wave_oscillator_test.o \
    $(builddir)/rect_test.o \
    $(builddir)/sampler_test.o \
    $(builddir)/sine_wave_oscillator_test.o \
    $(builddir)/smf_test.o \
    $(builddir)/smf_track_test.o \
    $(builddir)/song_test.o \
    $(builddir)/sprite_test.o \
    $(builddir)/texture_pool_test.o \
    $(builddir)/texture_test.o \
    $(builddir)/triangle_wave_oscillator_test.o \
    $(builddir)/variable_length_value_test.o \
    $(builddir)/vector_2d_test.o \
    $(builddir)/voice_test.o \
    $(builddir)/volume_test.o \
    $(builddir)/libpeg.a $(builddir)/libsdlapp.a $(builddir)/libsequencer.a $(builddir)/libtest_main.a $(builddir)/liblogger.a
	$(CXX) $(LDFLAGS) -framework OpenGL -o $@ $^ $(LDADD) -lcppunit -lSDL -lSDL_image -lboost_program_options-mt

AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libsequencer.a

libsequencer_a_SOURCES = variable_length_value.cpp variable_length_value.hpp \
			 volume.hpp

check_PROGRAMS = sequencer_test
TESTS = $(check_PROGRAMS)

sequencer_test_SOURCES = test_main.cpp variable_length_value_test.cpp volume_test.cpp
sequencer_test_CPPFLAGS = $(CPPUNIT_CFLAGS)
sequencer_test_LDADD = $(CPPUNIT_LIBS) libsequencer.a

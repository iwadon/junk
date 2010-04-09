AUTOMAKE_OPTIONS = foreign

check_PROGRAMS = volume_test
TESTS = $(check_PROGRAMS)

volume_test_SOURCES = test_main.cpp volume_test.cpp
volume_test_CPPFLAGS = $(CPPUNIT_CFLAGS)
volume_test_LDADD = $(CPPUNIT_LIBS)

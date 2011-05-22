#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(junk, 0.0.0, don@na.rim.or.jp)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([test_main.cpp])
AC_CONFIG_HEADER([config.h])

AC_ARG_ENABLE([opengl], [AS_HELP_STRING([--enable-opengl], [use OpenGL (default is no)])], [use_opengl=$withval], [use_opengl=no])
if test "x$use_opengl" != xno; then
  AC_DEFINE([ENABLE_OPENGL], [1], [Define 1 to you use OpenGL])
  case "$host" in
    *-*-darwin*)
      OPENGL_FRAMEWORK="-framework OpenGL"
      AC_SUBST(OPENGL_FRAMEWORK)
      ;;
  esac
fi

AC_ARG_ENABLE([coverage], [AS_HELP_STRING([--enable-coverage], [use gcov and lcov (default is no)])], [use_coverage=$withval], [use_coverage=no])
if test "x$use_coverage" != xno; then
  COVERAGE_CFLAGS="-coverage"
  COVERAGE_CXXFLAGS="-coverage"
  COVERAGE_LIBS="-lgcov"
  AC_SUBST(COVERAGE_CFLAGS)
  AC_SUBST(COVERAGE_CXXFLAGS)
  AC_SUBST(COVERAGE_LIBS)
fi

# Checks for programs.
AC_PROG_AWK
AC_PROG_OBJC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB
AC_PROG_CPP
AC_PROG_MKDIR_P
AX_PROG_NASM

AX_WITH_RUBY

AC_CHECK_PROGS(DOXYGEN, [doxygen])

# Checks for libraries.
AM_PATH_SDL(1.3.0)
SDL_LIBS="$SDL_LIBS -lSDL_image"
AM_PATH_CPPUNIT
AX_BOOST_BASE
AX_BOOST_PROGRAM_OPTIONS
AC_CHECK_LIB([pcap], [pcap_lookupdev])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h mach/mach_time.h netinet/in.h pcap.h pcap/pcap.h stdint.h sys/socket.h unistd.h])
AC_LANG_PUSH(C++)
AC_CHECK_HEADERS([tr1/cstdint tr1/unordered_map ext/hash_map])
AC_LANG_POP

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_HEADER_STDC
AC_CXX_HEADER_STDCXX_98
AC_FUNC_MEMCMP
AC_CHECK_FUNCS([memset socket])

AC_CONFIG_FILES([Doxyfile Makefile build.ninja])
AC_CONFIG_FILES([net_test.sh], [chmod +x net_test.sh])
AC_CONFIG_FILES([peg_test.sh], [chmod +x peg_test.sh])
AC_OUTPUT

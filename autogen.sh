#!/bin/sh
build_dir=`pwd`
top_dir=`dirname $0`
cd $top_dir

SDL2_CONFIG=`which sdl2-config`
if test "x$SDL2_CONFIG" != x; then
  ACDIR="-I `$SDL2_CONFIG --prefix`/share/aclocal"
fi
for d in $HOME/local /opt/local /usr/local; do
    test -d $d/share/aclocal && ACDIR="$ACDIR -I $d/share/aclocal"
done
ACLOCAL="aclocal $ACDIR"
AUTOHEADER="autoheader"
AUTOMAKE="automake -a"
AUTOCONF="autoconf"

echo $ACLOCAL
$ACLOCAL
echo $AUTOHEADER
$AUTOHEADER
echo $AUTOMAKE
$AUTOMAKE
echo $AUTOCONF
$AUTOCONF

cd $build_dir
$top_dir/configure ACLOCAL="$ACLOCAL" AUTOHEADER="$AUTOHEADER" AUTOMAKE="$AUTOMAKE" AUTOCONF="$AUTOCONF" $*

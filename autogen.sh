#!/bin/sh
build_dir=`pwd`
top_dir=`dirname $0`
cd $top_dir

ACDIR="-I `sdl-config --prefix`/share/aclocal"
for d in $HOME/local /opt/local /usr/local; do
    test -d $d/share/aclocal && ACDIR="$ACDIR -I $d/share/aclocal"
done
ACLOCAL="aclocal $ACDIR"
AUTOHEADER="autoheader"
AUTOMAKE="automake -a"
AUTOCONF="autoconf"

$ACLOCAL
$AUTOHEADER
$AUTOMAKE
$AUTOCONF

cd $build_dir
$top_dir/configure ACLOCAL="$ACLOCAL" AUTOHEADER="$AUTOHEADER" AUTOMAKE="$AUTOMAKE" AUTOCONF="$AUTOCONF" $*

#!/bin/sh
set -x

echo " clean object files (and .svg files)"
rm -fr *.o
rm -fr *.svg

echo " clean executables..."
rm -fr benchmarks/test-*


#!/bin/sh
#set -x

GNUPLOT=/usr/bin/gnuplot
INKSCAPE=/usr/bin/inkscape
#INKSCAPE=echo

##
## Plot 10: Approx
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g" > raw.csv 
cat raw.csv | grep CPU                 > data.csv
cat raw.csv | grep O2 | grep "APPROX" >> data.csv
$GNUPLOT<<EOF>data-find-approx.svg
set terminal svg size 1512,700
#set title 'Time (nanosec.)'
set xlabel 'Approximation / Number of elements in the key (1 - 64)'
set xtics rotate by 90 right scale 0
set ylabel 'Time (nanosec.)'
set logscale y
set yrange [ 0.1 : 7000 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv
rm -fr data.csv
$INKSCAPE data-find-approx.svg --without-gui --export-pdf=data-find-approx.pdf &


#
# Plot 20: -O2 vs -O0 ...
#
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"  > raw.csv 
cat raw.csv | grep CPU                                            > data.csv
cat raw.csv | grep "FIND-1-ON-1-DEFAULT"                         >> data.csv
$GNUPLOT<<EOF>data-find1-gccopt.svg
set terminal svg size 1248,600
#set title 'Time (nanosec.)'
set xlabel '"Compile Optimization" x "Number of elements in the key (1 - 64)"'
set xtics rotate by 90 right scale 0
set ylabel 'Time (nanosec.)'
set yrange [ 0.1 : 1900 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(2) title columnheader
EOF
rm -fr raw.csv
rm -fr data.csv
$INKSCAPE data-find1-gccopt.svg --without-gui --export-pdf=data-find1-gccopt.pdf &


##
## Plot 30: Approx trunc vs round vs ...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"           > raw.csv 
cat raw.csv | grep CPU                                                     > data.csv
cat raw.csv | grep O2 | grep  "FIND-1-ON-256" | sed 's/FIND-1-ON-256-//g' >> data.csv
$GNUPLOT<<EOF>data-find1on256-approxy.svg
set terminal svg size 1248,600
#set title 'Time (nanosec.)'
set xlabel '"Find one element in a hashtable of 256 elements filled with X" x "K elements in the key (1 - 64)"'
set xtics rotate by 90 right scale 0
set ylabel 'Time (nanosec.)'
set yrange [ 0.1 : 1100 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv
rm -fr data.csv
$INKSCAPE data-find1on256-approxy.svg --without-gui --export-pdf=data-find1on256-approxy.pdf &


##
## Plot 40: Approx trunc 1 vs 2 vs 4 vs ...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"         > raw.csv 
cat raw.csv | grep CPU                                                   > data.csv
cat raw.csv | grep O2 | grep  "APPROX-TRUNC" | sed 's/-APPROX-TRUNC//g' >> data.csv
$GNUPLOT<<EOF>data-findony-approxtrunc.svg
set terminal svg size 1248,600
#set title 'Time (nanosec.)'
set xlabel '"Find one element in a hashtable of H elements filled with approx-trunc" x "K elements in the key (1 - 64)"'
set xtics rotate by 90 right scale 0
set ylabel 'Time (nanosec.)'
set logscale y
set yrange [ 0.1 : 5000 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv
rm -fr data.csv
$INKSCAPE data-findony-approxtrunc.svg --without-gui --export-pdf=data-findony-approxtrunc.pdf &


##
## Plot 50: WITHOUT Approx 1 vs 2 vs 4 vs ...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"             > raw.csv 
cat raw.csv | grep CPU                                                       > data.csv
cat raw.csv | grep O2 | grep  "WITHOUT-APPROX" | sed 's/-WITHOUT-APPROX//g' >> data.csv
$GNUPLOT<<EOF>data-findony-woapprox.svg
set terminal svg size 1536,750
#set title 'Time (nanosec.)'
set xlabel '"Find one element in a hashtable of H elements filled without-approximation" x "K elements in the key (1 - 64)"'
set xtics rotate by 90 right scale 0
set ylabel 'Time (nanosec.)'
set logscale y
set yrange [ 1 : 3000 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv
rm -fr data.csv
$INKSCAPE data-findony-woapprox.svg --without-gui --export-pdf=data-findony-woapprox.pdf &


##
## Plot 60: errors on approx 1 vs ...
##
cat results/results-errors-i5.txt | sed "s/_/-/g" | sed "s/;$//g"   > raw.csv 
cat raw.csv | sed "s/APPROX-//g"                                    > data.csv
$GNUPLOT<<EOF>data-errors.svg
set terminal svg size 1536,600
#set title 'Error (percentaje) from without-approximation'
set xlabel 'K elements in the key (1 - 64) and Algorith x Approximation used'
set xtics rotate by 90 right scale 0
set ylabel 'Error (percentaje) from without-approximation'
#set logscale y
#set yrange [ 1 : 120 ]
set yrange [ -20 : 10 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set datafile separator ';'
plot for [COL=2:*] 'data.csv' using COL:xticlabels(1) title columnheader
EOF
rm -fr raw.csv
rm -fr data.csv
$INKSCAPE data-errors.svg --without-gui --export-pdf=data-errors.pdf &


##
## Plot 70: search key (with only one element) in...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"           > raw.csv 
grep O2 raw.csv | grep "\-WITHOUT-APPROX" | sed "s/-WITHOUT-APPROX//g"     > raw2.csv
cat raw.csv   | grep CPU                                                   > data.csv
cat raw2.csv  | awk -F';' '{ tname=substr($3,1,length($3)-1); print $1";"$2";"tname"-PACK\";"$4";"$5";"$6";"$7";"$8";"$9";"$10; print $1";"$2";"tname"-NOPACK\";"$4";"$4*2";"$4*4";"$4*8";"$4*16";"$4*32";"$4*64 }' >> data.csv
$GNUPLOT<<EOF>data-woapprx-key1elto.svg
set terminal svg size 1536,600
#set title 'Time (nanosec.) with key of single one element'
set xlabel 'Find K elements (1 - 64) in a hashtable of H elements (2 - 1024) one by one (NOPACK) or all K elements together (PACK)'
set xtics rotate by 90 right scale 0
set ylabel 'Time (nanosec.)'
set logscale y
set yrange [ 1 : 19000 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv raw2.csv
rm -fr data.csv
$INKSCAPE data-woapprx-key1elto.svg --without-gui --export-pdf=data-woapprx-key1elto.pdf &



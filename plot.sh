#!/bin/bash
set -x

GNUPLOT=/usr/bin/gnuplot
INKSCAPE=/usr/bin/inkscape
INKFILES=""

# ##
# ## Plot 10: Approx
# ##
# cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g" > raw.csv 
# cat raw.csv | grep CPU                 > data.csv
# cat raw.csv | grep O2 | grep "APPROX" >> data.csv
# $GNUPLOT<<EOF>data-find-approx.svg
# set terminal svg size 1536,650
# #set title 'Time (nanosec.)'
# ##set xlabel 'Approximation / Number of elements in the key (1 - 64)' font ",20"
# set xtics rotate by 90 right scale 0 font ",18"
# set ylabel 'Time (nanosec.)' font ",20"
# set ytics font ",18"
# set logscale y
# set yrange [ 0.1 : 7000 ]
# set style fill solid 1 noborder
# set style data histogram
# set style histogram clustered gap 1
# set grid ytics
# set key outside font ",18"
# set datafile separator ';'
# plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
# EOF
# rm -fr raw.csv
# mv data.csv data-find-approx.csv
# INKFILES+="data-find-approx "


#
# Plot 20: -O2 vs -O0 ...
#
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"  > raw.csv 
cat raw.csv | grep CPU                                            > data.csv
cat raw.csv | grep "FIND-1-ON-1-DEFAULT"                         >> data.csv
$GNUPLOT<<EOF>data-find1-gccopt.svg
set terminal svg size 1280,600
#set title 'Time (nanosec.)'
##set xlabel '"Compile Optimization" x "Number of elements in the key (1 - 64)"' font ",20"
#set xtics rotate by 90 right scale 0 font ",18"
set xtics scale 0 font ",18"
set ylabel 'Time (nanosec.)' font ",20"
set ytics font ",18"
set yrange [ 0.1 : 1900 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set key outside font ",18"
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(2) title columnheader
EOF
rm -fr raw.csv
mv data.csv data-find1-gccopt.csv
INKFILES+="data-find1-gccopt "


##
## Plot 30: Approx trunc vs round vs ...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"           > raw.csv 
cat raw.csv | grep CPU                                                     > data.csv
cat raw.csv | grep O2 | grep  "FIND-1-ON-256" | sed 's/FIND-1-ON-256-//g' >> data.csv
$GNUPLOT<<EOF>data-find1on256-approxy.svg
set terminal svg size 1280,600
#set title 'Time (nanosec.)'
##set xlabel '"Find one element in a hashtable of 256 elements filled with X" x "K elements in the key (1 - 64)"' font ",20"
set xtics rotate by 36 right scale 0 font ",18"
set ylabel 'Time (nanosec.)' font ",20"
set ytics font ",18"
set yrange [ 0.1 : 900 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set key outside font ",18"
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv
mv data.csv data-find1on256-approxy.csv
INKFILES+="data-find1on256-approxy "


##
## Plot 40: Approx trunc 1 vs 2 vs 4 vs ...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"         > raw.csv 
cat raw.csv | grep CPU                                                   > data.csv
cat raw.csv | grep O2 | grep  "APPROX-TRUNC" | sed 's/-APPROX-TRUNC//g' | sed 's/FIND-//g' >> data.csv
$GNUPLOT<<EOF>data-findony-approxtrunc.svg
set terminal svg size 1280,600
#set title 'Time (nanosec.)'
##set xlabel '"Find one element in a hashtable of H elements filled with approx-trunc" x "K elements in the key (1 - 64)"' font ",20"
set xtics rotate by 90 right scale 0 font ",18"
set ylabel 'Time (nanosec.)' font ",20"
set ytics font ",18"
set logscale y
set yrange [ 0.1 : 5000 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set key outside font ",18"
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv
mv data.csv data-findony-approxtrunc.csv
INKFILES+="data-findony-approxtrunc "


##
## Plot 50: WITHOUT Approx 1 vs 2 vs 4 vs ...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"             > raw.csv 
cat raw.csv | grep CPU                                                       > data.csv
cat raw.csv | grep O2 | grep  "WITHOUT-APPROX" | sed 's/-WITHOUT-APPROX//g' | sed 's/FIND-//g' >> data.csv
$GNUPLOT<<EOF>data-findony-woapprox.svg
set terminal svg size 1536,650
#set title 'Time (nanosec.)'
##set xlabel '"Find one element in a hashtable of H elements filled without-approximation" x "K elements in the key (1 - 64)"' font ",20"
set xtics rotate by 90 right scale 0 font ",18"
set ylabel 'Time (nanosec.)' font ",20"
set ytics font ",18"
set logscale y
set yrange [ 1 : 3000 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set key outside font ",18"
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv
mv data.csv data-findony-woapprox.csv
INKFILES+="data-findony-woapprox "


##
## Plot 55: WITHOUT without-approx 64 vs 128 vs ...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"             > raw.csv 
cat raw.csv | grep CPU                                                       > data.csv
cat raw.csv | grep O2 | grep  "WITHOUT-APPROX" | sed 's/-WITHOUT-APPROX//g' | sed 's/FIND-//g' | tail -5 >> data.csv
$GNUPLOT<<EOF>data-findony-woapprox2.svg
set terminal svg size 1536,650
#set title 'Time (nanosec.)'
##set xlabel '"Find one element in a hashtable of H elements filled without-approximation" x "K elements in the key (64 - 1024)"' font ",20"
set xtics rotate by 90 right scale 0 font ",18"
set ylabel 'Time (nanosec.)' font ",20"
set ytics font ",18"
set logscale y
set yrange [ 1 : 3000 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set key outside font ",18"
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv
mv data.csv data-findony-woapprox2.csv
INKFILES+="data-findony-woapprox2 "


###
### Plot 56: WITHOUT without-Approx 1, 2, 4...
###
#cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g" > raw.csv 
#cat raw.csv | grep CPU                                                                         | awk -F';' '{print $3";"$4}'  > data.csv
#cat raw.csv | grep O2 | grep  "WITHOUT-APPROX" | sed 's/-WITHOUT-APPROX//g' | sed 's/FIND-//g' | awk -F';' '{print $3";"$4}' >> data.csv
#$GNUPLOT<<EOF>data-findony-woapprox3.svg
#set terminal svg size 1536,650
##set title 'Time (nanosec.)'
###set xlabel '"Find one element in a hashtable of H elements filled without-approximation"' font ",20"
#set xtics rotate by 90 right scale 0 font ",18"
#set ylabel 'Time (nanosec.)' font ",20"
#set ytics font ",18"
#set logscale y
#set yrange [ 1 : 350 ]
#set style fill solid 1 noborder
#set style data histogram
#set style histogram clustered gap 1
#set grid ytics
##set key outside font ",18"
#set key off
#set datafile separator ';'
#plot for [COL=1:*] 'data.csv' using COL:xticlabels(1) title columnheader
#EOF
#rm -fr raw.csv
#mv data.csv data-findony-woapprox3.csv
#INKFILES+="data-findony-woapprox3 "


##
## Plot 57: 1 function Without/with-x, ...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g" > raw.csv 
cat raw.csv | grep CPU                                                           | awk -F';' '{print $3";"$4}'  > data.csv
cat raw.csv | grep O2   | sed 's/FIND-//g' | grep -v '1-ON-2'                    | awk -F';' '{print $3";"$4}' >> data.csv
$GNUPLOT<<EOF>data-findony-approx3.svg
set terminal svg size 1536,650
#set title 'Time (nanosec.)'
##set xlabel '"Find one element in a hashtable of H elements filled without-approximation"' font ",20"
set xtics rotate by 90 right scale 0 font ",18"
set ylabel 'Time (nanosec.)' font ",20"
set ytics font ",18"
set logscale y
set yrange [ 1 : 1300 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
#set key outside font ",18"
set key off
set datafile separator ';'
plot for [COL=1:*] 'data.csv' using COL:xticlabels(1) title columnheader
EOF
rm -fr raw.csv
mv data.csv data-findony-approx3.csv
INKFILES+="data-findony-approx3 "


##
## Plot 60: errors on approx 1 vs ...
##
cat results/results-errors-i5.txt | sed "s/_/-/g" | sed "s/;$//g"   > raw.csv 
cat raw.csv | sed "s/APPROX-//g"                                    > data.csv
$GNUPLOT<<EOF>data-errors.svg
set terminal svg size 1536,650
#set title 'Error (percentaje) from without-approximation'
##set xlabel 'K elements in the key (1 - 64) and Algorith x Approximation used' font ",20"
#set xtics rotate by 90 right scale 0 font ",18"
set xtics scale 0 font ",20"
set ylabel 'Error (percentaje) from without-approximation' font ",20"
set ytics font ",20"
#set logscale y
#set yrange [ 1 : 120 ]
set yrange [ -20 : 10 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set key outside font ",18"
set datafile separator ';'
plot for [COL=2:*] 'data.csv' using COL:xticlabels(1) title columnheader
EOF
rm -fr raw.csv
mv data.csv data-errors.csv
INKFILES+="data-errors "


##
## Plot 70: search key (with only one element) in...
##
cat results/results-times-i5.txt | sed "s/_/-/g" | sed "s/;$//g"           > raw.csv 
grep O2 raw.csv | grep "\-WITHOUT-APPROX" | sed "s/-WITHOUT-APPROX//g"     > raw2.csv
cat raw.csv   | grep CPU                                                   > data.csv
cat raw2.csv  | awk -F';' '{ tname=substr($3,1,length($3)-1); print $1";"$2";"tname"-GROUP\";"$4";"$5";"$6";"$7";"$8";"$9";"$10; print $1";"$2";"tname"-SINGLE\";"$4";"$4*2";"$4*4";"$4*8";"$4*16";"$4*32";"$4*64 }' | sed 's/FIND-//g' >> data.csv
$GNUPLOT<<EOF>data-woapprx-key1elto.svg
set terminal svg size 1536,650
#set title 'Time (nanosec.) with key of single one element'
##set xlabel 'Find K elements (1 - 64) in a hashtable of H elements (2 - 1024) one by one (SINGLE) or all K elements together (GROUP)' font ",20"
set xtics rotate by 90 right scale 0 font ",18"
set ylabel 'Time (nanosec.)' font ",20"
set ytics font ",18"
set logscale y
set yrange [ 1 : 19000 ]
set style fill solid 1 noborder
set style data histogram
set style histogram clustered gap 1
set grid ytics
set key outside font ",18"
set datafile separator ';'
plot for [COL=4:*] 'data.csv' using COL:xticlabels(3) title columnheader
EOF
rm -fr raw.csv raw2.csv
mv data.csv data-woapprx-key1elto.csv
INKFILES+="data-woapprx-key1elto "


#
# Inkscape
#

## Inkscape 1.0beta2
#  INKCMD=$(echo $INKFILES | sed 's/data*/&.svg/g')
#  $INKSCAPE --export-type="pdf" $INKCMD 
## Inkscape 0.92.3
    echo $INKFILES |sed 's/ /\n/g'| awk -FS' ' '{print " --export-pdf="$1".pdf "$1".svg"}' | $INKSCAPE --shell


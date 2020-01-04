#!/bin/sh
set -x

#
#
OPTS="-O0 -O1 -O2 -O3 -Ofast -g"
#NELTOS=17
#NTESTS=1000
NELTOS=65
NTESTS=200

R_TIMES_TEX="./results/results-times-i5.tex"
R_VALUES_TEX="./results/results-values-i5.tex"
R_TIMES_TXT="./results/results-times-i5.txt"
R_VALUES_TXT="./results/results-values-i5.txt"


#
#
echo "test-vector"

rm -fr ${R_TIMES_TEX}  ; touch ${R_TIMES_TEX}
rm -fr ${R_VALUES_TEX} ; touch ${R_VALUES_TEX}
rm -fr ${R_TIMES_TXT}  ; touch ${R_TIMES_TXT}
rm -fr ${R_VALUES_TXT} ; touch ${R_VALUES_TXT}

for OPT in $OPTS; do
  ./benchmarks/test-find${OPT} ${NELTOS} ${NTESTS}
done

cat results-header-times.tex   results-times.tex   results-footer-times.tex  > ${R_TIMES_TEX} 
cat results-header-values.tex  results-values.tex  results-footer-values.tex > ${R_VALUES_TEX} 
cat results-header-times.txt   results-times.txt   results-footer-times.txt  > ${R_TIMES_TXT} 
cat results-header-values.txt  results-values.txt  results-footer-values.txt > ${R_VALUES_TXT} 

rm -fr results-header-*
rm -fr results-footer-*
rm -fr results-times.*
rm -fr results-values.*


#
#
OPT="-O2"
NELTOS=65
NTESTS=200

R_VALUES_TXT="./results/results-errors-i5.txt"

#
#
echo "test-approx"
./benchmarks/test-approx${OPT} ${NELTOS} ${NTESTS} > ${R_VALUES_TXT}


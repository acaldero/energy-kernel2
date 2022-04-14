#!/bin/sh
set -x

 OPTS="-O0 -O1 -O2 -O3 -Ofast -g"
 CPU="i5"
 CC="g++ -std=c++17"

mkdir -p benchmarks

# benchmark 1 & 2
for OPT in $OPTS; do

      # http://troydhanson.github.io/uthash/userguide.html#hash_functions
      #-DHASH_FUNCTION=HASH_JEN
      #-DHASH_FUNCTION=HASH_BER
      #-DHASH_FUNCTION=HASH_SAX
      #-DHASH_FUNCTION=HASH_OAT
      #-DHASH_FUNCTION=HASH_FNV
      #-DHASH_FUNCTION=HASH_SFH
      #-DHASH_FUNCTION=HASH_MUR -DHASH_USING_NO_STRICT_ALIASING -fno-strict-aliasing

      ${CC} -I. ${OPT} -o memoization_uthash.o  -c memoization_uthash.cc    -DHASH_FUNCTION=HASH_FNV
      ${CC} -I. ${OPT} -o compute_vector.o             -c compute_vector.cc            -DOPT=${OPT} -DCPU=${CPU}

      ${CC} -I. ${OPT} -o test_memo.o           -c test_memo.cc             -DOPT=${OPT} -DCPU=${CPU}
      ${CC} -I. ${OPT} -o test_inputs.o         -c test_inputs.cc           -DOPT=${OPT} -DCPU=${CPU}
      ${CC} -I. ${OPT} -o test_results.o        -c test_results.cc          -DOPT=${OPT} -DCPU=${CPU}
      ${CC} -I. ${OPT} -o test_algorithms.o     -c test_algorithms.cc       -DOPT=${OPT} -DCPU=${CPU}

      ${CC} -I. ${OPT} -o benchmark-compute-vs-find.o -c benchmark-compute-vs-find.cc -DOPT=${OPT} -DCPU=${CPU}
      ${CC} -I. ${OPT} -o benchmarks/test-cvsf${OPT} benchmark-compute-vs-find.o \
  	                  test_memo.o test_results.o test_algorithms.o test_inputs.o \
                          memoization_uthash.o compute_vector.o -lm -lz

      ${CC} -I. ${OPT} -o benchmark-find-vs-find.o    -c benchmark-find-vs-find.cc    -DOPT=${OPT} -DCPU=${CPU}
      ${CC} -I. ${OPT} -o benchmarks/test-find${OPT} benchmark-find-vs-find.o \
  	                  test_memo.o test_results.o test_algorithms.o test_inputs.o \
                          memoization_uthash.o compute_vector.o -lm -lz

done

# benchmark 3
      OPT="-O2"
      ${CC} -I. ${OPT} -o benchmark-compute-approx.o  -c benchmark-compute-approx.cc  -DOPT=${OPT} -DCPU=${CPU}
      ${CC} -I. ${OPT} -o benchmarks/test-approx${OPT} benchmark-compute-approx.o \
  	                  test_memo.o test_results.o test_algorithms.o test_inputs.o \
                          memoization_uthash.o compute_vector.o -lm -lz



#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <assert.h>

#include <memoization_uthash.h>
#include <compute_vector.h>

#include <test_inputs.h>
#include <test_algorithms.h>
#include <test_results.h>
#include <test_memo.h>


/*
 * Test listing
 */

TestInputs     inputs ;
TestAlgorithms algos ;
TestResults    results ;
TestMemo       memopool ;


/*
 * Test Scenario: compute(s) vs find
 */

double findConsumption ( int id, int n_eltos, float *utilization )
{
    double *ret ;

    ret = memopool.find(id, n_eltos, utilization) ;
    return ((ret) ? (*ret) : 0.0) ;
}

const char  *algos_name_cvsf[]                   = {
	                                              "FIND", 
						      "CUBIC", 
						      "LINEAR", 
						      "SQUARE", 
						      "SQRT", 
						      "PM1", 
						      "PM2"
                                                   } ;
double     (*algos_fn_cvsf[])(int, int, float *) = {
						      findConsumption,
						      calculateConsumption_CUBIC,  
						      calculateConsumption_LINEAR,
						      calculateConsumption_SQUARE, 
						      calculateConsumption_SQRT,
						      calculateConsumption_PM1,    
						      calculateConsumption_PM1
                                                   } ;
       int   cfg_n_cvsf = sizeof(algos_fn_cvsf)/sizeof(void *) ;

int setup_compute_vs_find ( int n_eltos )
{
    int    i, j, k ;
    double ret ;

    // 1.- initialize algorithms...
    algos.initialize(cfg_n_cvsf) ;
    for (i=0; i<algos.length(); i++) {
         algos.set(i, algos_fn_cvsf[i], (char *)algos_name_cvsf[i]) ;
    }

    // 2.- initialize inputs...
    inputs.initialize(n_eltos) ;

    // 3.- initialize results...
    results.initialize(algos, inputs) ;

    // 4.- fill 'memopool' hash tables
    int n_algos_find = algos.length() ;
    memopool.initialize(n_algos_find) ;

    for (i=0; i<n_eltos; i++)
    {
         inputs.fill(i, TestInputs::FILL_WITHOUT_APPROX) ;
         ret = calculateConsumption_SQRT(0, i, inputs.get()) ;

         for (j=0; j<n_algos_find; j++) {
              memopool.add(j, i, (float *)inputs.get(), (float)ret) ;
         }
    }

    // end
    return 0;
}


/*
 * Main
 */

int main ( int argc, char *argv[] )
{
    // 0.- parameters
    //
    if (argc < 3)
    {
        printf("\n") ;
        printf(" Compute-Consumption Kernel Benchmarking\n") ;
        printf(" ---------------------------------------\n") ;
        printf("\n") ;
        printf(" Usage: %s <number of input elements> <number of times>\n", argv[0]) ;
        printf("\n") ;
        printf("   <number of input elements> = 1 | 2 | 3 | ...\n") ;
        printf("       number of elements to compute its global consumption.\n") ;
        printf("\n") ;
        printf("   <number of times>          = 100 | ...\n") ;
        printf("       number of times same test is executed.\n") ;
        printf("\n") ;

        exit(-1) ;
    }

    int  n_eltos = atoi(argv[1]) ;
    int  n_tests = atoi(argv[2]) ;

    // 1.- init
    //
    double ret = setup_compute_vs_find(n_eltos) ;
    assert(ret >= 0) ;

    // 2.- testing...
    //
    inputs.fill(n_eltos, TestInputs::FILL_APPROX_TRUNC) ;
    results.perform_test(n_tests) ;

    // 3.- printing...
    //
    results.print_tex() ;
    results.print_txt() ;

    // end
    return 0;
}


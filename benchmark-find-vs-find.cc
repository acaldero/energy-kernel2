
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
 * Test Scenario: find in different memopools
 */

// cfg-dashboard
 const char *cfg_names[]  = {
                              "APPROX_TRUNC",
                              "APPROX_CEIL",
                              "APPROX_FLOOR",
                              "APPROX_ROUND",
                              "WITHOUT_APPROX"
                            } ;
       int   cfg_filler[] = {
                              TestInputs::FILL_APPROX_TRUNC,
                              TestInputs::FILL_APPROX_CEIL,
                              TestInputs::FILL_APPROX_FLOOR,
                              TestInputs::FILL_APPROX_ROUND,
                              TestInputs::FILL_WITHOUT_APPROX
                            } ;
       int   cfg_n_filler = sizeof(cfg_filler)/sizeof(int) ;
       int   cfg_deep     = 10 ;


// setup code...
char *malloc_algo_name ( int n_overfill, const char *filler )
{
    // set names: {findConsumption2, "FIND_1_ON_1_XXX"}, {findConsumption2, "FIND_1_ON_2_XXX"}, ...
    char *algo_name_i = (char *) malloc(128 * sizeof(char)) ;

    if (n_overfill == 0)
         sprintf(algo_name_i, "FIND_1_ON_1_%s",  filler) ;
    else sprintf(algo_name_i, "FIND_1_ON_%d_%s", n_overfill, filler) ;

    return algo_name_i ;
}

// find2
double findConsumption2 ( int id, int n_eltos, float *utilization )
{
    int m_filler = (cfg_n_filler - (id % cfg_n_filler)) % cfg_n_filler ;
    inputs.fill(n_eltos, cfg_filler[m_filler]) ;

    /*DEBUG*///inputs.fill(n_eltos, TestInputs::FILL_WITHOUT_APPROX) ;
    /*DEBUG*///printf("idalgo=%d idfiller=%d filler=%s FIND\n", id, m_filler, cfg_names[m_filler]) ;

    double *ret = memopool.find(id, n_eltos, utilization) ;
    return ((ret) ? (*ret) : 0.0) ;
}


int setup_find1_vs_findn ( int n_eltos )
{
    double ret ;

    // 1.- initialize algorithms...
    int n_algos = 1 + cfg_n_filler*cfg_deep ; // DEFAULT + (TRUNC_1 + TRUNC_2 + TRUNC_4 + ... ) + (FLOOR_1 + ...)
    algos.initialize(n_algos) ;

    // (a) set names...
    char *algo_name_i = malloc_algo_name(0, "DEFAULT") ;
    algos.set(0, findConsumption2, algo_name_i) ;

    for (int i=1; i<=n_algos/cfg_n_filler; i++)
    {
	 int n_overfill = (int)pow(2, i) ;

	 for (int k=0; k<cfg_n_filler; k++)
	 {
              algo_name_i = malloc_algo_name(n_overfill, cfg_names[k]) ;
              algos.set(cfg_n_filler*i-k, findConsumption2, algo_name_i) ;
    /*DEBUG*///printf("idalgo=%d idfiller=%d filler=%s SET\n", cfg_n_filler*i-k, k, cfg_names[k]) ;
	 }
    }

    // 2.- initialize inputs...
    inputs.initialize(n_eltos) ;

    // 3.- initialize results...
    results.initialize(algos, inputs) ;

    // 4.- fill 'memopool' hash tables
    memopool.initialize(n_algos) ;

    //DEBUG// for (int i=0; i<n_eltos; i++)
    for (int i=0; i<n_eltos; i=i+5)
    {
         // (a) pre-compute(default-filler, i-eltos) and memo(hash[0])
         inputs.fill(i, TestInputs::FILL_WITHOUT_APPROX) ;
         ret = calculateConsumption_LINEAR(0, i, inputs.get()) ;

         memopool.add(0, i, (float *)inputs.get(), (float)ret) ;

         // (b) pre-compute(x-filler, i-eltos), and memo, add more pre-computed results (over-fill)
         for (int j=1; j<=n_algos/cfg_n_filler; j++)
         {
              int additional_elements = (int)pow(2, j) ;

	      for (int m=0; m<cfg_n_filler; m++)
	      {
                   inputs.fill(i, cfg_filler[m]) ;
                   memopool.add(cfg_n_filler*j-m, i, (float *)inputs.get(), (float)ret) ;

                   // (b) add more pre-computed results (over-fill)
                   for (int k=1; k<additional_elements; k++)
	           {
                        inputs.fill(i, TestInputs::FILL_RANDOM) ;
                        memopool.add(cfg_n_filler*j-m, i, (float *)inputs.get(), (float)ret) ;
	           }
              }
         }
    }

/*DEBUG*/
/*
    for (int m=0; m<cfg_n_filler; m++)
    {
	 inputs.fill(n_eltos, cfg_filler[m]) ;
         printf("DEBUG fill=%d eltos=(%s)\n", m, inputs.toString().c_str()) ;
    }
*/
/*DEBUG*/

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
    double ret = setup_find1_vs_findn(n_eltos) ;
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


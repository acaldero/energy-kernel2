
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <assert.h>

#include <test_inputs.h>
#include <compute_vector.h>
#include <test_memo.h>


/*
 * Test listing
 */

TestInputs  inputs ;


/*
 * Test Scenario: values
 */

 const char *algos_name_cvsf[] = {
	                              "CUBIC", 
                                      "LINEAR", 
                                      "SQUARE", 
                                      "SQRT", 
                                      "PM1", 
                                      "PM2"
                                 } ;
 double (*algos_fn_cvsf[])(int, int, float *) = {
				      calculateConsumption_CUBIC,  
                                      calculateConsumption_LINEAR,
				      calculateConsumption_SQUARE, 
                                      calculateConsumption_SQRT,
				      calculateConsumption_PM1,    
                                      calculateConsumption_PM1
                                 } ;
       int   cfg_n_cvsf = sizeof(algos_fn_cvsf)/sizeof(void *) ;

 const char *cfg_names[]  = { 
                              "APPROX_ROUND",
                              "APPROX_TRUNC",
                              "APPROX_CEIL",
                              "APPROX_FLOOR"
                            } ;
       int   cfg_filler[] = { 
                              TestInputs::FILL_APPROX_ROUND,
                              TestInputs::FILL_APPROX_TRUNC,
                              TestInputs::FILL_APPROX_CEIL,
                              TestInputs::FILL_APPROX_FLOOR
                            } ;
       int   cfg_n_filler = sizeof(cfg_filler)/sizeof(int) ;


/*
 * Main
 */

int main ( int argc, char *argv[] )
{
    // 0.- parameters
    //
    if (argc < 2)
    {
        printf("\n") ;
        printf(" Compute-Consumption Kernel Benchmarking\n") ;
        printf(" ---------------------------------------\n") ;
        printf("\n") ;
        printf(" Usage: %s <number of input elements>\n", argv[0]) ;
        printf("   <number of input elements> = 1 | 2 | 3 | ... 1024\n") ;
        printf("       number of elements to compute its global consumption.\n") ;
        printf("\n") ;
        printf(" sizeof(MemoNode) = %ld\n", sizeof(struct MemoNode)) ;
        printf("\n") ;

        exit(-1) ;
    }

    int n_eltos = atoi(argv[1]) ;

    // header
    TestInputs inputs ;
    inputs.initialize(1024) ;

    printf("neltos;") ;
    for (int j=0; j<cfg_n_cvsf; j++) 
    {
	 for (int i=0; i<cfg_n_filler; i++) 
	 {
              printf("%s-%s;", algos_name_cvsf[j], cfg_names[i]) ; // ERR
	 }
    }
    printf("\n") ;

    // values
    double ret1, ret2 ;

    for (int k=1; k<n_eltos; k=k*2) // k++, k=k+5, k=k*2
    {
            printf("%d;", k) ;
	    for (int j=0; j<cfg_n_cvsf; j++)
	    {
           	    inputs.fill(k, TestInputs::FILL_WITHOUT_APPROX) ;
                    ret1 = algos_fn_cvsf[j](0, k, inputs.get()) ;

		    for (int i=0; i<cfg_n_filler; i++)
		    {
           	         inputs.fill(k, cfg_filler[i]) ;
                         ret2 = algos_fn_cvsf[j](0, k, inputs.get()) ;
                         printf("%.1lf;", 100.0 * (ret1 - ret2) / ret1) ;
		    }
	    }
            printf("\n") ;
    }

    // end
    return 0;
}


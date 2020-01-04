
/*
 *  Copyright 2015-2020 Gabriel García Castañe, Alejandro Calderón Mateos
 *
 *  This file is part of MemoizationStudy.
 *
 *  MemoizationStudy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MemoizationStudy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with MemoizationStudy.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


  #include <test_results.h>


    #define  MSG(x) #x
    #define MSG2(x) MSG(x)


    TestResults::TestResults ( )
    {
	    algos_results = NULL ;
    }

    TestResults::~TestResults ( )
    {
	    int i, j, k ;

	    for (i=0; i<algos.length(); i++)
	    {
		 for (j=0; j<inputs.length(); j++)
		 {
		      free(algos_results[i][j]) ;
		 }

		 free(algos_results[i]) ;
	    }

	    free(algos_results) ;
    }

    int   TestResults::initialize ( TestAlgorithms obj_algos, 
		                    TestInputs obj_inputs )
    {
	    algos  = obj_algos ;
	    inputs = obj_inputs ;

	    algos_results = (double ***)malloc(algos.length() * sizeof(double **)) ;
	    assert(algos_results != NULL) ;

	    for (int i=0; i<algos.length(); i++)
	    {
		 algos_results[i] = (double **)malloc(inputs.length() * sizeof(double *)) ;
		 assert(algos_results[i] != NULL) ;

		 for (int j=0; j<inputs.length(); j++)
		 {
		      algos_results[i][j] = (double *)malloc(N_RESULTS * sizeof(double)) ;
		      assert(algos_results[i][j] != NULL) ;

		      for (int k=0; k<N_RESULTS; k++) {
			   algos_results[i][j][k] = 0.0 ;
		      }
		 }
	    }

	    // end
	    return 0;
    }

    void   TestResults::set ( int algo_id, 
		              int elto_id, 
			      int result_id, 
			      int value )
    {
           algos_results[algo_id][elto_id][result_id] = value ;

	    // DEBUG
            // cout << "> algo_id: "   << algo_id   << "," 
	    //      << " elto_id: "    << elto_id   << "," 
	    //      << " result_id: "  << result_id << "," 
	    //      << " value: "      << value     << endl ; 
	    // DEBUG
    }

    double TestResults::get ( int algo_id, 
		              int elto_id, 
			      int result_id )
    {
           return algos_results[algo_id][elto_id][result_id] ;
    }

    int    TestResults::print_txt ( )
    {
            int ret2 ;

	    ret2 = results_print_txt_header((char *)"results-header-times.txt",  TIME_UNIT) ;
	    assert(ret2 >= 0) ;
	    ret2 = results_print_txt_footer((char *)"results-footer-times.txt",  BASE_CAPTION,  BASE_LABEL, (char *)"-times") ;
	    assert(ret2 >= 0) ;
	    ret2 = results_print_txt_header((char *)"results-header-values.txt", VALUE_UNIT) ;
	    assert(ret2 >= 0) ;
	    ret2 = results_print_txt_footer((char *)"results-footer-values.txt", BASE_CAPTION,  BASE_LABEL, (char *)"-values") ;
	    assert(ret2 >= 0) ;

	    int n_algos = algos.length() ;
	    for (int i=0; i<n_algos; i++)
	    {
		 ret2 = results_print_txt_results((char *)"results-times.txt",  i, algos.get_name(i), R_TIMES) ;
		 assert(ret2 >= 0) ;
		 ret2 = results_print_txt_results((char *)"results-values.txt", i, algos.get_name(i), R_VALUES) ;
		 assert(ret2 >= 0) ;
	    }

	    return 0 ;
    }

    int    TestResults::print_tex ( )
    {
            int ret2 ;

	    ret2 = results_print_tex_header((char *)"results-header-times.tex",  TIME_UNIT) ;
	    assert(ret2 >= 0) ;
	    ret2 = results_print_tex_header((char *)"results-header-values.tex", VALUE_UNIT) ;
	    assert(ret2 >= 0) ;
	    ret2 = results_print_tex_footer((char *)"results-footer-times.tex",  BASE_CAPTION,  BASE_LABEL, (char *)"-times") ;
	    assert(ret2 >= 0) ;
	    ret2 = results_print_tex_footer((char *)"results-footer-values.tex", BASE_CAPTION,  BASE_LABEL, (char *)"-values") ;
	    assert(ret2 >= 0) ;

	    int n_algos = algos.length() ;
	    for (int i=0; i<n_algos; i++)
	    {
		 ret2 = results_print_tex_results((char *)"results-times.tex",  i, algos.get_name(i), R_TIMES) ;
		 assert(ret2 >= 0) ;
		 ret2 = results_print_tex_results((char *)"results-values.tex", i, algos.get_name(i), R_VALUES) ;
		 assert(ret2 >= 0) ;
	    }

	    return 0 ;
    }

    int    TestResults::perform_test ( int n_tests )
    {
	    high_resolution_clock::time_point before, after ;
	    double rel, jiff = 0.3 ;
	    double ret ;

	    float *e_inputs = inputs.get() ;
	    int    n_algos  = algos.length() ;
	    int    n_eltos  = inputs.length() ;
	    for (int i=0; i<n_algos; i++)
	    {
		    for (int j=1; j<n_eltos; j=j*2) // j++, j=j+5, j=j*2
		    {
				 before = high_resolution_clock::now() ;
				 for (int k=0; k<n_tests; k++) {
				      ret = algos.perform(i, j, e_inputs) ;
				 }
				 after = high_resolution_clock::now() ;

				 duration<double, std::nano> elapsed = after - before ;

			 for (int m=0; i<10; i++)
			 {
				 before = high_resolution_clock::now() ;
				 for (int k=0; k<n_tests; k++) {
				      ret = algos.perform(i, j, e_inputs) ;
				 }
				 after = high_resolution_clock::now() ;

				 duration<double, std::nano> elapsed2 = after - before ;

				 rel = elapsed2.count() / elapsed.count() ;
				 if ( (rel < 1.0+jiff) && (rel > 1.0-jiff) ) {
				       break ;
				 }
				 elapsed = elapsed2 ;
		         }

			 set(i, j, R_TIMES,  elapsed.count() / (double)n_tests) ;
			 set(i, j, R_VALUES, ret) ;

			 /*DEBUG*/
			 //printf("DEBUG idalgo=%s eltos=(%s) value=%f time=%0.2f\n", 
          		 //        algos.get_name(i), inputs.toString().c_str(), ret, elapsed.count() / (double)n_tests) ;
		    }
	    }

	    //
	    return 0 ;
    }


    //
    // Auxiliar
    //

    int    TestResults::results_print_txt_header ( char *fname, 
		                                   char *unit )
    {
	    int   j ;
	    FILE *fd ;

	    fd = fopen(fname, "w+") ;
	    if (fd == NULL) {
		perror("fopen") ;
		return -1 ;
	    }

	    fprintf(fd, "\"CPU\";\"Opt.\";\"Alg.\";") ;
  	       for (j=1; j<inputs.length(); j=j*2) // j++, j=j+5, j=j*2
	       { 
		    fprintf(fd, "%i;", j) ;
	       }
	    fprintf(fd, "\n") ;

	    fclose(fd) ;
	    return 0;
    }

    int    TestResults::results_print_txt_results ( char *fname, 
		                                    int aid, 
						    char *aname, 
						    int values )
    {
	    int j ;
	    char * cpu_used ;
	    char * opt_used ;
	    FILE *fd ;

	    fd = fopen(fname, "a+") ;
	    if (fd == NULL) {
		perror("fopen") ;
		return -1 ;
	    }

	    cpu_used = (char *)MSG2(CPU) ;
	    opt_used = (char *)MSG2(OPT) ;

	    fprintf(fd, "\"%s\";\"%s\";\"%s\";", cpu_used, opt_used, aname) ;
	       for (j=1; j<inputs.length(); j=j*2) // j++, j=j+5, j=j*2
	       {
	      	    fprintf(fd, "%.0lf;", get(aid, j, values)) ;
	       }
	    fprintf(fd, "\n") ;

	    fclose(fd) ;
	    return 0;
    }

    int    TestResults::results_print_txt_footer ( char *fname, 
		                                   char *base_caption, 
						   char *base_label, 
						   char *suffix )
    {
	    FILE *fd ;

	    fd = fopen(fname, "w+") ;
	    if (fd == NULL) {
		perror("fopen") ;
		return -1 ;
	    }

	    fprintf(fd, "\n") ;

	    fclose(fd) ;
	    return 0;
    }


    int    TestResults::results_print_tex_header ( char *fname, 
		                                   char *units )
    {
	    int j ;
	    FILE *fd ;

	    fd = fopen(fname, "w+") ;
	    if (fd == NULL) {
		perror("fopen") ;
		return -1 ;
	    }

	    fprintf(fd, "%% header\n") ;

	  //fprintf(fd, "\\begin{table}[hbt]\n") ;
	    fprintf(fd, "\\begin{sidewaystable}[hbt]\n") ;
	    fprintf(fd, "\\renewcommand{\\arraystretch}{1.3}\n") ;
	    fprintf(fd, "\\centering \\footnotesize\n") ;
	    fprintf(fd, "\n") ;
	  //fprintf(fd, "\\begin{tabular}{|l|l|") ;
	    fprintf(fd, "\\begin{tabularx}{\\linewidth}{|l|l|") ;
	       for (j=1; j<(inputs.length()-1); j=j*2) // j++, j=j+5, j=j*2
	       { 
		    fprintf(fd, "l|") ;
	       }
	    fprintf(fd, "}\n") ;
	    fprintf(fd, "\\hline\n") ;

	    fprintf(fd, "\\multirow{2}{*}{Opt} &  \n") ;
	    fprintf(fd, "\\multirow{2}{*}{Algorithm} & \n") ;
	    fprintf(fd, "\\multicolumn{%d}{c|}{Number elements / %s} \\\\ \n", inputs.length()-1, units) ;
	    fprintf(fd, "\\cline{3-%d}\n", inputs.length()+1) ;

	    fprintf(fd, "\\multicolumn{1}{|l|}{} &\n") ;
	    fprintf(fd, "\\multicolumn{1}{|l|}{} &\n") ;
	    for (j=1; j<inputs.length()-2; j++) {
		 fprintf(fd, "\\multicolumn{1}{c}{%d} &\n", j) ;
	    }
	    fprintf(fd, "\\multicolumn{1}{c|}{%d} \\\\\n", inputs.length()-2) ;
	    fprintf(fd, "\\hline\n") ;
	    fprintf(fd, "\n") ;

	    fclose(fd) ;
	    return 0;
    }

    int    TestResults::results_print_tex_results ( char *fname, 
		                                    int aid, 
						    char *aname, 
						    int values )
    {
	    int j ;
	    FILE *fd ;

	    fd = fopen(fname, "a+") ;
	    if (fd == NULL) {
		perror("fopen") ;
		return -1 ;
	    }

	    if (0 == aid) {
		fprintf(fd, "%% results for %s\n", aname) ;
		fprintf(fd, "\\multirow{2}{*}{%s} &\n", MSG2(OPT)) ;
	    }
	    else {
		fprintf(fd, "%% results for %s\n", aname) ;
		fprintf(fd, "\\multicolumn{1}{|l|}{} &\n") ;
	    }

	    fprintf(fd, "\\multicolumn{1}{|l|}{%s} &\n", aname) ;
	       for (j=1; j<inputs.length()-2; j=j*2) // j++, j=j+5, j=j*2
	       { 
		    fprintf(fd, "\\multicolumn{1}{c}{%.0lf} &\n", get(aid, j, values)) ;
	       }
	    fprintf(fd, "\\multicolumn{1}{c|}{%.0lf} \\\\\n",     get(aid, inputs.length()-1, values)) ;

	    if (aid == (algos.length() - 1)) {
		 fprintf(fd, "\\hline\n") ;
	    }
	    else {
		 fprintf(fd, "\\cline{2-%d}\n", inputs.length()+1) ;
	    }
	    fprintf(fd, "\n") ;

	    fclose(fd) ;
	    return 0;
    }

    int    TestResults::results_print_tex_footer ( char *fname, 
		                                   char *base_caption, 
						   char *base_label, 
						   char *suffix )
    {
	    FILE *fd ;

	    fd = fopen(fname, "w+") ;
	    if (fd == NULL) {
		perror("fopen") ;
		return -1 ;
	    }

	  //fprintf(fd, "\\end{tabular}\n") ;
	    fprintf(fd, "\\end{tabularx}\n") ;
	    fprintf(fd, "\n") ;
	    fprintf(fd, "\\caption{%s.}\n", base_caption) ;
	    fprintf(fd, "\\label{%s-%s}\n", base_label, suffix) ;
	  //fprintf(fd, "\\end{table}\n") ;
	    fprintf(fd, "\\end{sidewaystable}\n") ;
	    fprintf(fd, "\n") ;

	    fclose(fd) ;
	    return 0;
    }


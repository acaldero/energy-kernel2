
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

#ifndef TEST_RESULTS_H
#define TEST_RESULTS_H


  #include <stdio.h>
  #include <stdarg.h>
  #include <assert.h>

  #include <iostream>
  #include <string>
  #include <sstream>

  #include <chrono>
  using namespace std::chrono;

  #include <test_inputs.h>
  #include <test_algorithms.h>

  using namespace std;

	  class TestResults
          {
		private:
		    char * TIME_UNIT    = (char *)"Time elapsed (us)" ;
		    char * VALUE_UNIT   = (char *)"Values computed" ;
		    char * BASE_CAPTION = (char *)"Energy simulation models analysis for cloud computing systems" ;
		    char * BASE_LABEL   = (char *)"table_results_energy_models" ;

                    double          ***algos_results ;
                    TestAlgorithms     algos ;
		    TestInputs         inputs ;

		    int    results_print_txt_header  ( char *fname, char *unit ) ;
		    int    results_print_txt_results ( char *fname, int aid, char *aname, int values ) ;
		    int    results_print_txt_footer  ( char *fname, char *base_caption, char *base_label, char *suffix ) ;
		    int    results_print_tex_header  ( char *fname, char *units ) ;
		    int    results_print_tex_results ( char *fname, int aid, char *aname, int values ) ;
		    int    results_print_tex_footer  ( char *fname, char *base_caption, char *base_label, char *suffix ) ;


		public:
		    int    N_RESULTS = 2 ;
		    int    R_VALUES  = 0 ;
		    int    R_TIMES   = 1 ;

		     TestResults ( ) ;
		    ~TestResults ( ) ;

                    int    initialize   ( TestAlgorithms algos, TestInputs inputs ) ;
		    void   set          ( int algo_id, int elto_id, int result_id, 
				          int value ) ;
		    double get          ( int algo_id, int elto_id, int result_id ) ;
		    int    print_txt    ( ) ;
		    int    print_tex    ( ) ;
                    int    perform_test ( int n_tests ) ;
	  } ;

#endif


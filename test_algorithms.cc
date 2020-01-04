
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


  #include <test_algorithms.h>


    TestAlgorithms::TestAlgorithms ( )
    {
	  n_algos    = 0 ;
	  algos_name = NULL ;
	  algos_fn   = NULL ;
    }

    TestAlgorithms::~TestAlgorithms ( )
    {
    }

    int   TestAlgorithms::initialize ( int n_alg )
    {
	  n_algos = n_alg ;

	  algos_name = (char **) malloc(n_alg * sizeof(char *)) ;
	  assert(algos_name != NULL) ;

	  algos_fn = (double (**)(int, int, float *)) malloc(n_alg * sizeof(void *)) ;
	  assert(algos_fn != NULL) ;

	  for (int i=0; i<n_alg; i++) 
	  {
	       algos_name[i] = NULL ;
	         algos_fn[i] = NULL ;
	  }

	  // return ok
	  return 0 ;
    }

    int    TestAlgorithms::length ( )
    {
           return n_algos ;
    }

    void   TestAlgorithms::set ( int algo_id, 
		                 double (*algo_fn)(int, int, float *), 
				 char *algo_name )
    {
	    algos_fn[algo_id] = algo_fn ;
          algos_name[algo_id] = algo_name ;
    }

    double TestAlgorithms::perform ( int algo_id, 
		                     int n_eltos, 
				     float *inputs )
    {
           return algos_fn[algo_id](algo_id, n_eltos, inputs) ;
    }

    char  *TestAlgorithms::get_name ( int index )
    {
           return algos_name[index] ;
    }


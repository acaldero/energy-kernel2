
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

#ifndef TEST_ALGORITHM_H
#define TEST_ALGORITHM_H


  #include <stdio.h>
  #include <stdarg.h>
  #include <assert.h>

  #include <string>       // std::string
  #include <sstream>

  using namespace std;

	  class TestAlgorithms 
          {
		private:
		    int        n_algos ;
		    char     **algos_name ;
		    double  (**algos_fn)(int, int, float *) ;

		public:
		     TestAlgorithms ( ) ;
		    ~TestAlgorithms ( ) ;

                    int    initialize ( int n_alg ) ;
                    void   set        ( int index, double (*algo_fn)(int, int, float *), char *algo_name ) ;
                    double perform    ( int algo_id, int n_eltos, float *inputs ) ;
                    int    length     ( ) ;
                    char  *get_name   ( int index ) ;
	  } ;

#endif


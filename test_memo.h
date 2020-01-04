
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

#ifndef TEST_MEMO_H
#define TEST_MEMO_H


  #include <stdio.h>
  #include <stdarg.h>
  #include <assert.h>

  #include <string>       // std::string
  #include <sstream>

  #include <memoization_uthash.h>
  #include <test_inputs.h>

  using namespace std;

	  class TestMemo 
          {
		private:
                    MemoSupport **mempool ;

		public:
		     TestMemo ( ) ; // OK
		    ~TestMemo ( ) ;

                    int          initialize ( int n_eltos ) ;
                    MemoSupport *get        ( int index ) ;
                    void         add        ( int index, int n_inputs, float *inputs, float value ) ;
                    double      *find       ( int index, int n_inputs, float *inputs ) ;
	  } ;

#endif


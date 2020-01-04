
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

#ifndef TEST_INPUTS_H
#define TEST_INPUTS_H


  #include <stdio.h>
  #include <stdarg.h>
  #include <assert.h>

  #include <cmath>
  #include <cstdint>
  #include <iostream>

  #include <string>       // std::string
  #include <sstream>

  using namespace std;

	  class TestInputs 
          {
		private:
		    int     vlength ;
		    float  *vint ;

		public:
		    static const int FILL_WITHOUT_APPROX = 0 ;
		    static const int FILL_RANDOM         = 1 ;
		    static const int FILL_APPROX_TRUNC   = 3 ;
		    static const int FILL_APPROX_CEIL    = 4 ;
		    static const int FILL_APPROX_FLOOR   = 5 ;
		    static const int FILL_APPROX_ROUND   = 6 ;

                    static std::string toString ( int n_eltos, float *inputs ) ;

		     TestInputs ( ) ;
		    ~TestInputs ( ) ;

                    int         length     ( void ) ;
                    void        set        ( int index, double value ) ;
                    float      *get        ( void ) ;
		    float       approx     ( float value ) ;
                    void        fill       ( int n_eltos, int  fill_type ) ;
                    int         initialize ( int n_inputs ) ;
                    std::string toString   ( void ) ;
	  } ;

#endif


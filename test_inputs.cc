
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


  #include <test_inputs.h>


    TestInputs::TestInputs ( )
    {
            vlength = 0 ;
            vint    = NULL ;

	    srand(1) ;
	 // srand (time(NULL));
    }

    TestInputs::~TestInputs ( )
    {
    }


    // public

    int    TestInputs::length ( void )
    {
            return vlength ;
    }

    void   TestInputs::set ( int index, 
		             double value )
    {
            vint[index] = value ;
    }

    float *TestInputs::get ( void )
    {
            return vint ;
    }

	  //https://en.cppreference.com/w/cpp/numeric/bit_cast
	  //
	  // bitwise
	  //  auto abits = std::bit_cast<int32_t>(value) ;
	  //  return std::bit_cast<float>(abits & 0xf'fff0'0000'0000) ;
	  //
	  //http://www.cplusplus.com/reference/cmath/trunc/
	  //
	  // value   round   floor   ceil    trunc
          // -----   -----   -----   ----    -----
          //  2.3     2.0     2.0     3.0     2.0
          //  3.8     4.0     3.0     4.0     3.0
          //  5.5     6.0     5.0     6.0     5.0
          // -2.3    -2.0    -3.0    -2.0    -2.0
          // -3.8    -4.0    -4.0    -3.0    -3.0
          // -5.5    -6.0    -6.0    -5.0    -5.0
	  //

/*
    void  TestInputs::fill_0 ( int    n_eltos, 
			       int    fill_type )
    {
	    float value = 0.0 ;

	    for (int i=0; i<n_eltos; i++) 
	    {
		    switch (fill_type) 
		    {
			case TestInputs::FILL_WITHOUT_APPROX:
			     value = ((float) i) ;
			     break ;
			case TestInputs::FILL_RANDOM:
			     value = (float)(rand() % n_eltos) ;
			     break ;
			case TestInputs::FILL_LINEAL_NEXT:
			     value =      ((float) i + ((float) i / (float) (i+1)) / ((float) n_eltos)) ;
			     break ;
			case TestInputs::FILL_APPROX_TRUNC:
			     value = trunc((float) i + ((float) i / (float) (i+1)) / ((float) n_eltos)) ;
			     break ;
			case TestInputs::FILL_APPROX_CEIL:
			     value = ceil((float) i + ((float) i / (float) (i+1)) / ((float) n_eltos)) ;
			     break ;
			case TestInputs::FILL_APPROX_FLOOR:
			     value = floor((float) i + ((float) i / (float) (i+1)) / ((float) n_eltos)) ;
			     break ;
			case TestInputs::FILL_APPROX_ROUND:
			     value = round((float) i + ((float) i / (float) (i+1)) / ((float) n_eltos)) ;
			     break ;
			default:
			     vint[i] = ((float) i) ;
			     break ;
		    }

		    vint[i] = value ;
	    }
    }
*/

                         /* CPU-1,  CPU-2, CPU-3, CPU-4 */
    float semilla[4] = {    12.34,  10.26, 50.62, 80.87     } ;

    void  TestInputs::fill ( int    n_eltos, 
			     int    fill_type )
    {
	    float value = 0.0 ;

	    for (int i=0; i<n_eltos; i++) 
	    {
		    switch (fill_type) 
		    {
			case TestInputs::FILL_WITHOUT_APPROX:
			     value = i + semilla[i % 4] ;
			     break ;
			case TestInputs::FILL_RANDOM:
			     value = (float)(rand() % n_eltos) ;
			     break ;
			case TestInputs::FILL_APPROX_TRUNC:
			     value = trunc(i + semilla[i % 4]) ;
			     break ;
			case TestInputs::FILL_APPROX_CEIL:
			     value = ceil(i + semilla[i % 4]) ;
			     break ;
			case TestInputs::FILL_APPROX_FLOOR:
			     value = floor(i + semilla[i % 4]) ;
			     break ;
			case TestInputs::FILL_APPROX_ROUND:
			     value = round(i + semilla[i % 4]) ;
			     break ;
			default:
			     vint[i] = ((float) semilla[i % 4]) ;
			     break ;
		    }

		    vint[i] = value ;
	    }
    }

    int   TestInputs::initialize ( int n_eltos )
    {
	    vlength = n_eltos ;

	    vint = (float *)malloc(n_eltos * sizeof(float)) ;
	    assert(vint != NULL) ;
            fill(n_eltos, FILL_WITHOUT_APPROX) ;

	    // end
	    return 0;
    }

    std::string TestInputs::toString ( void )
    {
            float *inputs = get() ;
	    std::string floatString;

            int n_eltos = length() ;
	    for (int i=0; i<n_eltos; i++)
	    {
		 floatString.append(std::to_string(inputs[i])) ;
		 if (i != (n_eltos-1)) {
		     floatString.append("#") ;
		 }
	    }

	    return floatString ;
    }

    std::string TestInputs::toString ( int n_eltos, float *inputs )
    {
	    std::string floatString;

	    for (int i=0; i<n_eltos; i++)
	    {
		 floatString.append(std::to_string(inputs[i])) ;
		 if (i != (n_eltos-1)) {
		     floatString.append("#") ;
		 }
	    }

	    return floatString ;
    }


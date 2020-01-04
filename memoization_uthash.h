
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

#ifndef MEMOIZATION_UTHASH_H
#define MEMOIZATION_UTHASH_H


  #include <stdio.h>
  #include <stdarg.h>
  #include <sys/time.h>
  #include <zlib.h>

  #include "uthash.h"

  #include <iostream>
  #include <cstdlib>
  #include <limits>
  #include <iomanip>

  #include <string>       // std::string
  #include <sstream>

  using namespace std;

	  struct MemoNode 
          {
		    float   *id;
		    long     id_size;
		    double   result_value ;
		    long     hits ;
		    bool     need_free ;
		    UT_hash_handle hh;
	  } ;

	  class MemoSupport 
          {
		private:
		    MemoNode  *memo_calls ;
		    bool       memo_isDirty ;
		    bool       memo_isEnable ;
		    char       file_name[1024] ;
		    char       component_name[1024] ;

		    void restore_bin ( void ) ;


		public:
		     MemoSupport ( string component ) ;
		    ~MemoSupport ( ) ;

		    string getComponentName() { return component_name;};

		    void    dump_bin       ( void ) ;
		    double *find           ( unsigned int bsize, float *b ) ;
		    void    add            ( unsigned int bsize, float *b, double ) ;
		    void    add_mallocated ( unsigned int bsize, float *b, double ) ;
		    void    stats          ( void ) ;
	  } ;

#endif



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

#ifndef COMPUTE_VECTOR_H
#define COMPUTE_VECTOR_H


  #include <stdio.h>
  #include <stdarg.h>
  #include <assert.h>

  #include <cmath>
  #include <cstdint>
  #include <iostream>

  #include <string>       // std::string
  #include <sstream>


	// Cubic
	double calculateConsumption_CUBIC ( int id, int n_eltos, float *utilization ) ;

	// Linear
	double calculateConsumption_LINEAR ( int id, int n_eltos, float *utilization ) ;

	// Square
	double calculateConsumption_SQUARE ( int id, int n_eltos, float *utilization ) ;

	// SQRT
	double calculateConsumption_SQRT ( int id, int n_eltos, float *utilization ) ;

	// PM1: SPEC Benchmarking Software (WP7_Slides...)
	double calculateConsumption_PM1 ( int id, int n_eltos, float *utilization ) ;

	// PM2: SPEC Benchmarking Software (WP7_Slides...)
	double calculateConsumption_PM2 ( int id, int n_eltos, float *utilization ) ;


#endif


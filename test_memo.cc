
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


  #include <test_memo.h>


    TestMemo::TestMemo ( )
    {
            mempool = NULL ;
    }

    TestMemo::~TestMemo ( )
    {
    }

    int   TestMemo::initialize ( int n_eltos )
    {
	    mempool = (MemoSupport **)malloc(n_eltos * sizeof(MemoSupport *)) ;
	    assert(mempool != NULL) ;

	    for (int j=0; j<n_eltos; j++) {
		 mempool[j] = new MemoSupport("testing") ;
	         assert(mempool[j] != NULL) ;
	    }

	    // end
	    return 0;
    }

    MemoSupport *TestMemo::get ( int index )
    {
            return mempool[index] ;
    }

    void  TestMemo::add ( int index, int n_inputs, float *inputs, float value )
    {
            mempool[index]->add(n_inputs * sizeof(float), inputs, value) ;

	    // DEBUG
            // cout << "> mempool: " << index << "," 
	    //      << " key: "      << TestInputs::toString(n_inputs, inputs) << "," 
	    //      << " value: "    << value << endl ; 
	    // DEBUG
    }

    double *TestMemo::find ( int index, int n_inputs, float *inputs )
    {
            return mempool[index]->find(n_inputs * sizeof(float), inputs) ;
    }


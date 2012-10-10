// Copyright (C) 2012 The contributors of aire
//
// This program is free software: you can redistribute it and/or modify  
// it under the terms of the GNU General Public License as published by  
// the Free Software Foundation, either version 3 of the License.  
//
// This program is distributed in the hope that it will be useful,  
// but WITHOUT ANY WARRANTY; without even the implied warranty of  
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
// GNU General Public License for more details.  
//
// You should have received a copy of the GNU General Public License  
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//! \file BlameMatrix.h
//! \brief Test case for basic matrix tests. 
#ifndef BLAMEMATRIX_H
#define BLAMEMATRIX_H

#include <cstdlib>
#include <cstdint>
#include <iomanip>
#include <functional>
#include <cmath>

#include "Blame.h"
#include "Tools.h"

template<class TYPE, uint32_t N>
int32_t compDet() {
   int32_t result = EXIT_SUCCESS;
   if(N <= 4 && N > 1)
   {
      std::function<uint32_t (uint32_t, uint32_t)> idx = aire::idx1d<4>;
  
      TYPE A[16];
      A[idx(0,0)] =  2; A[idx(0,1)] =  1; A[idx(0,2)] =  5; A[idx(0,3)] = 0;
      A[idx(1,0)] =  3; A[idx(1,1)] =  4; A[idx(1,2)] =  8; A[idx(1,3)] = 0;
      A[idx(2,0)] =  6; A[idx(2,1)] = 13; A[idx(2,2)] = 18; A[idx(2,3)] = 0;
      A[idx(3,0)] =  0; A[idx(3,1)] =  0; A[idx(3,2)] =  0; A[idx(3,3)] = 1; 

      // Scle the vector
      double value = aire::det<TYPE,N>(A, aire::idx1d<4>);

      // Verify the result
      if(fabs(value-5.0) > 1e-16 && !aire::isnan(value))
      {
         result = EXIT_FAILURE;
         std::cout << "Error determinant is :" << value << std::endl;
      } 
   }
   else if(N == 1)
   {
      TYPE A = 2;
      double value = aire::det<TYPE,N>(&A, aire::idx1d<1>);
      // Verify the result
      if(fabs(value-0.5) > 1e-16 && !aire::isnan(value))
      {
         result = EXIT_FAILURE;
         std::cout << "Error determinant is :" << value << std::endl;
      }       
   }
   else
   {
      std::cerr << "Test case not implemented for N = " << N << std::endl;
      result = EXIT_FAILURE;
   }    
   return result;
}

#endif

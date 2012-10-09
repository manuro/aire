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
//! \file VectorAxpy.h
//! \brief Test case for axpy vector operations. 
#ifndef VECTORAXPY_H
#define VECTORAXPY_H

#include <cstdlib>
#include <cstdint>
#include <iomanip>
#include <cmath>
#include "Blame.h"

template<class TYPE, uint32_t N>
int32_t axpyPositive() {
   int32_t result = EXIT_SUCCESS;
   TYPE x[N];
   TYPE y[N];
   TYPE alpha = 3.14;
   TYPE value = 7.28;
   
   // Initialize the vector
   for(uint32_t i = 0; i < N; i++)
   {
      x[i] = 2.0;
      y[i] = 1.0;
   }
   
   // Scle the vector
   axpy<TYPE,N>(alpha, x, y);
   
   // Verify the result
   for(uint32_t i = 0; i < N; i++)
   {
      if(fabs(value-y[i]) > 1e-16)
      {
         result = EXIT_FAILURE;
         std::cout << "Error " << i << " " 
            << std::scientific << x[i] 
            << std::resetiosflags(::std::ios::scientific) 
            << std::endl;
         break;
      }
   }   
        
   return result;
}

template<class TYPE, uint32_t N>
int32_t axpyNegative() {
   int32_t result = EXIT_SUCCESS;
   TYPE x[N];
   TYPE y[N];
   TYPE alpha = -1;
   TYPE value = -1;
   
   // Initialize the vector
   for(uint32_t i = 0; i < N; i++)
   {
      x[i] = 2.0;
      y[i] = 1.0;
   }
   
   // Scle the vector
   axpy<TYPE,N>(alpha, x, y);
   
   // Verify the result
   for(uint32_t i = 0; i < N; i++)
   {
      if(fabs(value-y[i]) > 1e-16)
      {
         result = EXIT_FAILURE;
         std::cout << "Error " << i << " " 
            << std::scientific << x[i] 
            << std::resetiosflags(::std::ios::scientific) 
            << std::endl;
         break;
      }
   }   
        
   return result;
}

template<class TYPE, uint32_t N>
int32_t axpyNeutral() {
   int32_t result = EXIT_SUCCESS;
   TYPE x[N];
   TYPE y[N];
   TYPE alpha = 1.0;
   TYPE value = 3.0;
   
   // Initialize the vector
   for(uint32_t i = 0; i < N; i++)
   {
      x[i] = 2.0;
      y[i] = 1.0;
   }
   
   // Scle the vector
   axpy<TYPE,N>(alpha, x, y);
   
   // Verify the result
   for(uint32_t i = 0; i < N; i++)
   {
      if(fabs(value-y[i]) > 1e-16)
      {
         result = EXIT_FAILURE;
         std::cout << "Error " << i << " " 
            << std::scientific << x[i] 
            << std::resetiosflags(::std::ios::scientific) 
            << std::endl;
         break;
      }
   }   
        
   return result;
}

template<class TYPE, uint32_t N>
int32_t axpyZero() {
   int32_t result = EXIT_SUCCESS;
   TYPE x[N];
   TYPE y[N];
   TYPE alpha = 0;
   TYPE value = 1.0;
   
   // Initialize the vector
   for(uint32_t i = 0; i < N; i++)
   {
      x[i] = 2.0;
      y[i] = 1.0;
   }
   
   // Scle the vector
   axpy<TYPE,N>(alpha, x, y);
   
   // Verify the result
   for(uint32_t i = 0; i < N; i++)
   {
      if(fabs(value-y[i]) > 1e-16)
      {
         result = EXIT_FAILURE;
         std::cout << "Error " << i << " " 
            << std::scientific << x[i] 
            << std::resetiosflags(::std::ios::scientific) 
            << std::endl;
         break;
      }
   }   
        
   return result;
}
#endif

// Copyright (C) 2012 The contributors of aire
//
// This program is free software: you can redistribute it and/or modify  
// it under the terms of the GNU General Public License A published by  
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
//! \file Blame.h
//! \brief Basic Linear Algebra Methods Ensemble. 
#ifndef BLAME_H
#define BLAME_H

#include <functional>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

//! \brief Global aire namespace.
namespace aire 
{

//! \brief Scales a vector.
//! \param a The scalar for the multiplication with x.
//! \param x Vector with N elements.
//!
//! This function computes: x = a * x with scalar a and vector x.
template<class TYPE, uint32_t N>
inline void scal(const TYPE a, TYPE* x)
{
   if(a != 0)
   {
      for(uint32_t i = 0; i < N; i++)
      {
         x[i] *= a;
      }  
   }
}

//! \brief Vector-Vector addition with a scalar multiplication.
//! \param a The scalar for the multiplication with x.
//! \param x Vector with N elements.
//! \param y Vector with N elements.
//!
//! This function computes: y = a * x + y with scalar alpha, vector x and y.
template<class TYPE, uint32_t N>
inline void axpy(const TYPE a, TYPE* x, TYPE* y)
{
   if(a == 1)
   {
      for(uint32_t i = 0; i < N; i++)
      {
         y[i] += x[i];
      }   
   }
   else if(a == -1)
   {
      for(uint32_t i = 0; i < N; i++)
      {
         y[i] -= x[i];
      }   
   }
   else if(a != 0)
   {
      for(uint32_t i = 0; i < N; i++)
      {
         y[i] += a * x[i];
      }  
   }   
}

//! \brief Creates an identity matrix.
//! \param A The matrix.
//! \param idx Function to index the matrix. 
template<class TYPE, uint32_t N>
inline void eye(TYPE* A, std::function<uint32_t (uint32_t, uint32_t)> idx)
{
   memset(A, 0, N*N*sizeof(TYPE));
   for(uint32_t i = 0; i < N; i++)
   {
      A[idx(i,i)] = 1;
   }
}

//! \brief Computes the determinat of a matrix.
//! \param A Matrix of size (NxN).
//! \param idx Function to index the matrix. 
//! \return The determinat of the matrix
template<class TYPE, uint32_t N>
inline TYPE det(const TYPE* A, std::function<uint32_t (uint32_t, uint32_t)> idx)
{
   TYPE d = 0;
   
   if(N == 4)
   {
      d = A[idx(0,0)]*A[idx(1,1)]*A[idx(2,2)]*A[idx(3,3)]
        + A[idx(0,0)]*A[idx(1,2)]*A[idx(2,3)]*A[idx(3,1)]
        + A[idx(0,0)]*A[idx(1,3)]*A[idx(2,1)]*A[idx(3,2)]
        + A[idx(0,1)]*A[idx(1,0)]*A[idx(2,3)]*A[idx(3,2)]
        + A[idx(0,1)]*A[idx(1,2)]*A[idx(2,0)]*A[idx(3,3)]
        + A[idx(0,1)]*A[idx(1,3)]*A[idx(2,2)]*A[idx(3,0)]
        + A[idx(0,2)]*A[idx(1,0)]*A[idx(2,1)]*A[idx(3,3)]
        + A[idx(0,2)]*A[idx(1,1)]*A[idx(2,3)]*A[idx(3,0)]
        + A[idx(0,2)]*A[idx(1,3)]*A[idx(2,0)]*A[idx(3,1)]       
        + A[idx(0,3)]*A[idx(1,0)]*A[idx(2,2)]*A[idx(3,1)]
        + A[idx(0,3)]*A[idx(1,1)]*A[idx(2,0)]*A[idx(3,2)]
        + A[idx(0,3)]*A[idx(1,2)]*A[idx(2,1)]*A[idx(3,0)]
        - A[idx(0,0)]*A[idx(1,1)]*A[idx(2,3)]*A[idx(3,2)]
        - A[idx(0,0)]*A[idx(1,2)]*A[idx(2,1)]*A[idx(3,3)]
        - A[idx(0,0)]*A[idx(1,3)]*A[idx(2,2)]*A[idx(3,1)]           
        - A[idx(0,1)]*A[idx(1,0)]*A[idx(2,2)]*A[idx(3,3)]
        - A[idx(0,1)]*A[idx(1,2)]*A[idx(2,3)]*A[idx(3,0)]
        - A[idx(0,1)]*A[idx(1,3)]*A[idx(2,0)]*A[idx(3,2)]
        - A[idx(0,2)]*A[idx(1,0)]*A[idx(2,3)]*A[idx(3,1)]
        - A[idx(0,2)]*A[idx(1,1)]*A[idx(2,0)]*A[idx(3,3)]
        - A[idx(0,2)]*A[idx(1,3)]*A[idx(2,1)]*A[idx(3,0)]            
        - A[idx(0,3)]*A[idx(1,0)]*A[idx(2,1)]*A[idx(3,2)]
        - A[idx(0,3)]*A[idx(1,1)]*A[idx(2,2)]*A[idx(3,0)]
        - A[idx(0,3)]*A[idx(1,2)]*A[idx(2,0)]*A[idx(3,1)];
   }
   else if(N == 3)
   {
      //     | a b c |
      // A = | d e f | -> det(A) = aei + bfg + cdh - ceg - bdi - afh
      //     | g h i |
      d = A[idx(0,0)]*A[idx(1,1)]*A[idx(2,2)] 
        + A[idx(0,1)]*A[idx(1,2)]*A[idx(2,0)] 
        + A[idx(0,2)]*A[idx(1,0)]*A[idx(2,1)] 
        - A[idx(0,2)]*A[idx(1,1)]*A[idx(2,0)] 
        - A[idx(0,1)]*A[idx(1,0)]*A[idx(2,2)] 
        - A[idx(0,0)]*A[idx(1,2)]*A[idx(2,1)];
   }
   else if(N == 2)
   {
      //     | a b |
      // A = | c d | -> det(A) = ad - bc
      d = A[idx(0,0)]*A[idx(1,1)] - A[idx(0,1)]*A[idx(1,0)];
   }
   else if(N == 1)
   {
      // A = | a | -> det(A) = 1 / a
      d = A[idx(0,0)];
   }
   return d;
}

//! \brief Computes the inverse of the matrix.
//! \param A Matrix of size (NxN).
//! \param idx Function to index the matrix. 
//! \throw std::logic_error If det(A) < 1e-15
template<class TYPE, uint32_t N>
inline void inv(TYPE* A, std::function<uint32_t (uint32_t,uint32_t)> idx) 
throw(std::logic_error)
{
   TYPE d = det<TYPE,N>(A, idx);

   if(fabs(d-0) < 1e-15)
   {
      throw std::logic_error("Det is too small! Was " + std::to_string(d));
   }

   TYPE r = 1 / d;
   TYPE B[N*N];
   
   if(N == 4)
   {
      B[idx(0,0)] = A[idx(1,1)]*A[idx(2,2)]*A[idx(3,3)] 
                  + A[idx(1,2)]*A[idx(2,3)]*A[idx(3,1)] 
                  + A[idx(1,3)]*A[idx(2,1)]*A[idx(3,2)] 
                  - A[idx(1,1)]*A[idx(2,3)]*A[idx(3,2)]
                  - A[idx(1,2)]*A[idx(2,1)]*A[idx(3,3)] 
                  - A[idx(1,3)]*A[idx(2,2)]*A[idx(3,1)];

      B[idx(0,1)] = A[idx(0,1)]*A[idx(2,3)]*A[idx(3,2)] 
                  + A[idx(0,2)]*A[idx(2,1)]*A[idx(3,3)] 
                  + A[idx(0,3)]*A[idx(2,2)]*A[idx(3,1)] 
                  - A[idx(0,1)]*A[idx(2,2)]*A[idx(3,3)] 
                  - A[idx(0,2)]*A[idx(2,3)]*A[idx(3,1)] 
                  - A[idx(0,3)]*A[idx(2,1)]*A[idx(3,2)];
        
      B[idx(0,2)] = A[idx(0,1)]*A[idx(1,2)]*A[idx(3,3)] 
                  + A[idx(0,2)]*A[idx(1,3)]*A[idx(3,1)] 
                  + A[idx(0,3)]*A[idx(1,1)]*A[idx(3,2)] 
                  - A[idx(0,1)]*A[idx(1,3)]*A[idx(3,2)] 
                  - A[idx(0,2)]*A[idx(1,1)]*A[idx(3,3)] 
                  - A[idx(0,3)]*A[idx(1,2)]*A[idx(3,1)];

      B[idx(0,3)] = A[idx(0,1)]*A[idx(1,3)]*A[idx(2,2)] 
                  + A[idx(0,2)]*A[idx(1,1)]*A[idx(2,3)] 
                  + A[idx(0,3)]*A[idx(1,2)]*A[idx(2,1)]
                  - A[idx(0,1)]*A[idx(1,2)]*A[idx(2,3)]
                  - A[idx(0,2)]*A[idx(1,3)]*A[idx(2,1)] 
                  - A[idx(0,3)]*A[idx(1,1)]*A[idx(2,2)];
// --------------------------------------------------------------------------  
      B[idx(1,0)] = A[idx(1,0)]*A[idx(2,3)]*A[idx(3,2)] 
                  + A[idx(1,2)]*A[idx(2,0)]*A[idx(3,3)] 
                  + A[idx(1,3)]*A[idx(2,2)]*A[idx(3,0)]
                  - A[idx(1,0)]*A[idx(2,2)]*A[idx(3,3)] 
                  - A[idx(1,2)]*A[idx(2,3)]*A[idx(3,0)] 
                  - A[idx(1,3)]*A[idx(2,0)]*A[idx(3,2)];

      B[idx(1,1)] = A[idx(0,0)]*A[idx(2,2)]*A[idx(3,3)] 
                  + A[idx(0,2)]*A[idx(2,3)]*A[idx(3,0)] 
                  + A[idx(0,3)]*A[idx(2,0)]*A[idx(3,2)]
                  - A[idx(0,0)]*A[idx(2,3)]*A[idx(3,2)] 
                  - A[idx(0,2)]*A[idx(2,0)]*A[idx(3,3)] 
                  - A[idx(0,3)]*A[idx(2,2)]*A[idx(3,0)];
        
      B[idx(1,2)] = A[idx(0,0)]*A[idx(1,3)]*A[idx(3,2)] 
                  + A[idx(0,2)]*A[idx(1,0)]*A[idx(3,3)] 
                  + A[idx(0,3)]*A[idx(1,2)]*A[idx(3,0)]
                  - A[idx(0,0)]*A[idx(1,2)]*A[idx(3,3)] 
                  - A[idx(0,2)]*A[idx(1,3)]*A[idx(3,0)] 
                  - A[idx(0,3)]*A[idx(1,0)]*A[idx(3,2)];

      B[idx(1,3)] = A[idx(0,0)]*A[idx(1,2)]*A[idx(2,3)] 
                  + A[idx(0,2)]*A[idx(1,3)]*A[idx(2,0)] 
                  + A[idx(0,3)]*A[idx(1,0)]*A[idx(2,2)]
                  - A[idx(0,0)]*A[idx(1,3)]*A[idx(2,2)] 
                  - A[idx(0,2)]*A[idx(1,0)]*A[idx(2,3)] 
                  - A[idx(0,3)]*A[idx(1,2)]*A[idx(2,0)];
// --------------------------------------------------------------------------
      B[idx(2,0)] = A[idx(1,0)]*A[idx(2,1)]*A[idx(3,3)] 
                  + A[idx(1,1)]*A[idx(2,3)]*A[idx(3,0)] 
                  + A[idx(1,3)]*A[idx(2,0)]*A[idx(3,1)]
                  - A[idx(1,0)]*A[idx(2,3)]*A[idx(3,1)] 
                  - A[idx(1,1)]*A[idx(2,0)]*A[idx(3,3)] 
                  - A[idx(1,3)]*A[idx(2,1)]*A[idx(3,0)];

      B[idx(2,1)] = A[idx(0,0)]*A[idx(2,3)]*A[idx(3,1)] 
                  + A[idx(0,1)]*A[idx(2,0)]*A[idx(3,3)] 
                  + A[idx(0,3)]*A[idx(2,1)]*A[idx(3,0)]
                  - A[idx(0,0)]*A[idx(2,1)]*A[idx(3,3)] 
                  - A[idx(0,1)]*A[idx(2,3)]*A[idx(3,0)] 
                  - A[idx(0,3)]*A[idx(2,0)]*A[idx(3,1)];
        
      B[idx(2,2)] = A[idx(0,0)]*A[idx(1,1)]*A[idx(3,3)] 
                  + A[idx(0,1)]*A[idx(1,3)]*A[idx(3,0)] 
                  + A[idx(0,3)]*A[idx(1,0)]*A[idx(3,1)]
                  - A[idx(0,0)]*A[idx(1,3)]*A[idx(3,1)] 
                  - A[idx(0,1)]*A[idx(1,0)]*A[idx(3,3)] 
                  - A[idx(0,3)]*A[idx(1,1)]*A[idx(3,0)];

      B[idx(2,3)] = A[idx(0,0)]*A[idx(1,3)]*A[idx(2,1)] 
                  + A[idx(0,1)]*A[idx(1,0)]*A[idx(2,3)] 
                  + A[idx(0,3)]*A[idx(1,1)]*A[idx(2,0)]
                  - A[idx(0,0)]*A[idx(1,1)]*A[idx(2,3)] 
                  - A[idx(0,1)]*A[idx(1,3)]*A[idx(2,0)] 
                  - A[idx(0,3)]*A[idx(1,0)]*A[idx(2,1)];
// --------------------------------------------------------------------------
      B[idx(3,0)] = A[idx(1,0)]*A[idx(2,2)]*A[idx(3,1)] 
                  + A[idx(1,1)]*A[idx(2,0)]*A[idx(3,2)] 
                  + A[idx(1,2)]*A[idx(2,1)]*A[idx(3,0)]
                  - A[idx(1,0)]*A[idx(2,1)]*A[idx(3,2)] 
                  - A[idx(1,1)]*A[idx(2,2)]*A[idx(3,0)] 
                  - A[idx(1,2)]*A[idx(2,0)]*A[idx(3,1)];

      B[idx(3,1)] = A[idx(0,0)]*A[idx(2,1)]*A[idx(3,2)] 
                  + A[idx(0,1)]*A[idx(2,2)]*A[idx(3,0)] 
                  + A[idx(0,2)]*A[idx(2,0)]*A[idx(3,1)]
                  - A[idx(0,0)]*A[idx(2,2)]*A[idx(3,1)] 
                  - A[idx(0,1)]*A[idx(2,0)]*A[idx(3,2)] 
                  - A[idx(0,2)]*A[idx(2,1)]*A[idx(3,0)];
        
      B[idx(3,2)] = A[idx(0,0)]*A[idx(1,2)]*A[idx(3,1)] 
                  + A[idx(0,1)]*A[idx(1,0)]*A[idx(3,2)] 
                  + A[idx(0,2)]*A[idx(1,1)]*A[idx(3,0)]
                  - A[idx(0,0)]*A[idx(1,1)]*A[idx(3,2)] 
                  - A[idx(0,1)]*A[idx(1,2)]*A[idx(3,0)] 
                  - A[idx(0,2)]*A[idx(1,0)]*A[idx(3,1)];

      B[idx(3,3)] = A[idx(0,0)]*A[idx(1,1)]*A[idx(2,2)] 
                  + A[idx(0,1)]*A[idx(1,2)]*A[idx(2,0)] 
                  + A[idx(0,2)]*A[idx(1,0)]*A[idx(2,1)]
                  - A[idx(0,0)]*A[idx(1,2)]*A[idx(2,1)] 
                  - A[idx(0,1)]*A[idx(1,0)]*A[idx(2,2)] 
                  - A[idx(0,2)]*A[idx(1,1)]*A[idx(2,0)];

      for(int i = 0; i < 16; i++) 
      {
         B[i] *= r;
      }
   }
   else if(N == 3)
   {
      B[idx(0,0)] = r * (A[idx(1,1)]*A[idx(2,2)] - A[idx(1,2)]*A[idx(2,1)]);
      B[idx(0,1)] = r * (A[idx(0,2)]*A[idx(2,1)] - A[idx(0,1)]*A[idx(2,2)]);
      B[idx(0,2)] = r * (A[idx(0,1)]*A[idx(1,2)] - A[idx(0,2)]*A[idx(1,1)]);
      B[idx(1,0)] = r * (A[idx(1,2)]*A[idx(2,0)] - A[idx(1,0)]*A[idx(2,2)]);
      B[idx(1,1)] = r * (A[idx(0,0)]*A[idx(2,2)] - A[idx(0,2)]*A[idx(2,0)]);
      B[idx(1,2)] = r * (A[idx(0,2)]*A[idx(1,0)] - A[idx(0,0)]*A[idx(1,2)]);
      B[idx(2,0)] = r * (A[idx(1,0)]*A[idx(2,1)] - A[idx(1,1)]*A[idx(2,0)]);
      B[idx(2,1)] = r * (A[idx(0,1)]*A[idx(2,0)] - A[idx(0,0)]*A[idx(2,1)]);
      B[idx(2,2)] = r * (A[idx(0,0)]*A[idx(1,1)] - A[idx(0,1)]*A[idx(1,0)]);
   }
   else if(N == 2)
   {
      B[idx(0,0)] = r * A[idx(1,1)];
      B[idx(0,1)] = r * A[idx(0,1)] * (-1);
      B[idx(1,0)] = r * A[idx(1,0)] * (-1);
      B[idx(1,1)] = r * A[idx(0,0)];
   }
   else if(N == 1) 
   {
      B[idx(0,0)] = r;
   }

   // Copy the inverse
   std::memcpy(A, B, N*N*sizeof(TYPE));
}

}
////! \todo Optimize this function by implementing all possible branches.
////! Possible branches
////! a in {!=0, 0, 1}
////! b in {!=0, 0, 1, -1}
////! y in {!=0, == 0}
////! <BR>
////! (a != 0 && b !=  0 && y != nullptr) y = alpha * A * x + beta * y <BR>
////! (a != 0 && b ==  0 && y != nullptr) y = alpha * A * x <BR>
////! (a != 0 && b ==  1 && y != nullptr) y = alpha * A * x + y <BR>
////! (a != 0 && b == -1 && y != nullptr) y = alpha * A * x - y
////! <BR>
////! (a != 0 && b !=  0 && y == nullptr) x = alpha * A * x
////! (a != 0 && b ==  0 && y == nullptr) x = alpha * A * x
////! (a != 0 && b ==  1 && y == nullptr) x = alpha * A * x
////! (a != 0 && b == -1 && y == nullptr) x = alpha * A * x
////! <BR>
////! (a == 0 && b !=  0 && y != nullptr) y = beta * y
////! (a == 0 && b ==  0 && y != nullptr) y = 0
////! (a == 0 && b ==  1 && y != nullptr) y = y
////! (a == 0 && b == -1 && y != nullptr) y = -y
////! <BR>
////! (a == 0 && b !=  0 && y == nullptr) x = 0, y = 0
////! (a == 0 && b ==  0 && y == nullptr) x = 0, y = 0
////! (a == 0 && b ==  1 && y == nullptr) x = 0, y = 0
////! (a == 0 && b == -1 && y == nullptr) x = 0, y = 0
////! <BR>
////! (a == 1 && b !=  0 && y != nullptr) y = A * x + beta * y
////! (a == 1 && b ==  0 && y != nullptr) y = A * x
////! (a == 1 && b ==  1 && y != nullptr) y = A * x + y
////! (a == 1 && b == -1 && y != nullptr) y = A * x - y
////! <BR>
////! (a == 1 && b !=  0 && y == nullptr) x = A * x
////! (a == 1 && b ==  0 && y == nullptr) x = A * x
////! (a == 1 && b ==  1 && y == nullptr) x = A * x
////! (a == 1 && b == -1 && y == nullptr) x = A * x
//template<class TYPE, typename N, typename M>
//inline void gemv(const TYPE a, const TYPE* A, TYPE* x, 
//   const TYPE b = 0, TYPE* y = nullptr);
//{
//   for(uint32_t i = 0; i < N; i++)
//   {
//      for(uint32_t j = 0; i < M; j++)
//      {
//         y[i] = a * A(i,j) * x[j] + b * y[i];  
//      }
//   }
//}

#endif

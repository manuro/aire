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

//! \brief Defines matrix access pattern.
//#define A(i,j) A[((i)*(N))+(j)]
//#define B(i,j) B[((i)*(N))+(j)]

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

//! \brief Computes the determinat of a matrix.
//! \param A Matrix of size (NxN).
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
      d = A[idx(0,0)]*A[idx(1,1)] 
        - A[idx(0,1)]*A[idx(1,0)];
   }
   else if(N == 1)
   {
      // A = | a | -> det(A) = 1 / a
      d = 1 / A[idx(0,0)];
   }
   return d;
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

//template<class TYPE>
//inline TYPE* solve4(const TYPE& A, TYPE* x, const TYPE& b, TYPE d)
//{
//   TYPE B[16];
//   
//   B(0,0) = A(1,1)*A(2,2)*A(3,3) + A(1,2)*A(2,3)*A(3,1) + A(1,3)*A(2,1)*A(3,2)
//          - A(1,1)*A(2,3)*A(3,2) - A(1,2)*A(2,1)*A(3,3) - A(1,3)*A(2,2)*A(3,1);

//   B(0,1) = A(0,1)*A(2,3)*A(3,2) + A(0,2)*A(2,1)*A(3,3) + A(0,3)*A(2,2)*A(3,1)
//          - A(0,1)*A(2,2)*A(3,3) - A(0,2)*A(2,3)*A(3,1) - A(0,3)*A(2,1)*A(3,2);
//           
//   B(0,2) = A(0,1)*A(1,2)*A(3,3) + A(0,2)*A(1,3)*A(3,1) + A(0,3)*A(1,1)*A(3,2)
//          - A(0,1)*A(1,3)*A(3,2) - A(0,2)*A(1,1)*A(3,3) - A(0,3)*A(1,2)*A(3,1);

//   B(0,3) = A(0,1)*A(1,3)*A(2,2) + A(0,2)*A(1,1)*A(2,3) + A(0,3)*A(1,2)*A(2,1)
//          - A(0,1)*A(1,2)*A(2,3) - A(0,2)*A(1,3)*A(2,1) - A(0,3)*A(1,1)*A(2,2);

//   // --------------------------------------------------------------------------
//   
//   B(1,0) = A(1,0)*A(2,3)*A(3,2) + A(1,2)*A(2,0)*A(3,3) + A(1,3)*A(2,2)*A(3,0)
//          - A(1,0)*A(2,2)*A(3,3) - A(1,2)*A(2,3)*A(3,0) - A(1,3)*A(2,0)*A(3,2);

//   B(1,1) = A(0,0)*A(2,2)*A(3,3) + A(0,2)*A(2,3)*A(3,0) + A(0,3)*A(2,0)*A(3,2)
//          - A(0,0)*A(2,3)*A(3,2) - A(0,2)*A(2,0)*A(3,3) - A(0,3)*A(2,2)*A(3,0);
//           
//   B(1,2) = A(0,0)*A(1,3)*A(3,2) + A(0,2)*A(1,0)*A(3,3) + A(0,3)*A(1,2)*A(3,0)
//          - A(0,0)*A(1,2)*A(3,3) - A(0,2)*A(1,3)*A(3,0) - A(0,3)*A(1,0)*A(3,2);

//   B(1,3) = A(0,0)*A(1,2)*A(2,3) + A(0,2)*A(1,3)*A(2,0) + A(0,3)*A(1,0)*A(2,2)
//          - A(0,0)*A(1,3)*A(2,2) - A(0,2)*A(1,0)*A(2,3) - A(0,3)*A(1,2)*A(2,0);

//   // --------------------------------------------------------------------------
//   
//   B(2,0) = A(1,0)*A(2,1)*A(3,3) + A(1,1)*A(2,3)*A(3,0) + A(1,3)*A(2,0)*A(3,1)
//          - A(1,0)*A(2,3)*A(3,1) - A(1,1)*A(2,0)*A(3,3) - A(1,3)*A(2,1)*A(3,0);

//   B(2,1) = A(0,0)*A(2,3)*A(3,1) + A(0,1)*A(2,0)*A(3,3) + A(0,3)*A(2,1)*A(3,0)
//          - A(0,0)*A(2,1)*A(3,3) - A(0,1)*A(2,3)*A(3,0) - A(0,3)*A(2,0)*A(3,1);
//           
//   B(2,2) = A(0,0)*A(1,1)*A(3,3) + A(0,1)*A(1,3)*A(3,0) + A(0,3)*A(1,0)*A(3,1)
//          - A(0,0)*A(1,3)*A(3,1) - A(0,1)*A(1,0)*A(3,3) - A(0,3)*A(1,1)*A(3,0);

//   B(2,3) = A(0,0)*A(1,3)*A(2,1) + A(0,1)*A(1,0)*A(2,3) + A(0,3)*A(1,1)*A(2,0)
//          - A(0,0)*A(1,1)*A(2,3) - A(0,1)*A(1,3)*A(2,0) - A(0,3)*A(1,0)*A(2,1);
//           
//   // --------------------------------------------------------------------------
//   
//   B(3,0) = A(1,0)*A(2,2)*A(3,1) + A(1,1)*A(2,0)*A(3,2) + A(1,2)*A(2,1)*A(3,0)
//          - A(1,0)*A(2,1)*A(3,2) - A(1,1)*A(2,2)*A(3,0) - A(1,2)*A(2,0)*A(3,1);

//   B(3,1) = A(0,0)*A(2,1)*A(3,2) + A(0,1)*A(2,2)*A(3,0) + A(0,2)*A(2,0)*A(3,1)
//          - A(0,0)*A(2,2)*A(3,1) - A(0,1)*A(2,0)*A(3,2) - A(0,2)*A(2,1)*A(3,0);
//           
//   B(3,2) = A(0,0)*A(1,2)*A(3,1) + A(0,1)*A(1,0)*A(3,2) + A(0,2)*A(1,1)*A(3,0)
//          - A(0,0)*A(1,1)*A(3,2) - A(0,1)*A(1,2)*A(3,0) - A(0,2)*A(1,0)*A(3,1);

//   B(3,3) = A(0,0)*A(1,1)*A(2,2) + A(0,1)*A(1,2)*A(2,0) + A(0,2)*A(1,0)*A(2,1)
//          - A(0,0)*A(1,2)*A(2,1) - A(0,1)*A(1,0)*A(2,2) - A(0,2)*A(1,1)*A(2,0);
//           

//   // Solve by multiply with inverse   
//   TYPE a = 1 / d;
//   gemv(a, B, b, 0, x);
////   x[0] = (B(0,0)*b[0] + B(0,1)*b[1] + B(0,2)*b[2] + B(0,3)*b[3]) / d;
////   x[1] = (B(1,0)*b[0] + B(1,1)*b[1] + B(1,2)*b[2] + B(1,3)*b[3]) / d;
////   x[2] = (B(2,0)*b[0] + B(2,1)*b[1] + B(2,2)*b[2] + B(2,3)*b[3]) / d;
////   x[3] = (B(3,0)*b[0] + B(3,1)*b[1] + B(3,2)*b[2] + B(3,3)*b[3]) / d;
//}
#endif

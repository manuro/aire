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
//! \file Tools.h
//! \brief Some very tricky helper functions.
#ifndef TOOLS_H
#define TOOLS_H

#include <cassert>
#include <cstdint>

//! \brief Global aire namespace.
namespace aire 
{

//! \brief Is not a number according to IEEE standard.
//! \param a The number.
//! \return True, if it is not a number.
template<typename TYPE>
inline bool isnan(TYPE a)
{
   return ((a) != (a));
}


//! \brief Computes the 1D index of a 2D index.
//! \param x Index in x dimension.
//! \param y Index in y dimension. 
template<uint32_t dx>
inline uint32_t idx1d(uint32_t x, uint32_t y)
{
   return x * dx + y;
}

//! \brief Computes the 1D index of a 3D index.
//! \param x Index in x dimension.
//! \param y Index in y dimension. 
//! \param z Index in z dimension.
template<uint32_t dx, uint32_t dy>
inline uint32_t idx1d(uint32_t x, uint32_t y, uint32_t z)
{
   return x * dx * dy + y * dx + z;
}

//! \brief Swaps a and b without temporary space.
//! \param a Refernece to a
//! \param b Reference to b
inline void swap(int32_t& __restrict a, int32_t& __restrict b)
{
   assert(&a != &b);
   a ^= b;
   b ^= a;
   a ^= b;
}

}
#endif

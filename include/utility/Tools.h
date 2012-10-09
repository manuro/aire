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

#endif

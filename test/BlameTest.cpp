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
//! \file BlameTest.cpp
//! \brief Test driver for the BLAME. 
#include <cstdlib>
#include <cmath>
#include "Test.h"
#include "BlameVector.h"
#include "BlameMatrix.h"

#include <cstdint>

template<typename TYPE, uint32_t N>
void addTests(aire::Test& test)
{
   // --- SCAL
   test.add(std::to_string(N) + typeid(TYPE).name() + "-SCAL positive ", 
      scalPositive<TYPE, N>);
   test.add(std::to_string(N) + typeid(TYPE).name() + "-SCAL negative ",
      scalNegative<TYPE, N>);
   test.add(std::to_string(N) + typeid(TYPE).name() + "-SCAL neutral ", 
      scalNeutral<TYPE, N>);
   test.add(std::to_string(N) + typeid(TYPE).name() + "-SCAL inverse ", 
      scalInverse<TYPE, N>);

   // --- AXPY
   test.add(std::to_string(N) + typeid(TYPE).name() + "-AXPY positive ",
      axpyPositive<TYPE, N>);
   test.add(std::to_string(N) + typeid(TYPE).name() + "-AXPY negative ",
      axpyNegative<TYPE, N>);
   test.add(std::to_string(N) + typeid(TYPE).name() + "-AXPY neutral ", 
      axpyNeutral<TYPE, N>);
   test.add(std::to_string(N) + typeid(TYPE).name() + "-AXPY zero ", 
      axpyZero<TYPE, N>);
   
   // --- DET
   test.add(std::to_string(N) + typeid(TYPE).name() + "-DET positive ", 
      detPositive<TYPE, N>);

   // -- INV
   test.add(std::to_string(N) + typeid(TYPE).name() + "-INV positive ", 
      invPositive<TYPE, N>);
}


int main()
{
   aire::Test test("Blame-Test");
   
   addTests<double, 4>(test);
   addTests<double, 3>(test);
   addTests<double, 2>(test);
   addTests<double, 1>(test);

   addTests<float, 4>(test);
   addTests<float, 3>(test);
   addTests<float, 2>(test);
   addTests<float, 1>(test);
   
   test.run();
  
   return EXIT_SUCCESS;
}

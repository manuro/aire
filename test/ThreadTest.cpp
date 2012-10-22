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
//! \file ThreadTest.cpp
//! \brief Test case for the Thread, Mutex and Event class. 
#include <cstdlib>
#include <cmath>
#include "Test.h"
#include "ThreadSync.h"

int main()
{
   aire::Test test("Thread-Test");

   test.add("Signal and wait (2 threads)", signalAndWait);

   test.add("Synchronized print (2 threads)", threadOutput<2>);
   test.add("Synchronized print (8 threads)", threadOutput<8>);
   test.add("Synchronized print (32 threads)", threadOutput<32>);

   test.run();
  
   return EXIT_SUCCESS;
}

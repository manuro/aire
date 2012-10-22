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
//! \file SystemTest.cpp
//! \brief Test driver of basic system information class. 

#include <cstdlib>

#include "System.h"
#include "Test.h"

// --- Main --------------------------------------------------------------------
int main()
{
   // At this time we have only a cute system output test.
   auto func = [] () -> int {
      int result = EXIT_SUCCESS;

      std::cout << "Cores: " << aire::System::GetNumCores() << std::endl;

      return result;
   };

   aire::Test test("System-Test");
   
   test.add("Get system information", func);

   test.run();
  
   return EXIT_SUCCESS;
}

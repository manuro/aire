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
//! \file WatchTest.cpp
//! \brief Test driver of watch and timer class. 

/**< \brief Is not a number according to IEEE standard. */
#include <cmath>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "Test.h"
#include "Timer.h"
#include "Watch.h"

// --- Main --------------------------------------------------------------------
int main()
{
   aire::Test test("Watch-Test");

   test.add("Check timer and overhead", [] () -> int {
      int result = EXIT_SUCCESS;
      aire::Timer t;
      unsigned int nloops = 100;

      t.start();
      for(unsigned int i = 0; i < nloops; i++)
      {
         std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      t.stop();
      
      std::cout << "Wall time: " << t.getTime(false) << std::endl;
      std::cout << "Average time: " << t.getTime(true) << std::endl;
      std::cout << "Overhead: " << t.getTimeOverhead() << std::endl;
      
      if(t.getTimeOverhead() > 1e-6 || std::isnan(t.getTimeOverhead()))
      {
         std::cerr << "Timestamp overhead is bad!" << std::endl;
         result = EXIT_FAILURE;
      } 
      if(std::isnan(t.getTime(false)))
      {
         std::cerr << "Wall time measurement is wrong!" << std::endl;
         result = EXIT_FAILURE;
      }
      return result;
   }
   );

   test.add("Simple timer", [] () -> int {
      int result = EXIT_SUCCESS;
      aire::StopWatch::GetInstance()->getTimer("One timer")->start();
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      aire::StopWatch::GetInstance()->getTimer("One timer")->stop();
      return result;
   }
   );
   
   test.add("Nested timer", [] () -> int {
      int result = EXIT_SUCCESS;
      aire::StopWatch::GetInstance()->getTimer("Outer timer")->start();
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      aire::StopWatch::GetInstance()->getTimer("Inner timer")->start();
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      aire::StopWatch::GetInstance()->getTimer("Inner timer")->stop();
      aire::StopWatch::GetInstance()->getTimer("Outer timer")->stop();
      return result;
   }
   );

   test.run();

   aire::StopWatch::GetInstance()->printTime(std::cout, false);
  
   return EXIT_SUCCESS;
}

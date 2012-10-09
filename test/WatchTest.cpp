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
#define ISNAN(a) ((a) != (a)) 

#include <cstdlib>

#include "Test.h"
#include "Timer.h"
#include "Watch.h"

int main()
{
   Test test("Watch-Test");

   test.add("Check timer and overhead", [] () {
      int result = EXIT_SUCCESS;
      aire::Timer t;
      unsigned int nloops = 100;

      t.start();
      for(unsigned int i = 0; i < nloops; i++)
      {
         #if defined(__linux__) || defined(__APPLE__)
         usleep(1000);
         #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
         Sleep(1);
         #endif
      }
      t.stop();
      
      std::cout << "Wall time: " << t.getTime(false) << std::endl;
      std::cout << "Average time: " << t.getTime(true) << std::endl;
      std::cout << "Overhead: " << t.getTimeOverhead() << std::endl;
      
      if(t.getTimeOverhead() > 1e-6 || ISNAN(t.getTimeOverhead()))
      {
         std::cerr << "Timestamp overhead is bad!" << std::endl;
         result = EXIT_FAILURE;
      } 
      if(ISNAN(t.getTime(false)))
      {
         std::cerr << "Wall time measurement is wrong!" << std::endl;
         result = EXIT_FAILURE;
      }
      if(ISNAN(t.getTime(true)))
      {
         std::cerr << "Average time measurement is wrong!" << std::endl;
         result = EXIT_FAILURE;
      }
      return result;
   }
   );

   test.add("Simple timer", [] () {
      int result = EXIT_SUCCESS;
      aire::StopWatch::GetInstance()->getTimer("One timer")->start();
      #if defined(__linux__) || defined(__APPLE__)
      usleep(1000);
      #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
      Sleep(1);
      #endif
      aire::StopWatch::GetInstance()->getTimer("One timer")->stop();
      return result;
   }
   );
   
   test.add("Nested timer", [] () {
      int result = EXIT_SUCCESS;
      aire::StopWatch::GetInstance()->getTimer("Outer timer")->start();
      #if defined(__linux__) || defined(__APPLE__)
      usleep(1000);
      #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
      Sleep(1);
      #endif
      aire::StopWatch::GetInstance()->getTimer("Inner timer")->start();
      #if defined(__linux__) || defined(__APPLE__)
      usleep(1000);
      #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
      Sleep(1);
      #endif
      aire::StopWatch::GetInstance()->getTimer("Inner timer")->stop();
      aire::StopWatch::GetInstance()->getTimer("Outer timer")->stop();
      return result;
   }
   );

   test.run(true);
  
   return EXIT_SUCCESS;
}

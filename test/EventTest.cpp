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
//! \file EventTest.cpp
//! \brief Test case for some multi-threadding stuff. 
#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <thread>
#include <chrono>

#include "Test.h"
#include "Event.h"
#include "Stream.h"

// --- Thread output -----------------------------------------------------------
void outputFunc()
{
   std::thread::id tid = std::this_thread::get_id();
   std::cout << (aire::Stream() << "Thread " << tid << "\n").toString();
}

template<uint32_t N>
int32_t threadOutput()
{
   std::thread threads[N];
   
   for(uint32_t i = 0; i < N; i++)
   {
      threads[i] = std::thread(&outputFunc);
   }

   for(uint32_t i = 0; i < N; i++)
   {
      threads[i].join();
   }

   return EXIT_SUCCESS;
}

// --- Signal and wait ---------------------------------------------------------
static aire::Event eventOne;
static aire::Event eventTwo;

void functionOne()
{
   eventOne.wait();
   // Do something senseful
   eventTwo.signal();
}

void functionTwo()
{
   // Do something senseful
   std::this_thread::sleep_for(std::chrono::seconds(1));
   eventOne.signal();
   eventTwo.wait(); 
}

int32_t signalAndWait()
{
   std::thread threadOne(functionOne);
   std::thread threadTwo(functionTwo);

   threadOne.join();
   threadTwo.join();

   return EXIT_SUCCESS;
}

// --- Main --------------------------------------------------------------------
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

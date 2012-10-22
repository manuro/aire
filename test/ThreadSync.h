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
//! \file ThreadSync.h
//! \brief Test cases for thread syncronization. 
#ifndef THREADSYNC_H
#define THREADSYNC_H

#include <cstdint>
#include <thread>

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
   eventOne.resetSignal();
   // Do something senseful
   eventTwo.signal();
}

void functionTwo()
{
   // Do something senseful
   eventOne.signal();
   eventTwo.wait();
   eventTwo.resetSignal();   
}

int32_t signalAndWait()
{
   std::thread threadOne(functionOne);
   std::thread threadTwo(functionTwo);

   threadOne.join();
   threadTwo.join();

   return EXIT_SUCCESS;
}

#endif

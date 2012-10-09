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

#include "Thread.h"
#include "Event.h"
#include "Mutex.h"
#include "Stream.h"

// --- Thread output -----------------------------------------------------------
void* outputFunc(void* data)
{
   unsigned long tid = aire::Thread::GetId();
   std::cout << (aire::Stream() << "Thread " << tid << "\n").toString();
   return nullptr;
}

template<uint32_t N>
int32_t threadOutput()
{
   aire::Thread thread[N];

   for(uint32_t i = 0; i < N; i++)
   {
      thread[i].initialize(&outputFunc, nullptr);
   }

   for(uint32_t i = 0; i < N; i++)
   {
      thread[i].join();
   }

   return EXIT_SUCCESS;
}

// --- Mutex -------------------------------------------------------------------
aire::Mutex mutex(false);

void* mutexFunc(void* data)
{
   mutex.lock();
   // Do something senseful
   mutex.unlock();
   return nullptr;
}

template<uint32_t N>
int32_t lockWithMutex()
{
   aire::Thread thread[N];

   for(uint32_t i = 0; i < N; i++)
   {
      thread[i].initialize(&mutexFunc, nullptr);
   }

   for(uint32_t i = 0; i < N; i++)
   {
      thread[i].join();
   }

   return EXIT_SUCCESS;
}

// --- Signal and wait ---------------------------------------------------------
static aire::Event barrierOne;
static aire::Event barrierTwo;

void* eventOne(void* data)
{
   barrierOne.wait();
   barrierOne.resetSignal();
   // Do something senseful
   barrierTwo.signal();
   return nullptr;
}

void* eventTwo(void* data)
{
   // Do something senseful
   barrierOne.signal();
   barrierTwo.wait();
   barrierTwo.resetSignal();   
   return nullptr;
}

int32_t signalAndWait()
{
   aire::Thread threadOne(&eventOne, nullptr);
   aire::Thread threadTwo(&eventTwo, nullptr);

   threadOne.join();
   threadTwo.join();

   return EXIT_SUCCESS;
}

#endif

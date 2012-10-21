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
//! \file Thread.h
//! \brief Thread implementation on system level. 
#ifndef THREAD_H
#define THREAD_H

#if defined(__linux__) || defined(__APPLE__)
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <sys/syscall.h>
#include <unistd.h>
#elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
#include <windows.h>
#endif

//! \brief Global aire namespace.
namespace aire
{

//! \brief Thread implementation on system level.
class Thread
{
public:
   //! \brief Constructor of the object.
   Thread()
   {
      // Empty contructor
   }

   //! \brief Constructor of the object.
   //! \param entry Callback function for the thread.
   //! \param data A pointer to the data struct passed to the callback.
   Thread(void* (*entry)(void* data), void* data)
   {
      initialize(entry, data); 
   }

   //! \brief Destructor of the object.
   virtual ~Thread() { }

   //! \brief Initializes the default parameter of the object.
   //! \param entry Callback function for the thread.
   //! \param data A pointer to the data struct passed to the callback.
   virtual void initialize(void* (*entry)(void* data), void* data)
   {
      #if defined(__linux__) || defined(__APPLE__)
      pthread_create(&_thread, NULL, entry, data); 
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      _thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)entry, data, 0, 0);
      #endif
   }

   //! \brief Invokes the fork process and wait for join.
   void join()
   {
      #if defined(__linux__) || defined(__APPLE__)
      pthread_join(_thread, NULL);
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      WaitForSingleObject(_thread, INFINITE); 
      #endif   
   }
   
   //! \brief This function detach the current thread and calls exit.
   //! Use this function with caution because memory leaks can happen if 
   //! the memory used by the thread is not free.
   //! \param code Return code within exit function.
   static void ExitCurrent(int code)
   {
      #if defined(__linux__) || defined(__APPLE__)
      pthread_detach(pthread_self());
      pthread_exit(nullptr);
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      TerminateThread(GetCurrentThread(), code);
      #endif   
   }
   
   //! \brief Access to the unique thread id.
   //! \return The unique id for the current thread.
   static unsigned long GetId()
   {
      #if defined(__linux__) || defined(__APPLE__)
      //return (unsigned long)syscall( __NR_gettid );
      return (unsigned long)pthread_self();
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      return (unsigned long)GetCurrentThreadId();
      #endif   
   }
   
private:  
   #if defined(__linux__) || defined(__APPLE__)
   //! \brief Thread member. 
	pthread_t _thread;
   #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
   //! \brief Thread member. 
   HANDLE _thread;
   #endif  

   //! \brief Private copy constructor. 
   Thread(Thread const&);
   
   //! \brief Private assignment operator. 
   Thread& operator=(Thread const&);
};

}
#endif

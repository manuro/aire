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
//! \file Event.h
//! \brief Implementation of an event. 
#ifndef EVENT_H
#define EVENT_H

#if defined(__linux__) || defined(__APPLE__)
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
#include <windows.h>
#endif

#include <cstdint>

//! \brief Global aire namespace.
namespace aire 
{

//! \brief Defines the event class.
class Event
{
public:
   //! \brief Constructor of the object.
   Event()
   {
      initialize();
   }
   
   //! \brief Destructor of the object.
   virtual ~Event()
   {
      destroy();   
   }
   
   //! \brief Initializes the default parameter of the object.
   virtual void initialize()
   {
      #if defined(__linux__) || defined(__APPLE__)
      pthread_mutex_init(&_mutex, 0); 
      pthread_cond_init(&_condition, 0);
      _signaled = false;
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      handle = CreateEvent(NULL, true, false, NULL); 
      #endif 
   }
   
   //! \brief Free all used memory by this object and destroy it.
   virtual void destroy()
   {
      #if defined(__linux__) || defined(__APPLE__)
      // Empty
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      SetEvent(_handle); 
      CloseHandle(_handle); 
      #endif 
   }
   
   //! \brief Wait for signal with a timeout.
   //! \param timeout The timeout in milliseconds.
   void wait(uint64_t timeout)
   {
      #if defined(__linux__) || defined(__APPLE__)
      pthread_mutex_lock(&_mutex);
      struct timeval rtime;
      struct timespec ts;
      struct timezone ztime;
      gettimeofday(&rtime, &ztime);
      rtime.tv_sec += timeout;
      ts.tv_sec = rtime.tv_sec;
	
      int rc = 0;
      while (!_signaled && rc == 0) 
      {
         rc = pthread_cond_timedwait(&_condition, &_mutex, &ts);
      }
      pthread_mutex_unlock(&_mutex);
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      WaitForSingleObject(_handle, timeout);
      #endif    
   }
   
   //! \brief Wait for signal without a timeout.
   void wait()
   {
      #if defined(__linux__) || defined(__APPLE__)
      pthread_mutex_lock(&_mutex);
      while (!_signaled)
      {
         pthread_cond_wait(&_condition, &_mutex);
      }
      pthread_mutex_unlock(&_mutex);
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      WaitForSingleObject(_handle, -1); 
      #endif    
   }
   
   //! \brief Signal the event.
   void signal()
   {
      #if defined(__linux__) || defined(__APPLE__)
      pthread_mutex_lock(&_mutex);
      _signaled = true;
      pthread_cond_broadcast(&_condition);
      pthread_mutex_unlock(&_mutex); 
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      SetEvent(_handle); 
      #endif    
   }
   
   //! \brief Reset the signal into default state.
   void resetSignal()
   {
      #if defined(__linux__) || defined(__APPLE__)
      pthread_mutex_lock(&_mutex);
      _signaled = false;
      pthread_mutex_unlock(&_mutex);
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      ResetEvent(_handle); 
      #endif    
   }
   
private:
   #if defined(__linux__) || defined(__APPLE__)
   //! \brief Mutex member.
   pthread_mutex_t _mutex;
   
   //! \brief Signal condition.
   pthread_cond_t _condition;
   
   //! \brief Signal state variable.
   bool _signaled;
   #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
   //! \brief Signal handle.
   HANDLE _handle;
   #endif

   //! \brief Private copy constructor. 
   Event(Event const&);
   
   //! \brief Private assignment operator.
   Event& operator=(Event const&);
};

}
#endif

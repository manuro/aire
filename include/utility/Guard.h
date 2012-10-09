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
//! \file Guard.h
//! \brief Implementation of a lock guard. 
#ifndef GUARD_H
#define GUARD_H

#if defined(__linux__) || defined(__APPLE__)
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
#include <windows.h>
#endif

//! \brief Global aire namespace.
namespace aire 
{

//! \brief Defines the guard class.
//!
//! The guard locks in the constructor and unlocks in the destructor.
class Guard
{
public:
   //! \brief Default constructor of the object.
   Guard()
   {
      initialize(false);  
      lock();
   }
   
   //! \brief Destructor of the object.
   virtual ~Guard()
   {
      unlock();
      destroy();   
   }
   
   //! \brief Initializes the default parameter of the object.
   //! \param useSpinLock True, if spin lock is enabled.
   virtual void initialize(bool useSpinLock)
   {
      #if defined(__linux__)
      _useSpinLock = useSpinLock;
      if(_useSpinLock)
      {
         pthread_spin_init(&_spinlock, 0);
      }
      else
      {
         pthread_mutex_init(&_mutex, 0); 
      }
      #elif defined(__APPLE__)
      useSpinLock = useSpinLock;
      pthread_mutex_init(&_mutex, 0); 
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      _useSpinLock = useSpinLock;
      InitializeCriticalSection(&_mutex);
      #endif    
   }
   
   //! \brief Free all used memory by this object and destroy it.
   virtual void destroy()
   {
      #if defined(__linux__)
      if(_useSpinLock)
      {
         pthread_spin_destroy(&_spinlock);
      }
      else
      {
         pthread_mutex_destroy(&_mutex); 
      }
      #elif defined(__APPLE__)
      pthread_mutex_destroy(&_mutex); 
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      DeleteCriticalSection(&_mutex);
      #endif    
   }
   
   //! \brief Locks the mutex.
   void lock()
   {
      #if defined(__linux__)
      if(_useSpinLock)
      {
         pthread_spin_lock(&_spinlock);
      }
      else
      {
         pthread_mutex_lock(&_mutex);
      }      
      #elif defined(__APPLE__)
      pthread_mutex_lock(&_mutex);
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      EnterCriticalSection(&_mutex);
      #endif    
   }
   
   //! \brief Unlocks the mutex.
   void unlock()
   {
      #if defined(__linux__)
      if(_useSpinLock)
      {
         pthread_spin_unlock(&_spinlock);
      }
      else
      {
         pthread_mutex_unlock(&_mutex);
      }       
      #elif defined(__APPLE__)
      pthread_mutex_unlock(&_mutex);
      #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      LeaveCriticalSection(&_mutex); 
      #endif    
   }
   
private:  
   //! \brief Spin lock indicator member.
   bool _useSpinLock;
   #if defined(__linux__)
   //! \brief Spin lock member. 
   pthread_spinlock_t _spinlock;
   #endif   
   #if defined(__linux__) || defined(__APPLE__)
   //! \brief Mutex member.
   pthread_mutex_t _mutex;
   #elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
   //! \brief Mutex member.
   CRITICAL_SECTION _mutex;
   #endif

   //! \brief Private copy constructor. 
   Guard(Guard const&);
   
   //! \brief Private assignment operator.
   Guard& operator=(Guard const&);
};

}
#endif

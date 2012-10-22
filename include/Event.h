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
//! \brief Event class for thread signals. 
#ifndef EVENT_H
#define EVENT_H

#include <condition_variable>
#include <mutex>
#include <cstdint>

//! \brief Global aire namespace.
namespace aire 
{

//! \brief Event class for thread signals.
class Event
{
public:
   //! \brief Constructor of the object.
   Event()
   {
      initialize();
   }
   
   //! \brief Destructor of the object.
   virtual ~Event() { }
   
   //! \brief Initializes the default parameter of the object.
   virtual void initialize()
   {
      _signaled = false;
   }
   
   //! \brief Wait for signal with a timeout.
   //! \param timeout The timeout in milliseconds.
   void wait(uint64_t timeout)
   {
      std::unique_lock<std::mutex> lock(_mutex);
      while(!_signaled)
      {
         _signal.wait_for(lock, std::chrono::milliseconds(timeout));
      }
      _signaled = false;   
   }
   
   //! \brief Wait for signal without a timeout.
   void wait()
   {
      std::unique_lock<std::mutex> lock(_mutex);
      while(!_signaled)
      {
         _signal.wait(lock);
      }
      _signaled = false; 
   }
   
   //! \brief Signal the event.
   void signal()
   {
      std::unique_lock<std::mutex> lock(_mutex);
      _signaled = true;
      _signal.notify_one();  
   }
   
private:
   //! \brief Mutex member.
   std::mutex _mutex;
   
   //! \brief Signal condition.
   std::condition_variable _signal;
 
   //! \brief Signal state variable.
   bool _signaled;

   //! \brief Private copy constructor. 
   Event(Event const&);
   
   //! \brief Private assignment operator.
   Event& operator=(Event const&);
};

}
#endif

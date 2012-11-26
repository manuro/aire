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
//! \file Timer.h
//! \brief Timer that measures the time using start and stop. 
#ifndef TIMER_H
#define TIMER_H

#include <chrono>

//! \brief Global aire namespace.
namespace aire
{

//! \brief Timer that measures the time using start and stop.
//!
//! A measurement can be started and stopped multiple times. The timespan 
//! is added to the total time.  
class Timer
{
public:
   //! \brief Constructor of the object.
   Timer()
   {
      initialize();
   }
   
   //! \brief Destructor of the object.
   virtual ~Timer() { }
   
   //! \brief Initializes the default parameter of the object.
   virtual void initialize()
   {
      _count = 0;
      _isRunning = false;
   }
   
   //! \brief Starts the timer.
   void start()
   {
      if(!_isRunning)
      {
         _isRunning = true;
         _count++;     
         _startTime = std::chrono::steady_clock::now();
      }
   }
   
   //! \brief Stops the timer.
   void stop()
   {  
      _timeSpan += std::chrono::steady_clock::now() - _startTime;
      _isRunning = false;
   }
   
   //! \brief Access to the total recorded time.
   //! \param isAverage Specifies to return average values.
   //! \return The total time recorded by this timer.
   double getTime(bool isAverage = false)
   {
      double result = -1;
      if(isAverage)
      {
         result = (_timeSpan.count() / static_cast<double>(_count));
      }
      else
      {
         result = _timeSpan.count();
      }

      return result;
   }

private:
   //! \brief System overhead of the time stamp.
   double _timeOverhead;
   
   //! \brief Counter for average time measurments.
   size_t _count;

   //! \brief Start time stamp.
   std::chrono::time_point<std::chrono::steady_clock> _startTime;
   
   //! \brief Total time of a time measurement.
   std::chrono::duration<double, std::nano> _timeSpan;
   
   //! \brief State variable of the timer.
   bool _isRunning;

   //! \brief Private copy constructor. 
   Timer(Timer const&);
   
   //! \brief Private assignment operator. 
   Timer& operator=(Timer const&); 
};

}  

#endif

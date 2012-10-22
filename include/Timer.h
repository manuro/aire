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

#include <cmath>

#if defined(__linux__) || defined(__APPLE__)
#include <time.h> 
#include <sys/time.h>
#elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
#include <windows.h>
#endif

#if defined(__linux__) || defined(__APPLE__)
inline timespec timediff(timespec startTime, timespec endTime)
{
   timespec result;
   // Handle the case when endTime.tv_nsec < startTime.tv_nsec
   if ((endTime.tv_nsec - startTime.tv_nsec) < 0) 
   {
      result.tv_sec = endTime.tv_sec - startTime.tv_sec - 1;
      result.tv_nsec = 1000000000 + endTime.tv_nsec - startTime.tv_nsec;
   } 
   else 
   {
      result.tv_sec = endTime.tv_sec - startTime.tv_sec;
      result.tv_nsec = endTime.tv_nsec - startTime.tv_nsec;
   }
   return result;
}
#endif

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
      _timeSpan = 0;
      _timeOverhead = NAN;
      _isRunning = false;
      #if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
      _startTime = 0;
      #endif
   }
   
   //! \brief Starts the timer.
   void start()
   {
      if(!_isRunning)
      {
         _isRunning = true;
         _count++;     
         #if defined(__linux__)
         clock_gettime(CLOCK_MONOTONIC_RAW, &_startTime);
         #elif defined(__APPLE__)
         struct timeval tv;
         struct timezone tz;
         gettimeofday(&tv, &tz);
         _startTime.tv_sec = tv.tv_sec;
         _startTime.tv_nsec = tv.tv_usec * 1000;
         #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
         LONGLONG current;
         LONGLONG tmp;
         QueryPerformanceFrequency((LARGE_INTEGER*)&tmp);
         double cpuFrequency = static_cast<double>(tmp);
         QueryPerformanceCounter((LARGE_INTEGER*)&current);
         _startTime = static_cast<double>(current / cpuFrequency); 
         #endif
      }
   }
   
   //! \brief Stops the timer.
   void stop()
   {
      #if defined(__linux__)
      clock_gettime(CLOCK_MONOTONIC_RAW, &_endTime);
      struct timespec span = timediff(_startTime, _endTime);
      _timeSpan += span.tv_sec + span.tv_nsec * 0.000000001;
      #elif defined(__APPLE__)
      struct timeval tv;
      struct timezone tz;
      gettimeofday(&tv, &tz);
      _endTime.tv_sec = tv.tv_sec;
      _endTime.tv_nsec = tv.tv_usec * 1000;
      struct timespec span = timediff(_startTime, _endTime);
      _timeSpan += span.tv_sec + span.tv_nsec * 0.000000001;
      #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
      LONGLONG current;
      LONGLONG tmp;
      QueryPerformanceFrequency((LARGE_INTEGER*)&tmp);
      double cpuFrequency = static_cast<double>(tmp);
      QueryPerformanceCounter((LARGE_INTEGER*)&current);
      _timeSpan += static_cast<double>(current / cpuFrequency) - _startTime;
      #endif   
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
         result = (_timeSpan / static_cast<double>(_count));
      }
      else
      {
         result = _timeSpan;
      }

      return result;
   }
  
   //! \brief Computes the time overhead that is generated by the system.
   //! \return The overhead for a time single time stap request.
   double getTimeOverhead()
   {
      if(std::isnan(_timeOverhead))
      {
         computeOverhead();
      }
        
      return static_cast<double>(2 * _timeOverhead * _count);  
   }

private:
   //! \brief System overhead of the time stamp.
   double _timeOverhead;
   
   //! \brief Counter for average time measurments.
   size_t _count;
   
   #if defined(__linux__) || defined(__APPLE__)
   //! \brief Begin of a time measurement.
   struct timespec _startTime;
   //! \brief End of a time measurement.
   struct timespec _endTime;
   #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
   //! \brief Begin of a time measurement.
   double _startTime;
   #endif
   
   //! \brief Total time of a time measurement.
   double _timeSpan;
   
   //! \brief State variable of the timer.
   bool _isRunning;

   //! \brief Private copy constructor. 
   Timer(Timer const&);
   
   //! \brief Private assignment operator. 
   Timer& operator=(Timer const&); 
   
   //! \brief Computes a system overhead for a time stamp.
   void computeOverhead()
   {
      Timer timer;
      unsigned int nloops = 100000;
      #if defined(__APPLE__)
      struct timeval tv;
      #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
      LONGLONG current;
      LONGLONG tmp;
      #endif
      
      timer.start();
      for(unsigned int i = 0; i < nloops; i++)
      {
         #if defined(__linux__)
         clock_gettime(CLOCK_MONOTONIC_RAW, &_endTime);
         #elif defined(__APPLE__)
         gettimeofday(&tv, NULL);
         #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
         QueryPerformanceFrequency((LARGE_INTEGER*)&tmp);
         QueryPerformanceCounter((LARGE_INTEGER*)&current);   
         #endif
      }
      timer.stop();
      _timeOverhead = timer.getTime(false)/ nloops;   
   }
};

}  

#endif
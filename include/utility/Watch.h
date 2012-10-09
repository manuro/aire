//
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
//! \file Watch.h
//! \brief Implementation of the watch.
#ifndef WATCH_H
#define WATCH_H

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <map>

#include "Singleton.h"
#include "Timer.h"

//! \brief Global aire namespace.
namespace aire
{

//! \brief Defines the watch class.
// 
// This class is not thread safe and it is not suposed 
// to be thread safe. In a multi-threadded environment 
// each thread might want to have it's own watch. 
class Watch
{
public:
   //! \brief Constructor of the object.
   Watch() { }
    
   //! \brief Destructor of the object.
   virtual ~Watch() { }
   
   //! \brief Access method for a timer.
   //! \param name The string literal containing the timer name.
   //! \return Returns the timer corresponding to the string.
   std::unique_ptr<Timer> const& getTimer(std::string name)
   {
      // Look if the timer exists   
      auto it = _timers.find(name);
      if (it == _timers.end())
      {
         // Create timer if there is no timer for the name
         auto newTimer =_timers.insert(
            std::pair<std::string, std::unique_ptr<Timer>>(name,
            std::move(std::unique_ptr<Timer>(new Timer()))));
         return newTimer.first->second;
      }
      else
      {
         return it->second;
      }   
   }
   
   //! \brief Prints the total time recorded by all timers.
   //! \param isAverage Specifies to print average values.
   //! \param stream The output stream to print to.
   void printTime(std::ostream& stream, bool isAverage)
   {
      // Maximum lendth of the timer name
      unsigned int maxlen = 40;
      
      // Calculate the total time
      double totalTime = 0;
      for(auto it = _timers.begin(); it != _timers.end(); it++) 
      {
         totalTime += it->second->getTime(isAverage);
      }
      stream << "-------------------------------------------------------------" 
             << "---" << std::endl;
      
      // Iterate over all timers and print the total time
      for(auto it = _timers.begin(); it != _timers.end(); it++) 
      {
         unsigned int respace = maxlen;
         std::string output = it->first;
         if(it->first.length() > maxlen)
         {
            // Resize the string
            output.resize(maxlen);
         } 
         else
         {
            respace = it->first.length()-1;
         }
         
         stream << output << std::setw(maxlen-respace) << " "
                << std::scientific << it->second->getTime(isAverage) << " "
                << std::resetiosflags(::std::ios::scientific)
                << "(" << (it->second->getTime(isAverage)/totalTime*100) << "%)"
                << std::endl;
      }
      
      // Print out the total time
      stream << "-------------------------------------------------------------" 
             << "---" << std::endl
             << std::scientific
             << "Total                                    " << totalTime
             << std::resetiosflags(::std::ios::scientific) << std::endl;
   }
   
private:
   //! \brief Hash-map of timers.  
   std::map<std::string, std::unique_ptr<Timer>> _timers;

   //! \brief Private copy constructor. 
   Watch(Watch const&);
   
   //! \brief Private assignment operator.
   Watch& operator=(Watch const&);
};

//! \brief Singleton type of the watch.
typedef Singleton<Watch> StopWatch;

}

#endif

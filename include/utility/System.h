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
//! \file System.h
//! \brief System helper class.
#ifndef SYSTEM_H
#define SYSTEM_H

#if defined(__linux__) 
#include <unistd.h>
#elif defined(__APPLE__)
#include <sys/param.h>
#include <sys/sysctl.h>
#elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
#include <windows.h>
#endif

#include <cstdint>

//! \brief Global aire namespace.
namespace aire {

//! \brief System helper class.
class System 
{
public:
   System () { }
   virtual ~System() { }
   
   static int32_t GetNumCores()
   {
      #if defined(WIN32) || defined(WIN64) || defined(WINDOWS)
      // Use sysinfo on Windows
      SYSTEM_INFO info;
      GetSystemInfo(&info);
      return info.dwNumberOfProcessors;
      #elif defined(__APPLE__)
      // Lookup Management Information Base on Mac
      int32_t mib[2];
      size_t length = 4;
      uint32_t nCores;

      mib[0] = CTL_HW; 
      mib[1] = HW_AVAILCPU;
      sysctl(mib, 2, &nCores, &length, NULL, 0);

      if(nCores < 1) 
      {
         // try usind HW_NCPU
         mib[1] = HW_NCPU;
         sysctl(mib, 2, &nCores, &length, NULL, 0);
         if(nCores < 1) 
         { 
            nCores = 1; 
         }
      }
      return nCores;
      #elif defined(__linux__) 
      // The easy way on Linux
      return sysconf(_SC_NPROCESSORS_ONLN);
      #else
      return 0;
      #endif   
   }
};

}
#endif

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
//! \file Test.h
//! \brief Implements test case functionality.
#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <functional>
#include <cstdint>
#include <map>

class Test
{
public:
   Test() { }
   Test(std::string name) 
   { 
      initialize(name);      
   }
   
   virtual void initialize(std::string name)
   {
      _name = name;
   }
   
   virtual void destroy()
   {
      _test.erase(_test.begin(), _test.end());
   }
   
   virtual ~Test() 
   { 
      destroy();
   }

   virtual void add(std::string name, std::function<int32_t ()> f)
   {
      _test.insert(std::pair<std::string, std::function<int32_t ()>>(name, f));  
   }
   
   virtual void run(bool haltOnError)
   {
      int32_t error = 0;
      
      std::clog << "---------------------------------------------" << std::endl;
      std::clog << "Running " << _name << std::endl;
      std::clog << "---------------------------------------------" << std::endl;
      uint32_t k = 0;
      uint32_t i = 0;
      for(auto it = _test.begin(); it != _test.end(); it++)
      {
         k++;
         std::clog << "Case " << k << ": " << it->first << std::endl;
         std::cout << "Case " << k << ": " << it->first << std::endl;
         error += it->second();   
         if(haltOnError && error != 0)
         {
            std::clog << "Error: " << it->first << std::endl;
            exit(EXIT_FAILURE);  
         }
         else if(error != 0)
         {
            i++;
         }
      }
      
      std::clog << "Passed " << (k-i) << "/" << k << std::endl;
      std::cout << "Passed " << (k-i) << "/" << k << std::endl;
   }
   
   ///! \deprecated Do not use this anymore.
   virtual int32_t run(std::function<int32_t ()> f, std::string name)
   {
      std::clog << "Running test: " << name << std::endl;
      int32_t result = f();
      if(result == EXIT_SUCCESS)
      {
         std::clog << "[PASSED]" << std::endl;
      }
      else
      {
         std::clog << "[FAILED]" << std::endl;
      }   
      return result;
   }
private:
   //! \brief Name of the test.
   std::string _name;
   
   //! \brief Tast cases mapped by a descriptive test name.
   std::map<std::string, std::function<int32_t ()>> _test;
   
   //! \brief Private copy constructor. 
   Test(Test const&);
   
   //! \brief Private assignment operator.
   Test& operator=(Test const&);
};

#endif

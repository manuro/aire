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
//! \brief Test case that handles test functions.
//!
//! A test case can have multiple test functions. Just add a test function 
//! using the add member. Please ensure that all function names are unique.
#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <functional>
#include <cstdint>
#include <map>
#include <vector>

//! \brief Global aire namespace.
namespace aire
{

//! \brief Test case that handles test functions.
class Test
{
public:  
   //! \brief Constructor of a test object.
   //! \param name Name of the test case.
   Test(std::string name) 
   { 
      initialize(name);      
   }
   
   //! \brief Initialize the test case.
   //! \param name Name of the test case.
   virtual void initialize(std::string name)
   {
      _name = name;
   }
   
   //! \brief Destroy a test case object and free all used memory.
   virtual void destroy()
   {
      _test.erase(_test.begin(), _test.end());
   }
   
   //! \brief Destructor of a test object that calls destroy.
   virtual ~Test() 
   { 
      destroy();
   }

   //! \brief Adds test function to the test case.
   //! \param name Name of the function.
   //! \param f The test function.
   virtual void add(std::string name, std::function<int32_t ()> f)
   {
      if(_test.find(name) == _test.end())
      {
         _test.insert(
            std::pair<std::string, std::function<int32_t ()>>(name, f));  
      }
      else
      {
         std::cerr << "Test with name: " << name << " exists." << std::endl;
      }
   }
   
   //! \brief Runs all test functions in the test case.
   //! \param haltOnError Indicates if the test aborts if an error occurs.
   virtual void run(bool haltOnError = false)
   {
      int32_t error = 0;
      
      std::clog << "---------------------------------------------" << std::endl;
      std::clog << "Running " << _name << std::endl;
      std::clog << "---------------------------------------------" << std::endl;
      uint32_t k = 0;
      uint32_t i = 0;
      std::vector<std::string> failed;
      
      // For every test function
      for(auto it = _test.begin(); it != _test.end(); it++)
      {
         k++;
         std::clog << "Case " << k << ": " << it->first << std::endl;
         std::cout << "Case " << k << ": " << it->first << std::endl;
         error = it->second();   
         if(haltOnError && error != 0)
         {
            failed.push_back(it->first);
            std::clog << "Error: " << it->first << std::endl;
            exit(EXIT_FAILURE);  
         }
         else if(error != 0)
         {
            failed.push_back(it->first);
            i++;
         }
      }
      
      std::clog << "Pass: " << (k-i) << "/" << k << " Fail: " << i << std::endl;
      std::cout << "Pass: " << (k-i) << "/" << k << " Fail: " << i << std::endl;
      
      // Print out faild cases
      for(auto it = failed.begin(); it != failed.end(); it++)
      {
         std::clog << "Fail: " << *it << std::endl;
         std::cout << "Fail: " << *it << std::endl;
      }
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

}
#endif

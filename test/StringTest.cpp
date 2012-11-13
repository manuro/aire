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
//! \file StringTest.cpp
//! \brief Test driver for basic string utility functions. 

#include <cstdlib>
#include <string>

#include "String.h"
#include "Test.h"

// --- Main --------------------------------------------------------------------
int main()
{
   aire::Test test("String-Test");
   
   test.add("Substring count UTF-16", [] () -> int {
      int result = EXIT_SUCCESS;   
      std::basic_string<char> text("Ni N NI nI NiiniNi Niii");      
      uint32_t count = aire::String::CountSubstr<char>(text, "Ni");
      if(count != 4) 
      {
         result = EXIT_FAILURE;
      }
      return result;
   }
   );

   test.add("Substring count UTF-8", [] () -> int {
      int result = EXIT_SUCCESS;
      std::basic_string<wchar_t> text(L"Ni N NI nI NiiniNi Niii");      
      uint32_t count = aire::String::CountSubstr<wchar_t>(text, L"Ni");
      if(count != 4) 
      {
         result = EXIT_FAILURE;
      }
      return result;
   }
   );

   test.add("Substring replace UTF-16", [] () -> int {
      int result = EXIT_SUCCESS;   
      std::basic_string<char> text("Ni N NI nI NiiniNi Niii");      
      std::basic_string<char> key("Ni");
      std::basic_string<char> value("XYZ");
      auto replace = aire::String::ReplaceSubstr<char>(text, key, value);
      if(replace != "XYZ N NI nI XYZiniXYZ XYZii") 
      {
         result = EXIT_FAILURE;
      }
      return result;
   }
   );
   
   test.add("Substring replace UTF-8", [] () -> int {
      int result = EXIT_SUCCESS;   
      std::basic_string<wchar_t> text(L"Ni N NI nI NiiniNi Niii");      
      std::basic_string<wchar_t> key(L"Ni");
      std::basic_string<wchar_t> value(L"XYZ");
      auto replace = aire::String::ReplaceSubstr<wchar_t>(text, key, value);
      if(replace != L"XYZ N NI nI XYZiniXYZ XYZii") 
      {
         result = EXIT_FAILURE;
      }
      return result;
   }
   );


   test.run();
  
   return EXIT_SUCCESS;
}

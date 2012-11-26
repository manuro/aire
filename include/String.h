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
//! \file String.h
//! \brief Some utility functions to deal with strings. 
#ifndef STRING_H
#define STRING_H

//! \brief Global aire namespace.
namespace aire 
{

//! \brief Implements some utility functions for strings.
class String 
{
public:
   //! \brief Count the occurrences of a substring.
   //! \param text String to analyze.
   //! \param key Substring to search for.
   //! \return Number of substring occurrences. 
   template<class CharType>
   static uint32_t CountSubstr(const std::basic_string<CharType>& text,
      const std::basic_string<CharType>& key)
   {
      uint32_t count = 0;
      size_t pos = text.find(key);
      while(pos != std::string::npos)
      {
         count++;
         pos = text.find(key, pos+key.length());
      }
      return count;
   }

   //! \brief Substitute all substrings in a string using.
   //! \param text String to transform.
   //! \param key Substring to search for.
   //! \param value Substitution string.
   //! \return New string with the substitutions.
   template<class CharType>
   static std::basic_string<CharType> ReplaceSubstr(
      const std::basic_string<CharType>& text,
      const std::basic_string<CharType>& key,
      const std::basic_string<CharType>& value)
   {
      std::basic_string<CharType> result(text);
      size_t pos = result.find(key);
      while(pos != std::string::npos)
      {
         result.replace(pos, key.length(), value);
         pos = result.find(key, pos + value.length());
      }
      return result;
   }
};

}

#endif

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
//! \file Stream.h
//! \brief Implementation of the stream. 
#ifndef STREAM_H
#define STREAM_H

#include <iostream>
#include <sstream>

//! \brief Global aire namespace.
namespace aire 
{

//! \brief Defines a synchronized output stream.
//!
//! This class implements a stream that is synchronized for output from 
//! different threads. Use it as:
//! std::cout<<(Stream()<<"ID:"<<omp_get_thread_num()<<"\n").toString();  
class Stream
{
public:
   //! \brief Constructor of the object.
   Stream() { }
   
   //! \brief Destructor of the object.
   virtual ~Stream() { }
   
   //! \brief Convertes the stream to a string.
   //! \return A standard string. 
   std::string toString() const
   {
      return _outStream.str();
   }
 
   //! \brief Overloads the operator in a templated way.
   //! Because of the lack of visibility for the compiler the implementation 
   //! of this function must be here.
   //! \param data Templated data to be added to the stream.
   //! \return The class itself.
   template<class T> Stream& operator<<(const T& data)
   {
      _outStream << data;
      return *this;
   }

private:
   //! \brief Output stream member. 
   std::ostringstream _outStream;
   
   //! \brief Private copy constructor. 
   Stream(Stream const&);
   
   //! \brief Private assignment operator. 
   Stream& operator=(Stream const&);
};

}
#endif

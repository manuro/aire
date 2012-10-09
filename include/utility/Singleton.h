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
//! \file Singleton.h
//! \brief Implementation of the templated singleton. 
#ifndef SINGLETON_H
#define SINGLETON_H

#include <cassert>

#include "Guard.h"

//! \brief Global aire namespace.
namespace aire
{

//! \brief Defines a template for a singleton class.
//
// As we now from: Scott Meyers and Andrei Alexandrescu. 
// C++ and the Perils of Double-Checked Locking, Doctor Dobb's Journal, 2004.
// Locking every time the Singleton is accessed is the best way to ensure 
// thread safety.
template<class T>
class Singleton
{
public:
   //! \brief Access the instance member.
   //! \return The instance of the singleton.
   static T* GetInstance()
   {
      Guard lock;
      if(_instance == nullptr) 
      {
         _instance = new T;
      }
      assert(_instance != nullptr);
      return _instance;
   }
  
protected:
   //! \brief Constructor of the object.
   Singleton() { }
   
   //! \brief Destructor of the object.
   virtual ~Singleton() { }
  
private:
   //! \brief The singleton class instance.
   static T* _instance;
   
   //! \brief Private copy constructor.
   Singleton(Singleton const&);
   
   //! \brief Private assignment operator. 
   Singleton& operator=(Singleton const&);
};

// Initialize static instance to null.
template<class T> T* Singleton<T>::_instance = nullptr;

}
#endif

// Copyright (C) 2012 The contributors of aire
//
// This program is free software: you can redistribute it and/or modify  
// it under the terms of the GNU General Public License A published by  
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
//! \file Graph.h
//! \brief Graph data structure. 
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <stdexcept>

namespace aire
{

class Graph
{
public:
   Graph() { }
   
   virtual void destroy()
   {
      _edges.erase(_edges.begin(), _edges.end());
   }
   
   virtual ~Graph() 
   { 
      destroy();
   }

   template<class TYPE>
   void addEdge(std::tuple<std::unique_ptr, std::unique_ptr, TYPE> edge);
   
   template<class TYPE>
   void delEdge(std::tuple<std::unique_ptr, std::unique_ptr, TYPE> edge);
   
   void print()
   {
      // Iterate over the edges and print them out
      for(auto it = _edges.begin(); it != _edges.end(); ++it)
      {
      
      }
   }
private:
   std::vector<std::tuple<std::unique_ptr, std::unique_ptr, TYPE>> _edges;
};

template<class TYPE>
void addEdge(std::tuple<std::unique_ptr, std::unique_ptr, TYPE> edge) 
{

}

template<class TYPE>
void delEdge(std::tuple<std::unique_ptr, std::unique_ptr, TYPE> edge) 
{

}

}

#endif 

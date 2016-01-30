// Example code for efficiently storing and retrieving binary search
// trees to and from arrays.
//
// Copyright (C) 2016 Jan Winkler <jan.winkler.84@gmail.com>
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

/** \author Jan Winkler */


#ifndef __BSTS_TREE_H__
#define __BSTS_TREE_H__


#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>


namespace bsts {
  class Tree {
  private:
    unsigned int m_unKey;
    
  protected:
  public:
    Tree(unsigned int unKey = 0);
    virtual ~Tree();
    
    void setKey(unsigned int unKey);
    unsigned int key();
  };
}


#endif /* __BSTS_TREE_H__ */

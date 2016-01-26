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


#ifndef __BSTS_BINARY_TREE_H__
#define __BSTS_BINARY_TREE_H__


#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>


namespace bsts {
  class BinaryTree : public std::enable_shared_from_this<BinaryTree> {
  private:
    unsigned int m_unKey;
    std::shared_ptr<BinaryTree> m_arrbtChildren[2];
    
  protected:
    virtual std::shared_ptr<BinaryTree> instantiateChild();
    std::shared_ptr<BinaryTree> child(unsigned int unIndex, bool bCreateIfNonExistant = false);
    void setChild(unsigned int unIndex, std::shared_ptr<BinaryTree> btSet);
    
  public:
    BinaryTree(unsigned int unKey = 0);
    virtual ~BinaryTree();
    
    std::shared_ptr<BinaryTree> left(bool bCreateIfNonExistant = false);
    std::shared_ptr<BinaryTree> right(bool bCreateIfNonExistant = false);
    
    void setLeft(std::shared_ptr<BinaryTree> btSet);
    void setRight(std::shared_ptr<BinaryTree> btSet);
    
    void setKey(unsigned int unKey);
    unsigned int key();
    
    std::string print();
    
    unsigned int count();
    unsigned int depth();
    
    unsigned int nthLargest(unsigned int unN);
    unsigned int nthLargest(unsigned int unN, unsigned int& unOffset);
    
    bool equal(std::shared_ptr<BinaryTree> btCompare);
  };
}


#endif /* __BSTS_BINARY_TREE_H__ */

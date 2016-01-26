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


#ifndef __BSTS_BINARY_SEARCH_TREE_H__
#define __BSTS_BINARY_SEARCH_TREE_H__


#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include <bsts/BinaryTree.h>


namespace bsts {
  class BinarySearchTree : public BinaryTree {
  private:
  protected:
    std::shared_ptr<BinaryTree> instantiateChild() override;
    
  public:
    BinarySearchTree(unsigned int unKey = 0);
    ~BinarySearchTree();
    
    static std::shared_ptr<BinarySearchTree> randomTree(std::shared_ptr<BinarySearchTree> bstParent = NULL, int nMaxDepth = 3, unsigned int unMinKeyValue = 0, unsigned int unMaxKeyValue = 1000);
    
    std::vector<unsigned int> toArray();
    void fromArray(std::vector<unsigned int> vecArray, bool bLeftBranch = true, std::shared_ptr<BinaryTree> btParent = NULL, unsigned int unLargestParentKey = 0, bool bEverBranchedLeft = false);
    
    bool isBinarySearchTree();
    
    std::shared_ptr<BinarySearchTree> left(bool bCreate = false);
    std::shared_ptr<BinarySearchTree> right(bool bCreate = false);
  };
}


#endif /* __BSTS_BINARY_SEARCH_TREE_H__ */

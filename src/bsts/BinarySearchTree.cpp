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


#include <bsts/BinarySearchTree.h>


namespace bsts {
  BinarySearchTree::BinarySearchTree(unsigned int unKey) : BinaryTree(unKey) {
  }
  
  BinarySearchTree::~BinarySearchTree() {
  }
  
  std::shared_ptr<BinaryTree> BinarySearchTree::instantiateChild() {
    return std::dynamic_pointer_cast<BinaryTree>(std::make_shared<BinarySearchTree>());
  }
  
  std::shared_ptr<BinarySearchTree> BinarySearchTree::randomTree(std::shared_ptr<BinarySearchTree> bstParent, int nMaxDepth, unsigned int unMinKeyValue, unsigned int unMaxKeyValue) {
    std::shared_ptr<BinarySearchTree> bstRandom = NULL;
    
    if(nMaxDepth > 0) {
      if(unMaxKeyValue != unMinKeyValue) {
	unsigned int unRandomKey = (rand() % (unMaxKeyValue - unMinKeyValue)) + unMinKeyValue;
	bstRandom = (bstRandom ? bstParent : std::make_shared<BinarySearchTree>(unRandomKey));
	
	// Space for a left child?
	if(bstRandom->key() > unMinKeyValue) {
	  // Flip a coin: Create a left child?
	  if(rand() % 2 == 0) {
	    bstRandom->setLeft(randomTree(bstRandom, nMaxDepth - 1, unMinKeyValue, bstRandom->key() - 1));
	  }
	}
	
	// Space for a right child?
	if(bstRandom->key() < unMaxKeyValue) {
	  // Flip a coin: Create a right child?
	  if(rand() % 2 == 0) {
	    bstRandom->setRight(randomTree(bstRandom, nMaxDepth - 1, bstRandom->key() + 1, unMaxKeyValue));
	  }
	}
      }
    }
    
    return bstRandom;
  }
  
  std::shared_ptr<BinarySearchTree> BinarySearchTree::left(bool bCreate) {
    std::shared_ptr<BinaryTree> btLeft = this->BinaryTree::left(bCreate);
    
    if(btLeft) {
      return std::dynamic_pointer_cast<BinarySearchTree>(btLeft);
    }
    
    return NULL;
  }
  
  std::shared_ptr<BinarySearchTree> BinarySearchTree::right(bool bCreate) {
    std::shared_ptr<BinaryTree> btRight = this->BinaryTree::right(bCreate);
    
    if(btRight) {
      return std::dynamic_pointer_cast<BinarySearchTree>(btRight);
    }
    
    return NULL;
  }
  
  std::vector<unsigned int> BinarySearchTree::toArray() {
    std::vector<unsigned int> vecArray;
    vecArray.push_back(this->key());
    
    if(this->left()) {
      std::vector<unsigned int> vecArrayLeft = this->left()->toArray();
      vecArray.insert(vecArray.end(), vecArrayLeft.begin(), vecArrayLeft.end());
    }
    
    if(this->right()) {
      std::vector<unsigned int> vecArrayRight = this->right()->toArray();
      vecArray.insert(vecArray.end(), vecArrayRight.begin(), vecArrayRight.end());
    }
    
    return vecArray;
  }
  
  void BinarySearchTree::fromArray(std::vector<unsigned int> vecArray, bool bLeftBranch, std::shared_ptr<BinaryTree> btParent, unsigned int unSmallestParentKey, bool bEverBranchedLeft) {
    if(btParent && bLeftBranch) {
      unSmallestParentKey = std::min(unSmallestParentKey, btParent->key());
    } else if(!btParent) {
      unSmallestParentKey = 0;
      
      for(unsigned int unI : vecArray) {
	if(unI > unSmallestParentKey) {
	  unSmallestParentKey = unI;
	}
      }
    }
    
    this->setKey(vecArray[0]);
    
    // Find next left (next smaller key than this)
    for(unsigned int unI = 1; unI < vecArray.size(); unI++) {
      if(vecArray[unI] < this->key()) {
	std::vector<unsigned int> vecArrayCopy(vecArray.begin() + unI, vecArray.end());
	this->left(true)->fromArray(vecArrayCopy, true, this->shared_from_this(), unSmallestParentKey, true);
	
	break;
      }
    }
    
    // Find next right (next bigger key than this, no larger than smallest parent key when last branching left, smaller than parent if in parent's left branch)
    for(unsigned int unI = 1; unI < vecArray.size(); unI++) {
      bool bSmallerThanParentOK = (btParent ? vecArray[unI] < btParent->key() : true);
      bool bNoLargerThanLastLeftBranchParent = (bEverBranchedLeft ? vecArray[unI] < unSmallestParentKey : true);
      
      if(vecArray[unI] > this->key() && (!bLeftBranch || (bLeftBranch && bSmallerThanParentOK)) && bNoLargerThanLastLeftBranchParent) {
	std::vector<unsigned int> vecArrayCopy(vecArray.begin() + unI, vecArray.end());
	this->right(true)->fromArray(vecArrayCopy, false, this->shared_from_this(), unSmallestParentKey, bEverBranchedLeft);
	
	break;
      }
    }
  }
  
  bool BinarySearchTree::isBinarySearchTree() {
    bool bResult = true;
    
    if(this->left()) {
      if(!(this->left()->key() < this->key())) {
	bResult = false;
      }
    }
    
    if(this->right()) {
      if(!(this->right()->key() > this->key())) {
	bResult = false;
      }
    }
    
    return bResult;
  }
}

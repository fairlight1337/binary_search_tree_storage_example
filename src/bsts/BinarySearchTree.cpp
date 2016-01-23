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
  BinarySearchTree::BinarySearchTree(unsigned int unKey) : m_unKey(unKey) {
  }
  
  BinarySearchTree::~BinarySearchTree() {
  }
  
  std::shared_ptr<BinarySearchTree> BinarySearchTree::child(unsigned int unIndex, bool bCreateIfNonExistant) {
    if(unIndex >= 0 && unIndex < 2) {
      if(!m_arrbstChildren[unIndex] && bCreateIfNonExistant) {
	m_arrbstChildren[unIndex] = std::make_shared<BinarySearchTree>();
      }
    
      return m_arrbstChildren[unIndex];
    } else {
      return NULL;
    }
  }
  
  std::shared_ptr<BinarySearchTree> BinarySearchTree::left(bool bCreateIfNonExistant) {
    return this->child(0, bCreateIfNonExistant);
  }
  
  std::shared_ptr<BinarySearchTree> BinarySearchTree::right(bool bCreateIfNonExistant) {
    return this->child(1, bCreateIfNonExistant);
  }
  
  void BinarySearchTree::setChild(unsigned int unIndex, std::shared_ptr<BinarySearchTree> bstSet) {
    if(unIndex >= 0 && unIndex < 2) {
      m_arrbstChildren[unIndex] = bstSet;
    }
  }
  
  void BinarySearchTree::setLeft(std::shared_ptr<BinarySearchTree> bstSet) {
    this->setChild(0, bstSet);
  }
  
  void BinarySearchTree::setRight(std::shared_ptr<BinarySearchTree> bstSet) {
    this->setChild(1, bstSet);
  }
  
  std::string BinarySearchTree::print() {
    std::string strLeft = (this->left() ? "l=" + this->left()->print() : "");
    std::string strRight = (this->right() ? "r=" + this->right()->print() : "");
    std::string strChildren = "";
    
    if(strLeft != "") {
      strChildren = strLeft;
    }
    
    if(strRight != "") {
      strChildren += (strChildren != "" ? "; " : "") + strRight;
    }
    
    std::stringstream sts;
    sts << m_unKey;
    
    return "(" + sts.str() + (strChildren != "" ? "; " + strChildren : "") + ")";
  }
  
  void BinarySearchTree::setKey(unsigned int unKey) {
    m_unKey = unKey;
  }
  
  unsigned int BinarySearchTree::key() {
    return m_unKey;
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
  
  unsigned int BinarySearchTree::count() {
    int nLeftCount = (this->left() ? this->left()->count() : 0);
    int nRightCount = (this->right() ? this->right()->count() : 0);
    
    return nLeftCount + nRightCount + 1;
  }
  
  unsigned int BinarySearchTree::depth() {
    int nDepth = 0;
    
    if(this->left() || this->right()) {
      int nLeftDepth = (this->left() ? this->left()->depth() : 0);
      int nRightDepth = (this->right() ? this->right()->depth() : 0);
      
      if(nLeftDepth > nRightDepth) {
	nDepth = nLeftDepth + 1;
      } else {
	nDepth = nRightDepth + 1;
      }
    }
    
    return nDepth;
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
  
  void BinarySearchTree::fromArray(std::vector<unsigned int> vecArray, bool bLeftBranch, std::shared_ptr<BinarySearchTree> bstParent, unsigned int unSmallestParentKey, bool bEverBranchedLeft) {
    if(bstParent && bLeftBranch) {
      unSmallestParentKey = std::min(unSmallestParentKey, bstParent->key());
    } else if(!bstParent) {
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
      bool bSmallerThanParentOK = (bstParent ? vecArray[unI] < bstParent->key() : true);
      bool bNoLargerThanLastLeftBranchParent = (bEverBranchedLeft ? vecArray[unI] < unSmallestParentKey : true);
      
      if(vecArray[unI] > this->key() && (!bLeftBranch || (bLeftBranch && bSmallerThanParentOK)) && bNoLargerThanLastLeftBranchParent) {
	std::vector<unsigned int> vecArrayCopy(vecArray.begin() + unI, vecArray.end());
	this->right(true)->fromArray(vecArrayCopy, false, this->shared_from_this(), unSmallestParentKey, bEverBranchedLeft);
	
	break;
      }
    }
  }
  
  unsigned int BinarySearchTree::nthLargest(unsigned int unN) {
    unsigned int unOffset = 0;
    
    return this->nthLargest(unN, unOffset);
  }
  
  unsigned int BinarySearchTree::nthLargest(unsigned int unN, unsigned int& unOffset) {
    // TODO(winkler): Buggy; doesn't return the right values.
    
    unsigned int unLargest = 0;
    
    if(unOffset == unN) {
      unLargest = this->key();
    } else {
      if(this->right()) {
	unLargest = this->right()->nthLargest(unN, unOffset);
	unOffset++;
      }
      
      if(unOffset == unN) {
	unLargest = this->key();
      } else {
	if(this->left()) {
	  unOffset++;
	  unLargest = this->left()->nthLargest(unN, unOffset);
	}
	
	if(unOffset == unN) {
	  unLargest = this->key();
	}
      }
    }
    
    return unLargest;
  }
}

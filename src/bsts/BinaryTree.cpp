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


#include <bsts/BinaryTree.h>


namespace bsts {
  BinaryTree::BinaryTree(unsigned int unKey) : m_unKey(unKey) {
  }
  
  BinaryTree::~BinaryTree() {
  }
  
  std::shared_ptr<BinaryTree> BinaryTree::child(unsigned int unIndex, bool bCreateIfNonExistant) {
    if(unIndex >= 0 && unIndex < 2) {
      if(!m_arrbtChildren[unIndex] && bCreateIfNonExistant) {
	m_arrbtChildren[unIndex] = std::make_shared<BinaryTree>();
      }
    
      return m_arrbtChildren[unIndex];
    } else {
      return NULL;
    }
  }
  
  std::shared_ptr<BinaryTree> BinaryTree::left(bool bCreateIfNonExistant) {
    return this->child(0, bCreateIfNonExistant);
  }
  
  std::shared_ptr<BinaryTree> BinaryTree::right(bool bCreateIfNonExistant) {
    return this->child(1, bCreateIfNonExistant);
  }
  
  void BinaryTree::setChild(unsigned int unIndex, std::shared_ptr<BinaryTree> btSet) {
    if(unIndex >= 0 && unIndex < 2) {
      m_arrbtChildren[unIndex] = btSet;
    }
  }
  
  void BinaryTree::setLeft(std::shared_ptr<BinaryTree> btSet) {
    this->setChild(0, btSet);
  }
  
  void BinaryTree::setRight(std::shared_ptr<BinaryTree> btSet) {
    this->setChild(1, btSet);
  }
  
  std::string BinaryTree::print() {
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
  
  void BinaryTree::setKey(unsigned int unKey) {
    m_unKey = unKey;
  }
  
  unsigned int BinaryTree::key() {
    return m_unKey;
  }
  
  unsigned int BinaryTree::count() {
    int nLeftCount = (this->left() ? this->left()->count() : 0);
    int nRightCount = (this->right() ? this->right()->count() : 0);
    
    return nLeftCount + nRightCount + 1;
  }
  
  unsigned int BinaryTree::depth() {
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
  
  unsigned int BinaryTree::nthLargest(unsigned int unN) {
    unsigned int unOffset = 0;
    
    return this->nthLargest(unN, unOffset);
  }
  
  unsigned int BinaryTree::nthLargest(unsigned int unN, unsigned int& unOffset) {
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

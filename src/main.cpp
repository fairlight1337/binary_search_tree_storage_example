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


#include <iostream>
#include <cstdlib>
#include <time.h>

#include <bsts/BinarySearchTree.h>


int main(int argc, char** argv) {
  int nReturnvalue = EXIT_SUCCESS;
  
  int nMaxDepth = 3;
  bool bStartOK = false;
  
  if(argc == 1) {
    std::cout << "No max depth given, assuming " << nMaxDepth << "." << std::endl;
    bStartOK = true;
  } else if(argc == 2) {
    if(sscanf(argv[1], "%d", &nMaxDepth) == 1) {
      bStartOK = true;
    } else {
      std::cerr << "Parameter ('" << argv[1] << "') not a invalid max depth." << std::endl;
    }
  }
  
  if(bStartOK) {
    srand(time(NULL));
    
    std::shared_ptr<bsts::BinarySearchTree> bstTree = bsts::BinarySearchTree::randomTree(NULL, nMaxDepth);
    std::cout << "Random tree:" << std::endl;
    std::cout << bstTree->print() << std::endl;
    std::cout << "Depth: " << bstTree->depth() << std::endl;
    std::cout << "Count: " << bstTree->count() << std::endl;
    
    std::vector<unsigned int> vecArray = bstTree->toArray();
    
    std::cout << std::endl;
    
    std::cout << "Array: [";
    bool bFirst = true;
    for(unsigned int unKey : vecArray) {
      if(bFirst) {
	bFirst = false;
      } else {
	std::cout << " ";
      }
      
      std::cout << unKey;
    }
    std::cout << "]" << std::endl;
    
    std::cout << std::endl;
    
    std::shared_ptr<bsts::BinarySearchTree> bstReconstructed = std::make_shared<bsts::BinarySearchTree>(0);
    bstReconstructed->fromArrayPreorderTraversal(vecArray);
    
    std::cout << "Reconstructed tree:" << std::endl;
    std::cout << bstReconstructed->print() << std::endl;
    std::cout << "Depth: " << bstReconstructed->depth() << std::endl;
    std::cout << "Count: " << bstReconstructed->count() << std::endl;
    
    unsigned int unNthLargestN = rand() % bstReconstructed->count() + 1;
    std::cout << unNthLargestN << (unNthLargestN == 1 ? "st" : (unNthLargestN == 2 ? "nd" : (unNthLargestN == 3 ? "rd" : "th"))) << " largest key: " << bstReconstructed->nthLargest(unNthLargestN - 1) << std::endl;
    
    std::cout << "Is a binary search tree: " << (bstReconstructed->isBinarySearchTree() ? "yes" : "no") << std::endl;
    
    std::cout << "Traversing breadth-first:" << std::endl;
    bstReconstructed->traverse(bsts::BinaryTree::BreadthFirst, bsts::BinaryTree::NotApplicable, [](std::shared_ptr<bsts::BinaryTree> btTree) { std::cout << btTree->key() << std::endl; });
    
    std::cout << "Traversing depth-first (preorder):" << std::endl;
    bstReconstructed->traverse(bsts::BinaryTree::DepthFirst, bsts::BinaryTree::PreOrder, [](std::shared_ptr<bsts::BinaryTree> btTree) { std::cout << btTree->key() << std::endl; });
  } else {
    std::cerr << "Usage: " << argv[0] << " [max depth (integer)]" << std::endl;
    nReturnvalue = EXIT_FAILURE;
  }
  
  std::shared_ptr<bsts::BinaryTree> btCmp1 = std::make_shared<bsts::BinaryTree>(1);
  btCmp1->left(true)->setKey(2);
  btCmp1->right(true)->setKey(3);
  
  std::shared_ptr<bsts::BinaryTree> btCmp2 = std::make_shared<bsts::BinaryTree>(1);
  btCmp2->left(true)->setKey(2);
  btCmp2->right(true)->setKey(3);
  
  std::cout << std::endl;
  std::cout << "Comparing trees:" << std::endl;
  btCmp1->print();
  btCmp2->print();
  
  std::cout << "Trees equal: " << (btCmp1->equal(btCmp2) ? "yes" : "no") << std::endl;
  
  return nReturnvalue;
}

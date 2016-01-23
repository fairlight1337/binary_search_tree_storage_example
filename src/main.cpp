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
    bstReconstructed->fromArray(vecArray);
    
    std::cout << "Reconstructed tree:" << std::endl;
    std::cout << bstReconstructed->print() << std::endl;
    std::cout << "Depth: " << bstReconstructed->depth() << std::endl;
    std::cout << "Count: " << bstReconstructed->count() << std::endl;
  } else {
    std::cerr << "Usage: " << argv[0] << " [max depth (integer)]" << std::endl;
    nReturnvalue = EXIT_FAILURE;
  }
  
  return nReturnvalue;
}

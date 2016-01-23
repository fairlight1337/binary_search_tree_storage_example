#ifndef __BSTS_BINARY_SEARCH_TREE_H__
#define __BSTS_BINARY_SEARCH_TREE_H__


#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>


namespace bsts {
  class BinarySearchTree : public std::enable_shared_from_this<BinarySearchTree> {
  private:
    unsigned int m_unKey;
    std::shared_ptr<BinarySearchTree> m_arrbstChildren[2];
    
  protected:
    std::shared_ptr<BinarySearchTree> child(unsigned int unIndex, bool bCreateIfNonExistant = false);
    void setChild(unsigned int unIndex, std::shared_ptr<BinarySearchTree> bstSet);
    
  public:
    BinarySearchTree(unsigned int unKey = 0);
    ~BinarySearchTree();
    
    std::shared_ptr<BinarySearchTree> left(bool bCreateIfNonExistant = false);
    std::shared_ptr<BinarySearchTree> right(bool bCreateIfNonExistant = false);
    
    void setLeft(std::shared_ptr<BinarySearchTree> bstSet);
    void setRight(std::shared_ptr<BinarySearchTree> bstSet);
    
    void setKey(unsigned int unKey);
    unsigned int key();
    
    std::string print();
    
    static std::shared_ptr<BinarySearchTree> randomTree(std::shared_ptr<BinarySearchTree> bstParent = NULL, int nMaxDepth = 3, unsigned int unMinKeyValue = 0, unsigned int unMaxKeyValue = 1000);
    
    unsigned int count();
    unsigned int depth();
    
    std::vector<unsigned int> toArray();
    void fromArray(std::vector<unsigned int> vecArray, bool bLeftBranch = true, std::shared_ptr<BinarySearchTree> bstParent = NULL, unsigned int unLargestParentKey = 0, bool bEverBranchedLeft = false);
  };
}


#endif /* __BSTS_BINARY_SEARCH_TREE_H__ */

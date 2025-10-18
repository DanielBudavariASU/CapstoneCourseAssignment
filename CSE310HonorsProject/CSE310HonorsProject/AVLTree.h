// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Daniel Budavari
// ASU ID:1224612207
// Description:  

#define AVL_TREE_H  
#include <iostream>  
#include <iomanip>
using namespace std;

// Declaration of your AVL tree node class
struct TreeNode {
    int key;
    int balFactor;  
    int height;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode* parent;
};

class Tree {
private:
    TreeNode* root;
public:
    Tree();
    ~Tree();
    TreeNode* getRoot();
   
    int search(int key, TreeNode* subRoot);
    bool insert(int key, TreeNode* subRoot, TreeNode* prev);
    bool deleteNode(int key, TreeNode* subRoot, TreeNode* prev, TreeNode* data);
    void deleteSubTree(TreeNode* subRoot);
    
    void balanceTree(TreeNode* subRoot, TreeNode* prev);
    void calculateBH(TreeNode* subRoot, TreeNode* prev);
    void rotateLeft(TreeNode* subRoot, TreeNode* prev);
    void rotateRight(TreeNode* subRoot, TreeNode* prev);
    void rotateRightLeft(TreeNode* subRoot, TreeNode* prev);
    void rotateLeftRight(TreeNode* subRoot, TreeNode* prev);
    
    void preOrderPrint(TreeNode* subRoot);
    void postOrderPrint(TreeNode* subRoot);
    void print(TreeNode* node); //acts as in-order
    void printTree(TreeNode* subRoot);
}; 
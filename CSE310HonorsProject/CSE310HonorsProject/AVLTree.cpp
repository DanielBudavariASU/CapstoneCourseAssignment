// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Daniel Budavari
// ASU ID:1224612207
// Description: 

#include "AVLTree.h" 
using namespace std;

Tree::Tree() {
    root = NULL;
}

Tree::~Tree() {
    deleteSubTree(root);
    return;
}

//functions are separated by these dashes for clarity
//-------------------------------------------------------------------------------------------------------------------------------------
int Tree::search(int key, TreeNode* subRoot) {

    if (subRoot == NULL) {
        return -1;          //the node w/ key cannot be found, return -1
    }

    if (key < subRoot->key) {               //key is less than subroot, will be on the left side
        return search(key, subRoot->leftChild);
    }
    else if (key > subRoot->key) {          //key is greater than subroot, will be on the right side
        return search(key, subRoot->rightChild);
    }
    else {
        return subRoot->key; //the node w/ key is found, return it
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------
bool Tree::insert(int key, TreeNode* subRoot, TreeNode* prev) {

    if (search(key, root) != -1) {
        cout << "Key is a duplicate." << endl;
        return false;
    }
    //Root pointer and prev (points to NULL)
    TreeNode* parent = prev;
    TreeNode* rootStart = subRoot;
    
    //New node to be added
    TreeNode* newNode = new TreeNode();
    newNode->key = key;
    newNode->height = 1;

    //General BST Insertion
    //If list is empty and nod should be the Root
    if (subRoot == NULL) {
        root = newNode;
        newNode->parent = NULL;
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        return true;
    }
    //Traverse left and right subtrees, comparing keys to find
    //proper location
    while (rootStart != NULL) {
        parent = rootStart;
        if (newNode->key < rootStart->key) {
            rootStart = rootStart->leftChild;
        }
        else {
            rootStart = rootStart->rightChild;
        }
    }
    newNode->parent = parent;
    //set parent nodes
    if (newNode->key < parent->key) {
        parent->leftChild = newNode;
    }
    else {
        parent->rightChild = newNode;
    }
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;

    //calculate the balance factor and height of the newly inserted node
    //then call balance tree to fix any issues that may arise (imbalance)
    if (newNode->parent != NULL) {
        balanceTree(newNode, newNode->parent);
    }
    return true;   
}

//recursive starting from the root
void Tree::calculateBH(TreeNode* subRoot, TreeNode* prev) {

    if (subRoot != NULL) {
        int heightL = 0;
        int heightR = 0;

        if (subRoot->leftChild != NULL) {
            heightL = subRoot->leftChild->height;
        }

        if (subRoot->rightChild != NULL) {
            heightR = subRoot->rightChild->height;
        }

        //Choose the max of left and right height + 1 and set the subRoot's height to it
        if (heightL > heightR) {
            subRoot->height = heightL + 1;
        }
        else {
            subRoot->height = heightR + 1;
        }
        //Calculate the subRoot node's new balance factor using its height
        subRoot->balFactor = heightL - heightR; //Left subtree height - right subtree height
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------
//In an AVL Tree the balFactor of nodes can never be less than -1 and greater than 1, so the acceptable values are -1,0,1. If it ever goes outside
// of these bounds, then re-balancing/rotating is needed to fix the balance factors and the tree itself
void Tree::balanceTree(TreeNode* subRoot, TreeNode* prev) {
    
    if (subRoot == NULL) {
        return;
    }

    calculateBH(subRoot, NULL);
    int balanceFactor = subRoot->balFactor;
    
    if (balanceFactor == -2) { //right heavy
        // RightLeft Case: node inserted in the right subtree of a left subtree node, causing imbalance
                // First a right rotation is needed, then a left rotation fixes the imbalance
        if (subRoot->rightChild->leftChild != NULL && subRoot->rightChild->balFactor > 0) {
            rotateRightLeft(subRoot, prev);
        }
        else {
            // Left Rotation Case: node inserted in the right subtree causes the right to be heavy
                //  (right subtree is imbalanced) fixed via a single left rotation
            rotateLeft(subRoot, prev);
        }
    }
    else if (balanceFactor == 2) { //left heavy
        //LeftRight Case: node inserted in the left subtree of a right subtree node, causing imbalance
               // First a left rotation is needed, then a right rotation fixes the imbalance
        if (subRoot->leftChild->rightChild != NULL && subRoot->leftChild->balFactor < 0) {
            rotateLeftRight(subRoot, prev);
        }
        else {
            // Right Rotation Case: node inserted in the left subtree causes the left to be heavy
                // (left subtree is imbalanced) fixed via a single right rotation
            rotateRight(subRoot, prev);
        }
    }
    
    //Fix heights and balance factors 
    if (prev != NULL) {
        balanceTree(prev, prev->parent);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------
//Rotates the given subRoot left and sets new height values, symmetrical to rotateRight
void Tree::rotateLeft(TreeNode* subRoot, TreeNode* prev) {
   
    if (subRoot == NULL) {
        return;
    }

    //General BST Left Rotation
    TreeNode* rightC = NULL;

    rightC = subRoot->rightChild;
    subRoot->rightChild = rightC->leftChild;
    if (rightC->leftChild != NULL) { 
        rightC->leftChild->parent = subRoot;
    }
    else {
        rightC->parent = subRoot->parent; 
    }

    if (subRoot->parent == NULL) {
        root = rightC;
        root->parent = NULL;
    }
    else if (subRoot == subRoot->parent->leftChild) {
        subRoot->parent->leftChild = rightC;
    }
    else {
        subRoot->parent->rightChild = rightC;
    }
    rightC->leftChild = subRoot;
    subRoot->parent = rightC;
    prev;

    //Recalculate our new balance and height factors of all nodes moved
    calculateBH(prev, NULL); 
    calculateBH(subRoot->parent->leftChild, NULL);
    calculateBH(subRoot->parent, NULL);
}

//-------------------------------------------------------------------------------------------------------------------------------------
//Rotates the given subRoot right and sets new height values, symmetrical to rotateLeft
void Tree::rotateRight(TreeNode* subRoot, TreeNode* prev) {
   
    if (subRoot == NULL) {
        return;
    }
    TreeNode* leftC = NULL;

    leftC = subRoot->leftChild;
    subRoot->leftChild = leftC->rightChild;
    if (leftC->rightChild != NULL) {
        leftC->rightChild->parent = subRoot;
    }
    else {
        leftC->parent = subRoot->parent;
    }

    if (subRoot->parent == NULL) {
        root = leftC;
        root->parent = NULL;
    }
    else if (subRoot == subRoot->parent->rightChild) {
        subRoot->parent->rightChild = leftC;
    }
    else {
        subRoot->parent->leftChild = leftC;
    }
    leftC->rightChild = subRoot;
    subRoot->parent = leftC;
    
    //Recalculate our new balance and height factors of all nodes moved
    calculateBH(subRoot->parent->rightChild, NULL); 
    calculateBH(prev, NULL);
    calculateBH(subRoot->parent, NULL);
}

//------------------------------------------------------------------------------------------------------------------------------------- 
//These two functions are symmetric
void Tree::rotateRightLeft(TreeNode* subRoot, TreeNode* prev) {
    rotateRight(subRoot->rightChild, subRoot); 
    rotateLeft(subRoot, prev);
}

void Tree::rotateLeftRight(TreeNode* subRoot, TreeNode* prev) {
    rotateLeft(subRoot->leftChild, subRoot);
    rotateRight(subRoot, prev);
}

//-------------------------------------------------------------------------------------------------------------------------------------
bool Tree::deleteNode(int key, TreeNode* subRoot, TreeNode* prev, TreeNode* data) {

    if (subRoot == NULL) {
        return false;
    }
    else if (search(key, root) == -1) {
        cout << "Node cannot be found in tree." << endl;
        return false;
    }

    //Navigate to node that is to be deleted
    if (subRoot->key != key) {
        if (key < subRoot->key) {
            return deleteNode(key, subRoot->leftChild, subRoot, data);
        }
        else if (key > subRoot->key) {
            return deleteNode(key, subRoot->rightChild, subRoot, data);
        }
    }
    
    // Case 1: Node to be deleted has no children
    if (subRoot->leftChild == NULL && subRoot->rightChild == NULL) {

        if (subRoot->parent == NULL) {
            root = NULL; // If subRoot is the root
        }
        else if (prev->leftChild == subRoot) { //node was the left child
            prev->leftChild = NULL;
        }
        else {
            prev->rightChild = NULL; //node was the right child
        }
        delete subRoot;
        balanceTree(prev, prev->parent); //rebalance and calculate height
        
        //Subcase for correcting node keys after deleting node w/ 2 children
        if (prev->parent->key < prev->key) {
            int temp = prev->parent->key;
            prev->parent->key = prev->key;
            prev->key = temp;
        } 
        return true;
    }

    // Case 2: Node to be deleted has only one child
    if (subRoot->leftChild == NULL) {
        TreeNode* rightC = subRoot->rightChild;

        if (prev == NULL) {
            root = rightC; // If subRoot is the root
        }
        else if (prev->leftChild == subRoot) {
            prev->leftChild = rightC;
        }
        else {
            prev->rightChild = rightC;
        }
        delete subRoot;
        balanceTree(prev, prev->parent); 
        return true;
    }
    else if (subRoot->rightChild == NULL) {
        TreeNode* leftC = subRoot->leftChild;

        if (prev == NULL) {
            root = leftC; // If subRoot is the root
        }
        else if (prev->leftChild == subRoot) {
            prev->leftChild = leftC;
        }
        else {
            prev->rightChild = leftC;
        }
        delete subRoot; 
        balanceTree(prev, prev->parent); 
        return true;
    } 
    else {// Case 3: Node to be deleted has two children 
        
        TreeNode* successor = root->rightChild;
        //Find the minimum node in the right subTree
        while (successor->leftChild != NULL) {
            successor = successor->leftChild;
        }
        subRoot->key = successor->key;
        
        return deleteNode(successor->key, subRoot->leftChild, subRoot, NULL);
    }
}

void Tree::deleteSubTree(TreeNode* subRoot) {
    
    if (subRoot == NULL) {
        return;
    }
    else if (subRoot->rightChild != NULL) {
        deleteSubTree(subRoot->rightChild);
    }
    else if (subRoot->leftChild != NULL) {
        deleteSubTree(subRoot->leftChild);
    }
        
    // Delete the current node
    delete subRoot;
}
//-------------------------------------------------------------------------------------------------------------------------------------
TreeNode* Tree::getRoot() {
    return root;
}

//-------------------------------------------------------------------------------------------------------------------------------------
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void Tree::preOrderPrint(TreeNode* subRoot) {

    if (subRoot != NULL) {
        print(subRoot);
        preOrderPrint(subRoot->leftChild); // Traverse left subtree
        preOrderPrint(subRoot->rightChild); // Traverse right subtree
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void Tree::postOrderPrint(TreeNode* subRoot) {

    if (subRoot != NULL) {
        postOrderPrint(subRoot->leftChild); // Traverse left subtree
        postOrderPrint(subRoot->rightChild); // Traverse right subtree
        print(subRoot);
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Tree::print(TreeNode* subRoot) {
    cout << left;
    cout << subRoot->key << "   balfac (" << subRoot->balFactor << ")" << "   height(" << subRoot->height << ")\n";
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Tree::printTree(TreeNode* subRoot) {

    if (root == NULL) {
        cout << "Tree is empty" << endl;
        return;
    }

    if (subRoot == NULL) {
        return;
    }

   // printTree(subRoot);
    printTree(subRoot->leftChild);
    cout << subRoot->key << "   balfac (" << subRoot->balFactor << ")" << "   height(" << subRoot->height << ")\n";
    printTree(subRoot->rightChild);
}

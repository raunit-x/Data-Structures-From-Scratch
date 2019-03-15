//
//  main.cpp
//  redBlackTrees.cpp
//
//  Created by Raunit Singh on 13/03/19.
//  Copyright © 2019 Raunit Singh. All rights reserved.
//
#include <iostream>
#include <string>
#include <queue>
using namespace std;

/*
 INSERT a NODE in an RB Tree:
    1. Perform normal BST insertion of the NODE(RED).
    2. If the NODE is ROOT then color it as BLACK and RETURN.
    3. Find the UNCLE of the NODE:
        i) if (UNCLE -> color == RED)
           ... PARENT -> color = UNCLE -> color = BLACK
           ... GRANDPARENT -> color = RED, NODE = GRANDPARENT and GOTO STEP 2
        ii) Similar to AVL Trees if UNCLE -> color == BLACK
           a) LL case (GRANDPARENT -> left == PARENT and PARENT -> left == NODE)
           b) LR case (GRANDPARENT -> left == PARENT and PARENT -> right == NODE)
           c) RR case (GRANDPARENT -> right == PARENT and PARENT -> right == NODE)
           d) RL case (GRANDPARENT -> right == PARENT and PARENT -> left == NODE)
        After performing the appropriate rotations, SWAP(PARENT -> COLOR, GRANDPARENT -> COLOR)
 */

enum Color {RED, BLACK}; // 0 -> RED, 1 -> BLACK

// This class represents a node of the Red Black Tree
class Node
{
public:
    int data;
    Node * left, *right, *parent;
    bool color;
    Node(int data) : data(data), left(NULL), right(NULL), parent(NULL), color(RED)
    {

    }
};

class RBTree
{
    Node * root;
    void rotateLeft(Node * &, Node * &);
    void rotateRight(Node * &, Node * &);
    void fixViolation(Node * &, Node * &);
public:
    RBTree() : root(NULL)
    {
        
    }
    int height();
    void inorder();
    void levelOrder();
    void insert(const int data);
    void deleteNode(const int data);
};


void RBTree::rotateLeft(Node * &root, Node * &ptr)
{
    Node * right = ptr -> right;
    
    ptr -> right = right -> left;
    
    if (ptr -> right != NULL)
        ptr -> right -> parent = ptr;
    
    right -> parent = ptr -> parent;
    
    if (!ptr -> parent)
        root = right;
    
    else if (ptr -> parent -> left == ptr)
        ptr -> parent -> left = right;
    
    else
        ptr -> parent -> right = right;
    
    right -> left = ptr;
    ptr -> parent = right;
}

void RBTree::rotateRight(Node *&root, Node *&ptr)
{
    Node * left = ptr -> left;
    
    ptr -> left = left -> right;
    
    if (ptr -> left)
        ptr -> left -> parent = ptr;
    
    left -> parent = ptr->parent;
    
    if (ptr->parent == NULL)
        root = left;
    
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left;
    
    else
        ptr->parent->right = left;
    
    left->right = ptr;
    ptr->parent = left;
}

void inorderHelper(Node * root)
{
    if(!root)
        return;
    inorderHelper(root -> left);
    cout << root -> data << " ";
    inorderHelper(root -> right);
}
void RBTree:: inorder()
{
    inorderHelper(this -> root);
}

// Normal BST insertion along with updating the parent pointers
Node * BSTInsert(Node * root, Node * newNode)
{
    if(!root)
        return newNode;
    if(newNode -> data < root -> data)
    {
        root -> left = BSTInsert(root -> left, newNode);
        root -> left -> parent = root;
    }
    else
    {
        root -> right = BSTInsert(root -> right, newNode);
        root -> right -> parent = root;
    }
    return root;
}

void RBTree::insert(const int data)
{
    Node * newNode = new Node(data);
    this -> root = BSTInsert(this -> root, newNode);
    fixViolation(root, newNode);
}

// This function is to fix the tree so that it satisfies all the RB Tree properties
void RBTree:: fixViolation(Node * &root, Node * &ptr)
{
    Node * parent = NULL;
    Node * grandParent = NULL;
    while ((ptr != root) && (ptr -> parent -> color == RED) && (ptr -> color == RED))
    {
        parent = ptr -> parent;
        grandParent = parent -> parent;
        // CASE 'A' : parent is the left child of grandParent
        if(parent == grandParent -> left)
        {
            Node * uncle = grandParent -> right;
            // If the color of the uncle is RED, then only recoloring is required
            if(uncle && uncle -> color == RED)
            {
                grandParent -> color = RED;
                parent -> color = uncle -> color = BLACK;
                ptr = grandParent;
            }
            else
            {
                // ptr is the right child of its parent
                if(parent -> right == ptr)
                {
                    rotateLeft(root, parent);
                    ptr = parent;
                    parent = ptr -> parent;
                }
                rotateRight(root, grandParent);
                swap(parent -> color, grandParent -> color);
                ptr = parent;
            }
        }
        // CASE 'B' : parent is the right child of the grandParent
        else
        {
            Node * uncle = parent -> left;
            // If the color of the uncle is RED, then only recoloring is required
            if(uncle && uncle -> color == RED)
            {
                uncle -> color = parent -> color = BLACK;
                grandParent -> color = RED;
                ptr = grandParent;
            }
            else
            {
                // Right Left case
                if(parent -> left == ptr)
                {
                    rotateRight(root, parent);
                    ptr = parent;
                    parent = ptr -> parent;
                }
                rotateLeft(root, grandParent);
                swap(parent -> color, grandParent -> color);
                ptr = parent;
            }
        }
    }
    root -> color = BLACK;
}

int heightHelper(Node * root)
{
    return (!root) ? 0 : 1 + max(heightHelper(root -> left), heightHelper(root -> right));
}

int RBTree::height()
{
    return heightHelper(this -> root);
}

void RBTree:: levelOrder()
{
    if(!root)
        return;
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while(1)
    {
        Node * front = q.front();
        q.pop();
        if(front)
        {
            if(front -> left)
                q.push(front -> left);
            if(front -> right)
                q.push(front -> right);
            cout << front -> data << " ";
        }
        else
        {
            cout << endl;
            if(q.empty())
                return;
            q.push(NULL);
        }
    }
}


Node * deleteNode(Node * root, int data)
{
    if(!root)
        return root;
    if(!root -> left && !root -> right && root -> data == data)
    {
        delete root;
        return NULL;
    }
    
    return root;
}

// Deletion of a node from the RB Tree

int main()
{
    RBTree tree;
    
    for(int i = 10; i > 0; i--)
        tree.insert(i);
    cout << "Inorder : ";
    tree.inorder();
    cout << endl;
    cout << "Height : " << tree.height() << endl;
    tree.levelOrder();
}








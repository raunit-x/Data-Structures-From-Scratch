//
//  main.cpp
//  Treaps.cpp
//
//  Created by Raunit Singh on 14/03/19.
//  Copyright © 2019 Raunit Singh. All rights reserved.
//

// Treaps are randomized BSTs which have a high probability of O(logn) for search, insertion and deletion but NOT guaranteed logn.
#include <iostream>
#include <queue>
#include <vector>
#include <random>

using namespace std;

class TreapNode
{
public:
    int data;
    int priority;
    TreapNode * left, *right;
    TreapNode(int data) : data(data), priority(rand() % 100), left(NULL), right(NULL)
    {
        
    }
};

/* T1, T2 and T3 are subtrees of the tree rooted with y
 (on left side) or x (on right side)
     y                               x
    / \     rightRotate(y)          /  \
   x   T3   – – – – – – – >        T1   y
  / \       < - - - - - - -            / \
 T1  T2     leftRotate(x)            T2  T3
 */

class Treap
{
    TreapNode * root;
public:
    Treap() : root(NULL)
    {
        
    }
    void inorder();
    void insert(const int & data);
    void deleteNode(const int & data);
    TreapNode * search(int data);
    int height();
};
TreapNode * rightRotate(TreapNode * y)
{
    TreapNode * x = y -> left;
    TreapNode * t2 = x -> right;
    x -> right = y;
    y -> left = t2;
    return x;
}


TreapNode * leftRotate(TreapNode * x)
{
    TreapNode * y = x -> right;
    TreapNode * t2 = y -> left;
    y -> left = x;
    x -> right = t2;
    return y;
}


TreapNode * searchHelper(TreapNode * root, int data)
{
    if (!root)
        return NULL;
    if(root -> data == data)
        return root;
    if(data < root -> data)
        return searchHelper(root -> left, data);
    return searchHelper(root -> right, data);
}

TreapNode * Treap:: search(int data)
{
    return searchHelper(this -> root, data);
}

TreapNode * insertHelper(TreapNode * root, int data)
{
    if(!root)
        return new TreapNode(data);
    if(data < root -> data)
    {
        root -> left = insertHelper(root -> left, data);
        if(root -> left -> priority > root -> priority)
            root = rightRotate(root);
    }
    else
    {
        root -> right = insertHelper(root -> right, data);
        if(root -> right -> priority > root -> priority)
            root = leftRotate(root);
    }
    return root;
}
void Treap:: insert(const int & data)
{
    this -> root = insertHelper(this -> root, data);
}

TreapNode * deleteNodeHelper(TreapNode * root,  int data)
{
    if(!root)
        return NULL;
    if(data < root -> data)
        root -> left = deleteNodeHelper(root -> left, data);
    else if(data > root -> data)
        root -> right = deleteNodeHelper(root -> right, data);
    else
    {
        if (!root -> left)
        {
            TreapNode * temp = root -> right;
            delete root;
            root = temp;
        }
        else if(!root -> right)
        {
            TreapNode * temp = root -> left;
            delete root;
            root = temp;
        }
        else if(root -> left -> priority > root -> right -> priority)
        {
            root = rightRotate(root);
            root -> right = deleteNodeHelper(root -> right, data);
        }
        else
        {
            root = leftRotate(root);
            root -> left = deleteNodeHelper(root -> left, data);
        }
    }
    return root;
}

void Treap:: deleteNode(const int & data)
{
    this -> root = deleteNodeHelper(this -> root, data);
}

void inorderHelper(TreapNode * root)
{
    if(!root)
        return;
    inorderHelper(root -> left);
    cout << root -> data << " ";
    inorderHelper(root -> right);
}

void Treap:: inorder()
{
    inorderHelper(this -> root);
}

int heightHelper(TreapNode * root)
{
    return (!root) ? 0 : 1 + max(heightHelper(root -> left), heightHelper(root -> right));
}

int Treap:: height()
{
    return heightHelper(this -> root);
}



int main()
{
    Treap tree;
    for(int i = 10; i > 0; i--)
        tree.insert(i);
    cout << "Inorder: ";
    tree.inorder();
    cout << endl;
    cout << "Height: " << tree.height() << endl;
}





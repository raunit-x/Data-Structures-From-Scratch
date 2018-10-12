#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;


// Class for the node of the AVL tree
class Node
{
public:
    int data;
    Node * left, * right;
    int height;
    Node(int data)
    {
        this -> data = data;
        this -> left = this -> right = NULL;
        this -> height = 1;
    }
};


// This function returns the height of the tree or subtree
int height(Node * root)
{
    if (!root) {
        return 0;
    }
    return root -> height;
}


// Left rotates about the passed root
Node * leftRotate(Node * root)
{
    if (!root)
    {
        return NULL;
    }
    Node * y = root -> right;
    Node * t2 = y -> left;
    
    // perform rotation
    y -> left = root;
    root -> right = t2;
    
    // update the heights of the nodes
    root -> height = max(height(root -> left), height(root -> right)) + 1;
    y -> height = max(height(y -> left), height(y -> right)) + 1;
    
    // return the new root
    return y;
}

// Right rotates about the passed node
Node * rightRotate(Node * root)
{
    if (!root)
    {
        return NULL;
    }
    Node * x = root -> left;
    Node * t2 = x -> right;
    
    // perform rotation
    x -> right = root;
    root -> left = t2;
    
    // update the height of the nodes
    root -> height = max(height(root -> left), height(root -> right)) + 1;
    x -> height = max(height(x -> left), height(x -> right)) + 1;
    
    // return the new root
    return x;
}


// This function returns the balance factor of the subtree or tree
int getBalance(Node * root)
{
    if (!root)
    {
        return 0;
    }
    return height(root -> left) - height(root -> right);
}

// INSERT IN A TREE AND MAINTAINING THE BALANCE OF THE TREE
Node * insert(Node * root, int data)
{
    // perform the normal insertion
    if (!root)
    {
        Node * newNode = new Node(data);
        return newNode;
    }
    if (data < root -> data)
    {
        root -> left = insert(root -> left, data);
    }
    else if(data > root -> data)
        root -> right = insert(root -> right, data);
    // two nodes of the same data are not allowed in this BST
    
    // update the height of the new root
    root -> height = max(height(root -> left), height(root -> right)) + 1;
    
    // get the balance of the root
    int balance = getBalance(root);
    
    // left left case
    if (balance > 1 && data < root -> left -> data)
    {
        return rightRotate(root);
    }
    
    // left right case
    if (balance > 1 && data > root -> left -> data)
    {
        root -> left = leftRotate(root -> left);
        return rightRotate(root);
    }
    
    // right right case
    if (balance < -1 && data > root -> right -> data)
    {
        return leftRotate(root);
    }
    
    // right left case
    if (balance < -1 && data < root -> right -> data)
    {
        root -> right = rightRotate(root -> right);
        return leftRotate(root);
    }
    
    // if the control in the function reaches here then the tree is balanced
    // hence return the root as it is
    return root;
    
}





// DELETE IN A BST WHILE MAINTAINING THE BALANCE OF THE TREE
Node * deleteNode(Node * root, int data)
{
    // Perform the normal deletion just like in a regular BST
    if (!root)
    {
        return NULL;
    }
    if (root -> data == data)
    {
        if (!root -> left && !root -> right)
        {
            delete root;
            return NULL;
        }
        else if(!root -> left)
        {
            Node * newRoot = root -> right;
            delete root;
            return newRoot;
        }
        else if(!root -> right)
        {
            Node * newRoot = root -> left;
            delete root;
            return newRoot;
        }
        else
        {
            Node * successor = root -> right;
            Node * parent = root;
            while (successor -> left)
            {
                parent = successor;
                successor = successor -> left;
            }
            parent -> left = successor -> right;
            
            successor -> left = root -> left;
            successor -> right = root -> right;
            root -> left = root -> right = NULL;
            delete root;
            return successor;
        }
    }
    else if(data >= root -> data)
        root -> right = deleteNode(root -> right, data);
    else root -> left = deleteNode(root -> left, data);
    
    // Update the height of the root
    root -> height = max(height(root -> left), height(root -> right)) + 1;
    
    // check if the root is balanced or not
    int balance = getBalance(root);
    // if the tree is not balanced only then one of the next 4 if blocks would get executed
    // Left left case
    if (balance > 1 && getBalance(root -> left) >= 0)
    {
        return rightRotate(root);
    }
    // Left right Case
    if (balance > 1 && getBalance(root -> left) < 0)
    {
        root -> left = leftRotate(root -> left);
        return rightRotate(root);
    }
    // Right right case
    if (balance < -1 && getBalance(root -> right) <= 0)
    {
        return leftRotate(root);
    }
    
    // Right left case
    if (balance < - 1 && getBalance(root -> right) > 0)
    {
        root -> right = rightRotate(root -> right);
        return leftRotate(root);
    }
    
    // The control will only reach here if this node was balanced
    return root;
    
}

void printTree(Node * root)
{
    cout << "TREE";
    queue<Node*> pendingNodes;
    pendingNodes.push(root);
    while (!pendingNodes.empty())
    {
        Node * front = pendingNodes.front();
        pendingNodes.pop();
        cout << endl << front -> data << " : ";
        if (front -> left)
        {
            cout << "L -> " << front -> left -> data << "   ";
            pendingNodes.push(front -> left);
        }
        if (front -> right)
        {
            cout << "R -> " << front -> right -> data;
            pendingNodes.push(front -> right);
        }
       
    }
    cout << endl;
    
}

void preorder(Node * root)
{
    if (!root)
    {
        return;
    }
    cout << root -> data << " ";
    preorder(root -> left);
    preorder(root -> right);
}


int main()
{
    Node * root = NULL;
    for (int i = 0; i < 7; i++)
    {
        root = insert(root, i + 1);
    }
    printTree(root);
    root = deleteNode(root, 4);
    cout << endl;
    printTree(root);
}









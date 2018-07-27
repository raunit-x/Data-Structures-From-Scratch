#include <iostream>

using namespace std;

// O(n^2) implementation of the Cartesian Tree (max-heap)
class BinaryTreeNode
{
public:
    int data;
    BinaryTreeNode * left;
    BinaryTreeNode * right;
    BinaryTreeNode(int data)
    {
        this -> data = data;
        this -> left = NULL;
        this -> right = NULL;
    }
};


int getMaxIndex(int arr[], int start, int end)
{
    int max = arr[start];
    int index = start;
    for (int i = start + 1; i <= end; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            index = i;
        }
    }
    return index;
}

// Building a max heap Cartesian binary tree
BinaryTreeNode * buildCartesianTree(int inorder[], int start, int end)
{
    if (start > end)
    {
        return NULL;
    }
    int i = getMaxIndex(inorder, start, end);
    BinaryTreeNode * root = new BinaryTreeNode(inorder[i]);
    if (start == end)
    {
        return root;
    }
    root -> left = buildCartesianTree(inorder, start, i - 1);
    root -> right = buildCartesianTree(inorder, i + 1, end);
    return root;
}

// Just to check if the formed cartesian tree is correct or not
void printInorder(BinaryTreeNode * root)
{
    if (!root) {
        return;
    }
    printInorder(root -> left);
    cout << root -> data << " ";
    printInorder(root -> right);
}

int main()
{
    int arr[] = {5, 10, 40, 30, 28};
    int size = (sizeof(arr))/ sizeof(int);
    BinaryTreeNode * root = buildCartesianTree(arr, 0, size - 1); // The printed tree should be the same as the input tree
    printInorder(root);
    cout << endl;
    return 0;
}


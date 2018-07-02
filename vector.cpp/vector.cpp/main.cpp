#include <iostream>

using namespace std;

template<typename T>
class TreeNode {
    TreeNode<T>** children;
    int childCount;
    
public:
    T data;
    
    TreeNode(T data);    // Constructor
    int numChildren();
    void addChild(TreeNode<T>* child);
    TreeNode<T>* getChild(int index);
    void setChild(int index, TreeNode<T>* child);
};
class Pair
{
public:
    TreeNode<int> * max = NULL;
    TreeNode<int> * secondMax = NULL;
};
TreeNode<int>* maxDataNode(TreeNode<int>* root)
{
    if(root == NULL)
        return NULL;
    TreeNode<int> * large = root;
    for(int i = 0; i < root -> numChildren(); i++)
    {
        if(maxDataNode(root -> getChild(i)) -> data > large -> data)
        {
            large = maxDataNode(root -> getChild(i));
        }
    }
    return large;
}

TreeNode <int>* secondLargest(TreeNode<int> *root)
{
    if(root == NULL)
        return NULL;
    Pair ans;
    ans.max = root;
    ans.secondMax = NULL;
    for (int i = 0 ; i < root -> numChildren(); i++)
    {
        Pair temp;
        temp.max = maxDataNode(root -> getChild(i));
        temp.secondMax = secondLargest(root -> getChild(i));
        if(temp.secondMax && ans.secondMax)
        {
            if(temp.max -> data > ans.max -> data)
            {
                TreeNode<int> * x = ans.max;
                ans.max = temp.max;
                if(x -> data > temp.secondMax -> data)
                {
                    ans.secondMax = x;
                }
            }
            else if(ans.secondMax -> data > temp.max -> data)
            {
                ans.secondMax = temp.max;
            }
        }
        else if(ans.secondMax == NULL && temp.secondMax != NULL)
        {
            if(temp.max -> data > ans.max -> data)
            {
                TreeNode<int> * x = ans.max;
                ans.max = temp.max;
                if(x -> data > temp.secondMax -> data)
                {
                    ans.secondMax = x;
                }
                else
                {
                    ans.secondMax = temp.secondMax;
                }
            }
            else
            {
                temp.secondMax = ans.max;
            }
        }
        else if(ans.secondMax != NULL && temp.secondMax == NULL)
        {
            if(temp.max -> data > ans.max -> data)
            {
                ans.max = temp.max;
            }
            else
            {
                ans.secondMax = temp.max;
            }
        }
        else if(ans.secondMax == NULL && temp.secondMax == NULL)
        {
            if(temp.max -> data > ans.max -> data)
            {
                ans.max = temp.max;
            }
            else
            {
                ans.secondMax = temp.max;
            }
        }
    }
    return ans.secondMax;
}


int main()
{
    return 0;
}

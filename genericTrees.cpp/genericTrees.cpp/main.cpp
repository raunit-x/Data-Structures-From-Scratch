#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class TreeNode
{
public:
    T data;
    vector<TreeNode *> children;
    //constructor
    TreeNode(T data)
    {
        this -> data = data;
    }
    // destructor
    ~TreeNode()
    {
        for (int i = 0 ; i < children.size(); i++)
        {
            delete children[i];
        }
    }
};


// Take input using recursion
TreeNode<int> * takeInput()
{
    int rootData;
    cout << "Enter data" << endl;
    cin >> rootData;
    TreeNode<int> * root = new TreeNode<int>(rootData);
    int n;
    cout << "Enter the number of children of " << root -> data << ":";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        TreeNode<int> * child = takeInput();
        root -> children.push_back(child);
    }
    return root;
}

//Print using recursion
void printTree(TreeNode<int> * root)
{
    // edge case
    if(!root)
    {
        return;
    }
    
    cout << root -> data << ": ";
    for (int i = 0; i < root -> children.size(); i++)
    {
        cout << root -> children[i] -> data << "  ";
    }
    cout << endl;
    
    
    for (int i = 0; i < root -> children.size(); i++)
    {
        printTree(root -> children[i]);
    }
}

// Take input level wise
TreeNode<int> * takeInputLevelWise()
{
    int rootData;
    cout << "Enter root data: ";
    cin >> rootData;
    TreeNode<int> * root = new TreeNode<int>(rootData);
    cout << endl;
    queue<TreeNode<int>*> pendingNodes;
    pendingNodes.push(root);
    while (!pendingNodes.empty())
    {
        TreeNode<int> * front = pendingNodes.front();
        pendingNodes.pop();
        cout << "Enter the number of children of " << front -> data << ": ";
        int numChild;
        cin >> numChild;
        for (int i = 0; i < numChild; i++)
        {
            cout << "Enter data of the " << i << "th child : ";
            int tempData;
            cin >> tempData;
            TreeNode<int> * child = new TreeNode<int>(tempData);
            front -> children.push_back(child);
            pendingNodes.push(child);
        }
    }
    return root;
}

// Print tree level wise
void printTreeLevelWise(TreeNode<int> * root)
{
    if(!root)
        return;
    queue<TreeNode<int> *> pendingNodes;
    pendingNodes.push(root);
    while(!pendingNodes.empty())
    {
        TreeNode<int> * front = pendingNodes.front();
        pendingNodes.pop();
        cout << front -> data << ": ";
        for (int i = 0; i < front -> children.size(); i++)
        {
            cout << front -> children[i] -> data << "  ";
            pendingNodes.push(front -> children[i]);
        }
        cout << endl;
    }
}

// Number of nodes
int countNodes(TreeNode<int> * root)
{
    int ans = 1;
    for (int i = 0; i < root -> children.size(); i++)
    {
        ans += countNodes(root -> children[i]);
    }
    return ans;
}

// Sum of all the nodes
int sumOfNodes(TreeNode<int> * root)
{
    int ans = root -> data;
    for (int i = 0; i < root -> children.size(); i++)
    {
        ans += sumOfNodes(root -> children[i]);
    }
    return ans;
}

// Height of the tree
int height(TreeNode<int>* root)
{
    int large = 0;
    if(root == NULL)
        return large;
    
    for(int i = 0; i < root -> children.size(); i++)
    {
        int temp = height(root -> children[i]);
        if(temp > large)
        {
            large = temp;
        }
    }
    return large + 1;
}

// Number of leaf nodes
int numLeafNodes(TreeNode<int> * root)
{
    if(root == NULL)
        return 0;
    int count = 0;
    if(root -> children.size() == 0)
        count++;
    for(int i = 0; i < root -> children.size(); i++)
    {
        count += numLeafNodes(root -> children[i]);
    }
    return count;
}

// Post-order traversal
void postOrder(TreeNode<int>* root)
{
    if(root == NULL)
        return;
    if(root -> children.size() == 0)
    {
        cout << root -> data << " ";
        return;
    }
    for(int i = 0; i < root -> children.size(); i++)
    {
        postOrder(root -> children[i]);
    }
    cout << root -> data << " ";
}

// Search
bool containsX(TreeNode<int>* root, int x)
{
    if(root == NULL)
        return false;
    if(root -> data == x)
        return true;
    for(int i = 0; i < root -> children.size(); i++)
    {
        bool a = containsX(root -> children[i], x);
        if(a)
        {
            return true;
        }
        else continue;
    }
    return false;
}

int nodesGreaterThanX(TreeNode<int> *root, int x)
{
    if(root == NULL)
        return 0;
    int ans = 0;
    if(root -> data > x)
        ans++;
    for(int i = 0; i < root -> children.size(); i++)
    {
        ans += nodesGreaterThanX(root -> children[i], x);
    }
    return ans;
}




//  dummy tree input: 1 3 2 3 4 2 5 6 0 0 0 0
int main()
{
    TreeNode<int> * root = takeInputLevelWise();
    cout << endl;
    printTreeLevelWise(root);
    cout << sumOfNodes(root) << endl;
}

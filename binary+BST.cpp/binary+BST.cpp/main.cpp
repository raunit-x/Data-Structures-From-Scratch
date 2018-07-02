#include<iostream>
#include "queue"
#include<vector>
#include<string>
using namespace std;

template <typename T>
class BinaryTreeNode
{
public:
    T data;
    BinaryTreeNode<T> * left;
    BinaryTreeNode<T> * right;
    BinaryTreeNode(T data)
    {
        this -> data = data;
        left = NULL;
        right = NULL;
    }
    ~BinaryTreeNode()
    {
        delete left;
        delete right;
    }
};

BinaryTreeNode<int> * takeInput()
{
    int rootData;
    cout << "Enter data: ";
    cin >> rootData;
    if(rootData != -1)
        return NULL;
    BinaryTreeNode<int> * root = new BinaryTreeNode<int>(rootData);
    BinaryTreeNode<int> * leftChild = takeInput();
    BinaryTreeNode<int> * rightChild = takeInput();
    root -> right = rightChild;
    root -> left = leftChild;
    return root;
}
BinaryTreeNode<int> * takeInputLevelWise()
{
    int rootData;
    cout << "Enter root data: ";
    cin >> rootData;
    if(rootData == -1)
        return NULL;
    BinaryTreeNode<int> * root = new BinaryTreeNode<int>(rootData);
    queue<BinaryTreeNode<int> *> PendingNodes;
    PendingNodes.push(root);
    while(!PendingNodes.empty())
    {
        BinaryTreeNode<int> * front = PendingNodes.front();
        PendingNodes.pop();
        int leftData, rightData;
        cout << "Enter Left data of " << front -> data << ": ";
        cin >> leftData;
        
        if(leftData != -1)
        {
            BinaryTreeNode<int> * node1 = new BinaryTreeNode<int>(leftData);
            front -> left = node1;
            PendingNodes.push(front -> left);
        }
        
        cout << "Enter right data of " << front -> data << ": ";
        cin >> rightData;
        
        if(rightData != -1)
        {
            BinaryTreeNode<int> * node2 = new BinaryTreeNode<int>(rightData);
            front -> right = node2;
            PendingNodes.push(front -> right);
        }

   }
    return root;
}

void PrintBinaryTree(BinaryTreeNode<int> * root)
{
    if(root == NULL)
        return;
    cout << root -> data << ": ";
    if(root -> left != NULL)
        cout << "L" << root -> left -> data;
    if(root -> right != NULL)
        cout << "\tR" << root -> right -> data;
    cout << endl;
    PrintBinaryTree(root -> left);
    PrintBinaryTree(root -> right);
}

BinaryTreeNode<int> * deleteleafNodes(BinaryTreeNode<int> * root)
{
    if (!root)
    {
        return NULL;
    }
    if (!root -> left && !root -> right)
    {
        delete root;
        return NULL;
    }
    
    
    root -> left = deleteleafNodes(root -> left);
    root -> right = deleteleafNodes(root -> right);
    return root;
}

void PrintTreeLevelWise(BinaryTreeNode<int> * root)
{
    if(root == NULL)
        return;
    queue<BinaryTreeNode<int> *> PendingNodes;
    PendingNodes.push(root);
    while (!PendingNodes.empty())
    {
        BinaryTreeNode<int> * front = PendingNodes.front();
        cout << front -> data << ": ";
        PendingNodes.pop();
        if(front -> left != NULL)
        {
            PendingNodes.push(front -> left);
            cout << "L" << front -> left -> data;
        }
        if(front -> right != NULL)
        {
            PendingNodes.push(front -> right);
            cout << "R" << front -> right -> data;
        }
        cout << endl;
    }
    
}
int countNodes(BinaryTreeNode<int> * root)
{
    if(root == NULL)
        return 0;
    return 1 + countNodes(root -> right) + countNodes(root -> left);
}
void inOrder(BinaryTreeNode<int> * root)
{
    if(root == NULL)
        return;
    inOrder(root -> left);
    cout << root -> data << " ";
    inOrder(root -> right);
}


BinaryTreeNode<int> * buildTreeHelper(int * preorder, int * inorder, int preE, int preS, int inE, int inS)
{
    if(inS >= inE)
        return NULL;
    int rootData = preorder[preS];
    int index = -1;
    for(int i = inS; i <= inE; i++)
    {
        if(rootData == inorder[i])
        {
            index = i;
            break;
        }
    }
    int linS = inS;
    int linE = index - 1;
    int lpreS = preS + 1;
    int lpreE = lpreS + linE - linS;
    
    int rpreS = lpreE + 1;
    int rpreE = preE;
    int rinS = index + 1;
    int rinE = inE;
    BinaryTreeNode<int> * root = new BinaryTreeNode<int>(rootData);
    root -> left = buildTreeHelper(preorder, inorder, lpreE, lpreS, linE, linS);
    root -> right = buildTreeHelper(preorder, inorder, rpreE, rpreS, rinE, rinS);
    return root;
}

BinaryTreeNode<int>* buildTree(int *preorder, int preLenght, int *inorder, int inLength)
{
    int size = inLength;
    return buildTreeHelper(preorder,inorder, size - 1, 0, size - 1, 0);
}

int sumOfNodes(BinaryTreeNode<int> * root)
{
    if(root == NULL)
        return 0;
    return sumOfNodes(root -> left) + sumOfNodes(root -> right) + root -> data;
}

class Pair
{
public:
    int height;
    int diam;
    Pair()
    {
        height = 0;
        diam = 0;
    }
    
};
Pair diameter(BinaryTreeNode<int> * root)
{
    if(root == NULL)
    {
        Pair ans;
        return ans;
    }
    Pair rightAns, leftAns;
    rightAns= diameter(root -> right);
    leftAns = diameter(root -> left);
    
    
    Pair ans;
    ans.height = 1 + max(rightAns.height, leftAns.height);
    ans.diam = max(rightAns.height + leftAns.height, max(rightAns.diam, leftAns.diam));
    return ans;
}

BinaryTreeNode<int> * buildTreeHelper2(int * postorder, int * inorder, int postS, int postE, int inS, int inE)
{
    if(inS > inE)
        return NULL;
    int rootData = postorder[postE];
    BinaryTreeNode<int> * root = new BinaryTreeNode<int>(rootData);
    int index = -1;
    for(int i = inS; i <= inE; i++)
    {
        if(rootData == inorder[i])
        {
            index = i;
            break;
        }
    }
    int LinS = inS;
    int LinE = index - 1;
    int LpostS = postS;
    int LpostE = LpostS + LinE - LinS;
    
    int RinS = index + 1;
    int RinE = inE;
    int RpostS = LpostE + 1;
    int RpostE = RpostS + RinE - RinS;
    
    root -> left = buildTreeHelper2(postorder, inorder, LpostS, LpostE, LinS, LinE);
    root -> right = buildTreeHelper2(postorder, inorder, RpostS, RpostE, RinS, RinE);
    return root;

}

BinaryTreeNode<int>* getTreeFromPostorderAndInorder(int *postorder, int postLength, int *inorder, int inLength)
{
    int size = postLength;
    return buildTreeHelper2(postorder, inorder, 0, size - 1, 0 , size - 1);

}

int height(BinaryTreeNode<int> *root)
{
    if(root == NULL)
        return 0;
    int left = height(root -> left);
    int right = height(root -> right);
    if(left > right)
        return left + 1;
    else return right + 1;
}

bool isBalanced(BinaryTreeNode<int> *root)
{
    if(root == NULL)
        return true;
    
    int Ldepth = height(root -> left);
    int Rdepth = height(root -> right);
    
    if(Ldepth - Rdepth == 1 || Rdepth == Ldepth || Ldepth - Rdepth == 1)
    {
        return true;
    }
    
    return false;
}
template<typename T>
class node{
public:
    T data;
    node<T> * next;
    node(T data){
        this->data=data;
        this->next=NULL;
    }
};

vector<node<int>*> createLLForEachLevel(BinaryTreeNode<int> *root)
{
    vector<node<int>* > output;
    queue<BinaryTreeNode<int>* > pendingNodes;
    pendingNodes.push(root);
    pendingNodes.push(NULL);
    node<int> * head = NULL;
    node<int> * tail = NULL;
    while(!pendingNodes.empty())
    {
        BinaryTreeNode<int> * front = pendingNodes.front();
        if(front)
        {
            node<int> * newNode = new node<int>(front -> data);
            pendingNodes.pop();
            if(head == NULL)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail -> next = newNode;
                tail = newNode;
            }
            
            if(front -> left)
                pendingNodes.push(front -> left);
            if(front -> right)
                pendingNodes.push(front -> right);
            if(pendingNodes.empty())
                break;
        }
        else
        {
            pendingNodes.pop();
            output.push_back(head);
            head = NULL;
            tail = NULL;
            if(pendingNodes.empty())
                break;
            pendingNodes.push(NULL);
        }
    }
    return output;
}
// BINARYSEARCHTREES ---> BST

int minimum(BinaryTreeNode<int>* root)
{
    if(root == NULL)
        return INT_MAX;
    return min(root -> data, min(minimum(root -> left), minimum(root -> right)));
}

int maximum(BinaryTreeNode<int>* root)
{
    if(root == NULL)
        return INT_MIN;
    return max(root -> data, max(maximum(root -> left), maximum(root -> right)));
}

bool isBST(BinaryTreeNode<int>* root)
{
    if(root == NULL)
    {
        return true;
    }
    
    int leftMax = maximum(root -> left);
    int rightMin = minimum(root -> right);
    
    bool output = (root -> data > leftMax) && (root -> data <= rightMin) && (isBST(root -> left)) && (isBST(root -> right));
    
    return output;
}


class isBSTReturn
{
public:
    bool isBST;
    int max;
    int min;
};

isBSTReturn isBST2(BinaryTreeNode<int>* root)
{
    if(root == NULL)
    {
        isBSTReturn output;
        output.isBST = true;
        output.max = INT_MIN;
        output.min = INT_MAX;
        return output;
    }
    
    isBSTReturn leftOutput = isBST2(root -> left);
    isBSTReturn rightOutput = isBST2(root -> right);
    int minimum = min(root -> data, min(leftOutput.min, rightOutput.min));
    int maximum = max(root -> data, max(leftOutput.max, rightOutput.max));
    isBSTReturn output;
    output.max = maximum;
    output.min = minimum;
    output.isBST = (root -> data > leftOutput.max) && (root -> data <= rightOutput.min) && leftOutput.isBST && rightOutput.isBST;
    return output;
}

bool isBST3(BinaryTreeNode<int>* root, int min = INT_MIN, int max = INT_MAX)
{
    if(root == NULL)
    {
        return true;
    }
    if(root -> data < min || root -> data > max)
        return false;
    bool leftResult = isBST3(root -> left, min, root -> data - 1);
    bool rightResult = isBST3(root -> right, root -> data, max);
    return leftResult && rightResult;
}


template <typename T>
class NodeLL
{
public:
    T data;
    NodeLL<T> *next;
    NodeLL(T data){
        this -> data = data;
        this -> next = NULL;
    }
};

NodeLL<int>* constructBST(BinaryTreeNode<int>* root)
{
    if(root == NULL)
        return NULL;
    NodeLL<int>* lHead = constructBST(root -> left);
    NodeLL<int>* temp = lHead;
    NodeLL<int>* newNode = new NodeLL<int>(root -> data);
    NodeLL<int>* rHead = constructBST(root -> right);
    while(temp -> next != NULL)
    {
        temp = temp -> next;
    }
    temp -> next = newNode;
    newNode -> next = rHead;
    return lHead;
}

class HeadTail
{
public:
    NodeLL<int>* head;
    NodeLL<int>* tail;
    HeadTail()
    {
        head = NULL;
        tail = NULL;
    }
};

HeadTail  constructBST2(BinaryTreeNode<int>* root)
{
    if(root == NULL)
    {
        HeadTail ans;
        return ans;
    }
    
    HeadTail leftTree = constructBST2(root -> left);
    NodeLL<int>* newNode = new NodeLL<int>(root -> data);
    HeadTail rightTree = constructBST2(root -> right);
    if(leftTree.tail)
    leftTree.tail -> next = newNode;
    else
    {
        leftTree.head = newNode;
    }
    newNode -> next = rightTree.head;
    return leftTree;
}

vector<int>* findPath(BinaryTreeNode<int> *root , int data)
{
    if(root == NULL)
        return NULL;
    if (root -> data == data)
    {
        vector<int>* output = new vector<int>();
        output -> push_back(root -> data);
        return output;
    }
    else if(root -> data > data)
    {
        vector<int>* leftOutput = findPath(root -> left, data);
        if(leftOutput)
        leftOutput -> push_back(root -> data);
        return leftOutput;
    }
    else
    {
        vector<int>* rightOutput = findPath(root -> right, data);
        if(rightOutput)
        rightOutput -> push_back(root -> data);
        return rightOutput;
    }
    
}
class BST
{
public:
    
    BinaryTreeNode<int>* root;
    BST()
    {
        root = NULL;
    }
    ~BST()
    {
        delete root;
    }
private:
    
    bool hasDataHelper(BinaryTreeNode<int>* root, int data)
    {
        if(root == NULL)
            return false;
        if(root -> data == data)
        {
            return true;
        }
        else if(root -> data > data)
        {
            return hasDataHelper(root -> left, data);
        }
        else
        {
            return hasDataHelper(root -> right, data);
        }
    }
    
    BinaryTreeNode<int>* insertHelper(int data, BinaryTreeNode<int>* Node)
    {
        if(Node == NULL)
        {
            BinaryTreeNode<int>* newNode = new BinaryTreeNode<int>(data);
            this -> root = newNode;
            return newNode;
        }
        if(Node -> data > data)
        {
            BinaryTreeNode<int>* leftRoot = insertHelper(data, Node -> left);
            Node -> left = leftRoot;
            this -> root = Node;
            return Node;
            
        }
        else
        {
            BinaryTreeNode<int>* rightRoot = insertHelper(data, Node -> right);
            Node -> right = rightRoot;
            this -> root = Node;
            return Node;
        }
    }
    
    BinaryTreeNode<int>* deleteDataHelper(BinaryTreeNode<int>* Node, int data)
    {
        if(Node == NULL)
            return NULL;
        
        if(Node -> data > data)
        {
            Node -> left = deleteDataHelper(Node -> left, data);
            return Node;
        }
        else if(Node -> data < data)
        {
            Node -> right = deleteDataHelper(Node -> right, data);
            return Node;
        }
        else
        {
            if(Node -> left == NULL && Node -> right == NULL)
            {
                delete Node;
                return NULL;
            }
            else if(Node -> left && Node -> right == NULL)
            {
                BinaryTreeNode<int>* newRoot = Node -> left;
                Node -> left = NULL;
                delete Node;
                return newRoot;
            }
            else if(Node -> right && Node -> left == NULL)
            {
                BinaryTreeNode<int>* newRoot = Node -> right;
                Node -> right = NULL;
                delete Node;
                return newRoot;
            }
            else
            {
                BinaryTreeNode<int>* minRight = Node -> right;
                while(minRight -> left != NULL)
                {
                    minRight = minRight -> left;
                }
                int min = minRight -> data;
                BinaryTreeNode<int>* newRoot = deleteDataHelper(Node -> right, min);
                Node -> data = min;
                Node -> right = newRoot;
                return Node;
            }
        }
    }
    
    void PrintTreeHelper(BinaryTreeNode<int> * root)
    {
        if(root == NULL)
            return;
        cout << root -> data << ":";
        if(root -> left != NULL)
            cout << "L:" << root -> left -> data;
        if(root -> right != NULL)
        {
            if(root -> left)
                cout << ",";
            cout << "R:" << root -> right -> data;
        }
        cout << endl;
        PrintTreeHelper(root -> left);
        PrintTreeHelper(root -> right);
    }
public:
    void printTree()
    {
        PrintTreeHelper(this -> root);
    }
    void insert(int data)
    {
        this -> root = insertHelper(data, this -> root);
    }
    bool  hasData(int data)
    {
        return hasDataHelper(this -> root, data);
    }
    void deleteData(int data)
    {
        this -> root = deleteDataHelper(this -> root, data);
    }
    

};
class Pair2
{
public:
    bool ans;
    int number;
    BinaryTreeNode<int>* root;
    vector<int>* arr = new vector<int>();
    
    bool Lsearch(vector<int>* arr, int data)
    {
        for(int i = 0; i < arr -> size(); i++)
        {
            if(arr -> at(i) == data)
                return true;
        }
        return false;
    }
    
    bool hasDataHelper(BinaryTreeNode<int>* node, int data)
    {
        if(node == NULL)
            return false;
        if(node -> data == data)
        {
            return true;
        }
        else
        {
            if(hasDataHelper(node -> left, data))
                return true;
            else if(hasDataHelper(node -> right,data))
                return true;
            else return false;
        }
        
    }
    
    void nodesSumToSHelper(BinaryTreeNode<int> *node, int sum)
    {
        
        if(node == NULL)
            return;
        
        if(hasDataHelper(this -> root, sum - node -> data))
        {
            if(!Lsearch(arr, sum - node -> data))
            {
                cout << node -> data << " " << sum - node -> data << endl;
                arr -> push_back(node -> data);
                arr -> push_back(sum - node -> data);
            }
        }
        nodesSumToSHelper(node -> left, sum);
        nodesSumToSHelper(node -> right, sum);
    }
    
};
void nodesSumToS(BinaryTreeNode<int> *root, int sum)
{
    Pair2  ans;
    ans.root = root;
    ans.nodesSumToSHelper(root, sum);
}


void rootToLeafPathsSumToK(BinaryTreeNode<int> *root, int k)
{
    if(root == NULL)
        return;
    if(root -> left == NULL && root -> right == NULL)
    {
        if(root -> data == k)
            cout << root -> data << " ";
        else return;
    }
    else
    {
        cout << root -> data << " ";
        rootToLeafPathsSumToK(root -> left, k - root -> data);
    }
}
void rootToLeafPathsSumToK(BinaryTreeNode<int>* root, int k, string output)
{
    if(root == NULL)
        return;
    if(root -> left == NULL || root -> right == NULL)
    {
        output += root -> data;
        if(root -> data == k)
        {
            cout << output << endl;
            return;
        }
        else
        {
            output = "";
            return;
        }
    }
    else
    {
        output += root -> data;
        rootToLeafPathsSumToK(root -> left, k - root -> data, output);
        rootToLeafPathsSumToK(root -> right, k - root -> data, output);
        
    }
}

void rootToLeafPathsSumToX(BinaryTreeNode<int>* root, int x, string output)
{
    if(root == NULL)
        return;
    if(root -> left == NULL && root -> right == NULL)
    {
        if(root -> data == x)
        {
            string smallOutput = "";
            int k = root -> data;
            while(k != 0)
            {
                char ch = char(k%10) + '0';
                smallOutput = ch + smallOutput;
                k = k/10;
            }
            output = output + smallOutput + " ";
            cout << output << endl;
        }
    }
    else
    {
        string smallOutput = "";
        int k = root -> data;
        while(k != 0)
        {
            char ch = char(k%10) + '0';
            smallOutput = ch + smallOutput;
            k = k/10;
        }
        output = output + smallOutput + " ";
        rootToLeafPathsSumToX(root -> left, x - root -> data, output);
        rootToLeafPathsSumToX(root -> right, x - root -> data, output);
    }
    
}



int main()
{
    BinaryTreeNode<int> * root = takeInputLevelWise();
    PrintTreeLevelWise(root);
    deleteleafNodes(root);
    PrintTreeLevelWise(root);
}
// 1 4 1 2 1 1 1 3 1 6 1 5 1 7

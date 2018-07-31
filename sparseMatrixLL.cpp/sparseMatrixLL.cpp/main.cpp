#include <iostream>

using namespace std;

class Node
{
public:
    int row;
    int column;
    int value;
    Node * next;
    Node(int row, int column, int value)
    {
        this -> row = row;
        this -> column = column;
        this -> value = value;
        this -> next = NULL;
    }
};

void printLL(Node * head)
{
    if(head == NULL)
    {
        cout << "Empty";
        return;
    }
    Node * temp = head;
    cout << "Rows    : ";
    while (temp != NULL)
    {
        cout << temp -> row << " ";
        temp = temp -> next;
    }
    cout << "\nColumns : ";
    temp = head;
    while (temp != NULL)
    {
        cout << temp -> column << " ";
        temp = temp -> next;
    }
    cout << "\nValues  : ";
    temp = head;
    while (temp != NULL)
    {
        cout << temp -> value << " ";
        temp = temp -> next;
    }
}

int main()
{
    // Assume 4x5 sparse matrix
    int sparseMatrix[4][5] =
    {
        {0 , 0 , 3 , 0 , 4 },
        {0 , 0 , 5 , 7 , 0 },
        {0 , 0 , 0 , 0 , 0 },
        {0 , 2 , 6 , 0 , 0 }
    };
    bool flag = true;
    Node * head = NULL; // initalize the head of the LL
    Node * tail = NULL; // initialize the tail of the LL
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(sparseMatrix[i][j] != 0)
            {
                if(flag) // this block would be executed only once
                {
                    Node * temp = new Node(i, j , sparseMatrix[i][j]);
                    head = temp; // form the head
                    tail = temp; // update the tail
                    flag = false; // so that this block is executed only once
                    continue;
                }
                Node * newNode = new Node(i, j, sparseMatrix[i][j]);
                tail -> next = newNode; // append the node to the LL
                tail = newNode; // update the tail
            }
        }
    }
    printLL(head);
    cout << endl;
    
    
}

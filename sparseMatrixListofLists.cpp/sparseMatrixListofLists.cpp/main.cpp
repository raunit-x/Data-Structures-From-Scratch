#include <iostream>
#define R 4
#define C 5
using namespace std;

class Node
{
public:
    int column;
    int value;
    Node * next;
    Node(int column, int value)
    {
        this -> column = column;
        this -> value = value;
        this -> next = NULL;
    }
};

class List
{
public:
    int row;
    Node * right;
    List * down;
    List(int row)
    {
        this -> row = row;
        this -> right = NULL;
        this -> down = NULL;
    }
};




List * createList(int Sparse_Matrix[R][C])
{
    List * head = NULL;
    List * tail = NULL;
    bool flag = true;
    for(int i = 0; i < R; i++)
    {
        if (flag)
        {
            List * temp = new List(i);
            head = temp;
            tail = temp;
            flag = false;
            continue;
        }
        List * newNode = new List(i);
        tail -> down = newNode;
        tail = newNode;
    }
    return head;
}

void createNodes(int Sparse_Matrix[R][C], List * start)
{
    List * temp = start;
    int row = 0;
    while (temp)
    {
        bool flag = true;
        Node * head = NULL;
        Node * tail = NULL;
        for (int j = 0; j < C; j++)
        {
            if (Sparse_Matrix[row][j] != 0)
            {
                if (flag)
                {
                    Node * newNode = new Node(j, Sparse_Matrix[row][j]);
                    head = newNode;
                    tail = newNode;
                    flag = false;
                    continue;
                }
                Node * newNode = new Node(j, Sparse_Matrix[row][j]);
                tail -> next = newNode;
                tail = newNode;
            }
        }
        temp -> right = head;
        temp = temp -> down;
        row++;
    }
}

void printList(List * start)
{
    if (!start) {
        cout << "Empty";
        return;
    }
    List * temp = start;
    int i = 0;
    while (temp)
    {
        cout << i +  1 << ") Row: " << temp -> row << endl;
        Node * row = temp -> right;
        if (!row)
        {
            cout << "   NULL" << endl;
        }
        else
        {
            cout << "   Columns :";
            while (row)
            {
                cout << row -> column << " ";
                row = row -> next;
            }
            cout << "\n   Values :";
            row = temp -> right;
            while (row)
            {
                cout << row -> value << " ";
                row = row -> next;
            }
            cout << endl;
        }
        temp = temp -> down;
        i++;
    }
    
}

int main()
{
    // Assume 4x5 sparse matrix
    int Sparse_Matrix[R][C] =
    {
        {0 , 0 , 3 , 0 , 4 },
        {0 , 0 , 5 , 7 , 0 },
        {0 , 0 , 0 , 0 , 0 },
        {0 , 2 , 6 , 0 , 0 }
    };
    List * start = createList(Sparse_Matrix);
    createNodes(Sparse_Matrix, start);
    printList(start);
    cout << endl;
}

#include <iostream>

using namespace std;

class Node{
public:
    int data;
    Node *next;
    Node(int data){
        this -> data = data;
        this -> next = NULL;
    }
};


int sizeOfLL(Node * head)
{
    if (head == NULL)
    {
        return 0;
    }
    else return sizeOfLL(head -> next) + 1;
}
class Deque
{
    Node * front;
    Node * rear;
    int capacity;
    int size;
    
public:
    Deque()
    {
        front = NULL;
        rear = NULL;
    }
    Deque(int x)
    {
        front = NULL;
        rear = NULL;
        capacity = 10;
        size = 0;
    }
    void insertFront(int data)
    {
        if (size >= capacity)
        {
            cout << -1 << endl;
            return;
        }
        if (front == NULL)
        {
            Node * newNode = new Node(data);
            this -> front = newNode;
            this -> rear = newNode;
            this -> rear -> next = NULL;
            size++;
            return;
        }
        else
        {
            Node * newNode = new Node(data);
            newNode -> next = this -> front;
            this -> front = newNode;
            size++;
            return;
        }
    }
    
    void insertRear(int data)
    {
        if (size >= capacity)
        {
            cout << -1 << endl;
            return;
        }
        if (front == NULL)
        {
            Node * newNode = new Node(data);
            this -> front = newNode;
            this -> rear = newNode;
            this -> rear -> next = NULL;
            size++;
            return;
        }
        else
        {
            Node * newNode = new Node(data);
            this -> rear -> next = newNode;
            this -> rear = newNode;
            this -> rear -> next = NULL;
            size++;
            return;
        }
    }
    
    void deleteFront()
    {
        if (this -> size == 0 || this -> front == NULL)
        {
            cout << -1 << endl;
            return;
        }
        
        Node * temp = this -> front;
        this -> front = this -> front -> next;
        size--;
        temp -> next = NULL;
        delete temp;
        return;
    }
    
    void deleteRear()
    {
        if (this -> size == 0 || this -> front == NULL)
        {
            cout << -1 << endl;
            return;
        }
        Node * temp = this -> front;
        
        for (int i = 0; i < size - 2; i++)
        {
            temp = temp -> next;
        }
        Node * last = this -> rear;
        temp -> next = NULL;
        this -> rear = temp;
        size--;
        delete last;
        return;
    }
    
    int getFront()
    {
        if (!this -> front)
        {
            return -1;
        }
        else return this -> front -> data;
    }
    
    int getRear()
    {
        if (!this -> front)
        {
            return -1;
        }
        else return this -> rear -> data;
    }
    
};

int main()
{
    Deque dq(10);
    int choice,input;
    while(true) {
        cin >> choice;
        switch (choice) {
            case 1:
                cin >> input;
                dq.insertFront(input);
                break;
            case 2:
                cin >> input;
                dq.insertRear(input);
                break;
            case 3:
                dq.deleteFront();
                break;
            case 4:
                dq.deleteRear();
                break;
            case 5:
                cout << dq.getFront() << "\n";
                break;
            case 6:
                cout << dq.getRear() << "\n";
                break;
            default:
                return 0;
        }
    }
    
    return 0;
}


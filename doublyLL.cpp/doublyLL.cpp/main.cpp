#include <iostream>

using namespace std;

// doubly linked list node
class Node
{
public:
    int data;
    Node * next;
    Node * prev;
    Node(int data)
    {
        this -> data = data;
        this -> next = this -> prev = this;
    }
};

// insert at the end of the list
Node * insertAtEnd(Node * head, int data)
{
    if (head == NULL)
    {
        Node * newNode = new Node(data);
        head = newNode;
        return head;
    }
    // List is not empty
    Node * newNode = new Node(data);
    Node * tail = head -> prev;
    tail -> next = newNode;
    newNode -> next = head;
    newNode -> prev = tail;
    head -> prev = newNode;
    return head;
}
// insert at the beg of the list
Node * insertAtBeg(Node * head, int data)
{
    if (head == NULL)
    {
        Node * newNode = new Node(data);
        head = newNode;
        return head;
    }
    
    // List is not empty
    
    Node * tail = head -> prev;
    Node * oldHead = head;
    Node * newHead = new Node(data);
    
    // form the new links
    newHead -> next = oldHead;
    newHead -> prev = tail;
    tail -> next = newHead;
    oldHead -> prev = newHead;
    
    // update the head
    head = newHead;
    
    return head;
}

// insert a new node with data1 after the node with data as data2
Node * insertAfter(Node * head, int data1, int data2)
{
    Node * newNode = new Node(data1);
    Node * temp = head;
    while (temp -> data != data2)
    {
        temp = temp -> next;
    }
    Node * nextNode = temp -> next;
    // insert newNode between temp and next
    temp -> next = newNode;
    newNode -> next = nextNode;
    nextNode -> prev = newNode;
    newNode -> prev = temp;
    return head;
}

// deletion
Node * deleteNode(Node * head, int data)
{
    if (!head)
    {
        cout << "Empty list" << endl;
        return NULL;
    }
    Node * temp = head;
    bool flag = false;
    while (temp -> next != head)
    {
        if (temp -> data == data)
        {
            flag = true;
            break;
        }
        temp = temp -> next;
    }
    if (!flag)
    {
        cout << "Element not found!" << endl;
        return head;
    }
    Node * prevNode = temp -> prev;
    Node * nextNode = temp -> next;
    prevNode -> next = nextNode;
    nextNode -> prev = prevNode;
    if(temp == head)
        return nextNode;
    return head;
}

// swap any two nodes
Node * swapTwoNodes(Node * start, int data1, int data2)
{
    Node * temp1 = start;
    Node * temp2 = start;
    while (temp1 -> next != start)
    {
        if (temp1 -> data == data1)
        {
            break;
        }
        temp1 = temp1 -> next;
    }
    while (temp2 -> next != start)
    {
        if (temp2 -> data == data2)
        {
            break;
        }
        temp2 = temp2 -> next;
    }
    if(temp1 -> next == temp2)
    {
        Node * prev = temp1 -> prev;
        Node * next = temp2 -> next;
        prev -> next = temp2;
        temp2 -> prev = prev;
        temp2 -> next = temp1;
        temp1 -> prev = temp2;
        temp1 -> next = next;
        next -> prev = temp1;
        if (start -> data == data1)
        {
            return temp2;
        }
    }
    if(temp2 -> next == temp1)
    {
        Node * prev = temp2 -> prev;
        Node * next = temp1 -> next;
        prev -> next = temp1;
        temp1 -> prev = prev;
        temp1 -> next = temp2;
        temp2 -> prev = temp1;
        temp1 -> next = next;
        next -> prev = temp2;
        if (start -> data == data2)
        {
            return temp1;
        }
    }
    
    Node * prev1 = temp1 -> prev;
    Node * prev2 = temp2 -> prev;
    Node * next1 = temp1 -> next;
    Node * next2 = temp2 -> next;
    prev1 -> next = temp2;
    temp2 -> prev = prev1;
    temp2 -> next = next1;
    next1 -> prev = temp2;
    temp1 -> next = next2;
    prev2 -> next = temp1;
    temp1 -> prev = prev2;
    next2 -> prev = temp1;
   
    if (start -> data == data2)
    {
        return temp1;
    }
    else if(start -> data == data1)
    {
        return temp2;
    }
    return start;
}




// print the LL in both ways: Head to tail and Tail to head
void printLL(Node * head)
{
    if (head == NULL)
    {
        return;
    }
    cout << "Head to Tail: ";
    Node * tail = head -> prev;
    Node * temp = head;
    while (temp -> next != head)
    {
        cout << temp -> data << " <=> ";
        temp = temp -> next;
    }
    cout << temp -> data << endl;
    temp = tail;
    cout << "Tail to head: ";
    while (temp -> prev != tail)
    {
        cout << temp -> data << " <=> ";
        temp = temp -> prev;
    }
    cout << temp -> data << endl;
}



int main()
{
    Node * head = NULL;
    for (int i = 0; i < 10; i++)
    {
        head = insertAtEnd(head, i + 1);
    }
    printLL(head); // 1 2 3 4 5 6 7 8 9 10
    head = insertAtBeg(head, 1001);
    printLL(head); // 1001 1 2 3 4 5 6 7 8 9 10
    head = insertAfter(head, 500, 6);
    printLL(head); // 1001 1 2 3 4 5 6 500 7 8 9 10
    head = deleteNode(head, 1001);
    printLL(head); // 1 2 3 4 5 6 500 7 8 9 10
    head = swapTwoNodes(head, 1, 2);
    printLL(head); // 6 2 3 4 5 1 500 7 8 9 10
    cout << endl;
}

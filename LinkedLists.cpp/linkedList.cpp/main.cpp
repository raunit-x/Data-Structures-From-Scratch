#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node * next;
    Node(T data)
    {
        this -> data = data;
        this -> next = NULL;
    }
};

// Length of the node recursively
int length(Node<int> * head)
{
    if (head == NULL)
    {
        return 0;
    }
    return length(head -> next) + 1;
}

// Print ith node iteratively
void printIthNode(Node<int> *head, int i)
{
    int count = 0;
    Node<int> * temp = head;
    int len = length(head);
    if(i > len)
        return;
    while(count != i && temp -> next != NULL)
    {
        count++;
        temp = temp -> next;
    }
    cout << temp -> data << endl;
}

// Delete a node iteratively
Node<int> * deleteNode(Node<int> *head, int i)
{
    Node<int> *temp = head;
    int count = 0;
    int len = length(head);
    if(i >= len)
    {
        return head;
    }
    
    while(count < i - 1)
    {
        temp = temp -> next;
        count++;
    }
    Node<int> *nextNode = temp -> next;
    Node<int> *newNext = nextNode -> next;
    delete nextNode;
    temp -> next = newNext;
    return head;
}

// Insert a node recursively at the given index
Node<int>* insertNodeRec(Node<int> *head, int i, int data)
{
    if(i == 0)
    {
        Node<int> *newNode = new Node<int>(data);
        newNode -> next = head;
        head = newNode;
        return head;
    }
    
    if(head == NULL)
    {
        return head;
    }
    
    Node<int> * temp = head;
    
    Node<int> * newHead = insertNodeRec(temp -> next, i - 1, data);
    head -> next = newHead;
    return head;
}

// Delete a node at a particular index
Node<int>* deleteNodeRec(Node<int> *head, int i)
{
    if(head == NULL)
        return head;
    if(i == 0)
    {
        Node<int> * temp = head;
        head = head -> next;
        delete temp;
        return head;
    }
    Node<int> * temp = head;
    
    Node<int> *newHead = deleteNodeRec(temp -> next, i -1);
    head -> next = newHead;
    return head;
}
// Index of N iterations
int indexOfNIter(Node<int> *head, int n)
{
    int len = length(head);
    int count = 0;
    Node<int> * temp = head;
    while(temp != NULL)
    {
        if(temp -> data == n)
        {
            return count;
        }
        temp = temp -> next;
        count ++;
    }
    if(count == len)
        return -1;
    return count;
}
// Append the first n elements to the last
Node<int>* append_LinkedList(Node<int>* head,int n)
{
    Node<int> * temp = head;
    int count = 0;
    int len = length(head);
    int index = len - n;
    if(index <= 0)
    {
        return head;
    }
    while(count < index - 1)
    {
        temp = temp -> next;
        count++;
    }
    Node<int> * newHead = temp -> next;
    Node<int> * tail = head;
    while(tail -> next != NULL)
    {
        tail = tail -> next;
    }
    tail -> next = head;
    temp -> next = NULL;
    
    return newHead;
}

// Print the LL recursively
void print_linkedlist_spl(Node<int>*head)
{
    if(head == NULL)
    {
        return;
    }
    print_linkedlist_spl(head -> next);
    cout << head -> data << " ";
}
// Mid point of the LL
Node<int>* midpoint_linkedlist(Node<int> *head)
{
    Node<int> * temp = head;
    int len = length(head);
    int mid = len/2;
    if(len % 2 == 0)
    {
        for(int i = 0; i < mid - 1; i++)
        {
            temp = temp -> next;
        }
        return temp;
    }
    else
    {
        for(int i = 0; i < mid; i++)
        {
            temp = temp -> next;
        }
        return temp;
    }
}
Node<int>* mergeTwoLLs(Node<int> *head1, Node<int> *head2)
{
    Node<int> * newHead = NULL;
    if(head1 -> data >= head2 -> data)
    {
        newHead = head2;
        head2 = head2 -> next;
    }
    else
    {
        newHead = head1;
        head1 = head1 -> next;
    }
    Node<int> * temp3 = newHead;
    
    while(head1 != NULL && head2 != NULL)
    {
        if(head1 -> data >= head2 -> data)
        {
            temp3 -> next = head2;
            head2 = head2 -> next;
        }
        else
        {
            temp3 -> next = head1;
            head1 = head1 -> next;
        }
        temp3 = temp3 -> next;
    }
    while(head2 != NULL)
    {
        temp3 -> next = head2;
        head2 = head2 -> next;
        temp3 = temp3 -> next;
    }
    while(head1 != NULL)
    {
        temp3 -> next = head1;
        head1 = head1 -> next;
        temp3 = temp3 -> next;
    }
    
    return newHead;
}


// Merge Sort
Node<int>* mergeSort(Node<int> *head)
{
    Node<int> * temp = head;
    if(head -> next == NULL)
        return head;
    int len = length(head);
    int mid = len/2;
    for(int i = 0; i < mid - 1; i++)
    {
        temp = temp -> next;
    }
    
    Node<int> * temp1 = temp;
    temp = temp -> next;  // second half formed
    temp1 -> next = NULL; // first half formed
    
    Node<int> * head1 = mergeSort(head); //first half call
    Node<int> * head2 = mergeSort(temp); //second half call
    Node<int> * newHead = mergeTwoLLs(head1, head2);
    return newHead;
}

class Pair
{
public:
    Node<int> * head;
    Node<int> * tail;
};

Pair reverseLL_2(Node<int> * head)
{
    if(head == NULL || head -> next == NULL)
    {
        Pair ans;
        ans.head = head;
        ans.tail = head;
        return ans;
    }
    
    Pair smallAns = reverseLL_2(head -> next);
    
    smallAns.tail -> next = head;
    head -> next = NULL;
    Pair ans;
    ans.head = smallAns.head;
    ans.tail = head;
    return ans;
}
// Reverse a LL recursively
Node<int> *reverse_linked_list_rec(Node<int> *head)
{
    return  reverseLL_2(head).head;
}

// Reverse a LL iteratively
Node<int> * rev_linkedlist_itr(Node<int>* head)
{
    Node<int> * current = head;
    Node<int> * prev = NULL;
    Node<int> * temp;
    while(current != NULL)
    {
        temp = current -> next;
        current -> next = prev;
        prev = current;
        current = temp;
    }
    head = prev;
    return head;
}

int sizeOfLL(Node<int> * head)
{
    if (head == NULL)
    {
        return 0;
    }
    else return sizeOfLL(head -> next) + 1;
}

//Next number question 999 -> 1000
Node<int>* NextLargeNumber(Node<int> *head)
{
    Node<int> * temp = head;
    while (temp -> next)
    {
        temp = temp -> next;
    }
    if (temp -> data != 9)
    {
        temp -> data++;
        return head;
    }
    else
    {
        temp -> data = 0;
        temp = head;
        int size = sizeOfLL(head);
        size--;
        while (size != 1)
        {
            for (int i = 0; i < size - 1; i++)
            {
                temp = temp -> next;
            }
            if (temp -> data == 9)
            {
                temp -> data = 0;
                temp = head;
                size--;
                if (size == 1)
                {
                    if (temp -> data == 9)
                    {
                        temp -> data = 1;
                        size = sizeOfLL(head);
                        while (temp -> next)
                        {
                            temp = temp -> next;
                        }
                        Node<int>* newNode = new Node<int>(0);
                        temp -> next = newNode;
                        return head;
                    }
                    else
                    {
                        temp -> data++;
                        return head;
                    }
                    
                }
                
                continue;
            }
            else
            {
                temp -> data++;
                return head;
            }
        }
    }
    return head;
}

// Delete alternate nodes
void delete_alternate_node_LinkedList(Node<int> *head)
{
    if(!head || !head -> next)
        return;
    int count = 0;
    Node<int> * current = head;
    Node<int> * prev = head;
    while (current)
    {
        if (count % 2 == 0)
        {
            prev = current;
            current = current -> next;
            count++;
        }
        else
        {
            prev -> next = current -> next;
            current = current -> next;
            prev = current;
            count++;
        }
    }
}

int main()
{
    return 0;
}


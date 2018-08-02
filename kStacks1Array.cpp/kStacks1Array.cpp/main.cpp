#include <iostream>
#include <limits.h>
using namespace std;

class kStacks
{
    int * arr;
    int * top;
    int * nextIndex;
    int k, n;
    int nextAvailable;
public:
    // Constructor to initialise all the data members members
    kStacks(int k, int n)
    {
        // Initialise all the data members
        this -> k = k;
        this -> n = n;
        arr = new int[n];
        top = new int[k];
        nextIndex = new int[n];
        for (int i = 0; i < n - 1; i++) {
            arr[i] = 0;
            nextIndex[i] = i + 1;
        }
        for (int i = 0; i < k; i++)
        {
            top[i] = -1;
        }
        arr[n - 1] = 0;
        nextIndex[n - 1] = -1;
        nextAvailable = 0;
    }
    
    bool isFull() // if there is any space left in the array
    {
        return nextAvailable == -1;
    }
    
    bool isEmpty(int index) // if the stack of a particular index is empty
    {
        return top[index] == -1;
    }
    
    int getTop(int index) // get the top of the stack of the given index
    {
        if (isEmpty(index))
        {
            cout << "Stack underflow" << endl;
            return INT_MIN;
        }
        return arr[top[index]];
    }
    
    void push(int index, int data)
    {
        if (isFull())
        {
            cout << "Stack Overflow!" << endl;
            return;
        }
        int i = nextAvailable;
        nextAvailable = nextIndex[i];
        nextIndex[i] = top[index];
        top[index] = i;
        arr[top[index]] = data;
    }
    
    int pop(int index)
    {
        if (isEmpty(index))
        {
            cout << "Stack underflow!" << endl;
            return INT_MIN;
        }
        int data = arr[top[index]];
        arr[top[index]] = 0; // this maybe skipped but for the sake of clarity, 0 signifies an empty space
        int i = top[index];
        top[index] = nextIndex[i];
        nextIndex[i] = nextAvailable;
        nextAvailable = i;
        return data;
    }
};

int main()
{
    // Let us create 3 stacks in an array of size 10
    int k = 3, n = 10;
    kStacks ks(k, n);
    
    // Let us put some items in stack number 2
    ks.push(2, 15);
    ks.push(2, 45);
    
    // Let us put some items in stack number 1
    ks.push(1, 17);
    ks.push(1, 49);
    ks.push(1, 39);
    
    // Let us put some items in stack number 0
    ks.push(0, 9);
    ks.push(0, 98);
    ks.push(0, 12);
    
    cout << "Popped element from stack 2 is " << ks.pop(2) << endl;
    cout << "The new top element of the stack 2 is " << ks.getTop(2) << endl;
    cout << "Popped element from stack 1 is " << ks.pop(1) << endl;
    cout << "The new top element of the stack 1 is " << ks.getTop(1) << endl;
    cout << "Popped element from stack 0 is " << ks.pop(0) << endl;
    cout << "The new top element of the stack 0 is " << ks.getTop(0) << endl;
    
    return 0;
}



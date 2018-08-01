#include <iostream>
#include <vector>
using namespace std;

class Stack
{
    vector<int>  arr;
    int capacity;
public:
    
    Stack(int capacity)
    {
        this -> capacity = capacity;
    }
    
    unsigned long size()
    {
        return arr.size();
    }
    
    int top()
    {
        if (arr.empty())
        {
            return -1;
        }
        return arr.at(size() - 1);
    }
    
    bool isEmpty()
    {
        return arr.size() == 0;
    }
    
    void push(int data)
    {
        if (arr.size() - 1 == capacity)
        {
            return;
        }
        arr.push_back(data);
    }
    
    void pop()
    {
        if (arr.empty()) {
            return;
        }
        arr.pop_back();
    }
};

int main()
{
    int capacity;
    cout << "Enter the capacity of the stack";
    cin >> capacity;
    
    Stack s(capacity);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
        
    cout << "current size: " << s.size()
    << endl;
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    cout << "current size: " << s.size()
    << endl;
    return 0;
}

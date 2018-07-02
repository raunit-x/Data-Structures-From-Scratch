#include <string>
#include <vector>
#include <iostream>

using namespace std;

class PriorityQueue {
    vector<int> pq;
    
    public :
    
    PriorityQueue() {
        
    }
    
    bool isEmpty() {
        return pq.size() == 0;
    }
    
    // Return the size of priorityQueue - no of elements present
    int getSize() {
        return pq.size();
    }
    
    int getMin() {
        if(isEmpty()) {
            return 0;        // Priority Queue is empty
        }
        return pq[0];
    }
    
    void insert(int element) {
        pq.push_back(element);
        
        int childIndex = pq.size() - 1;
        
        while(childIndex > 0) {
            int parentIndex = (childIndex - 1) / 2;
            
            if(pq[childIndex] < pq[parentIndex]) {
                int temp = pq[childIndex];
                pq[childIndex] = pq[parentIndex];
                pq[parentIndex] = temp;
            }
            else {
                break;
            }
            childIndex = parentIndex;
        }
        
    }
    
    int removeMin()
    {
        if(isEmpty())
            return 0;
        int ans = pq[0];
        pq[0] = pq[pq.size() - 1];
        pq.pop_back();
        int index = 0;
        int LCI = 2*index + 1;
        int RCI = 2*index + 2;
        int minIndex = index;
        while (LCI < pq.size())
        {
            if(pq[minIndex] > pq[LCI])
                minIndex = LCI;
            if(RCI < pq.size() && pq[minIndex] > pq[RCI])
                minIndex = RCI;
            if(minIndex == index)
                break;
            swap(pq[index], pq[minIndex]);
            index = minIndex;
            LCI = 2*index + 1;
            RCI = 2*index + 2;
        }
        return ans;
    }
    
    void display()
    {
        for(int i = 0; i < pq.size(); i++)
            cout << pq.at(i) << endl;
        if(pq.size() == 0)
            cout << "Empty Heap!" << endl;
    }
    
};

void inplaceHeapSort(int input[], int n)
{
    
    // build a heap
    int index = 1;
    int childIndex = index;
    for ( index = 1; index < n; index++)
    {
        childIndex = index;
      while(childIndex > 0) {
          int parentIndex = (childIndex - 1) / 2;
          if(input[childIndex] < input[parentIndex]) {
              int temp = input[childIndex];
              input[childIndex] = input[parentIndex];
              input[parentIndex] = temp;
          }
          else {
              break;
          }
          childIndex = parentIndex;
        }
        
    }
    
    //down-heapify
    
    int size = n;
    while (size > 1) {
    
    swap(input[0], input[size - 1]);
    size--;
    int Pindex = 0;
    int LCI = 2*Pindex + 1;
    int RCI = 2*Pindex + 2;
    int minIndex = Pindex;
    while (LCI < size)
    {
        if(input[minIndex] > input[LCI])
            minIndex = LCI;
        if(RCI < size && input[minIndex] > input[RCI])
            minIndex = RCI;
        if(minIndex == Pindex)
            break;
        swap(input[Pindex], input[minIndex]);
        Pindex = minIndex;
        LCI = 2*Pindex + 1;
        RCI = 2*Pindex + 2;
    }
    }
}




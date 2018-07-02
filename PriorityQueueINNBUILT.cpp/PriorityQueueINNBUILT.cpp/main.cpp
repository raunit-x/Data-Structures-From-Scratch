#include <iostream>
#include<queue>
#include <vector>
using namespace std;

// K-Sorted Array
void KSortedArray(int input[], int size, int k)
{
    priority_queue<int> pq;
    for(int i = 0; i < k; i++)
    {
        pq.push(input[i]);
    }
    int j = 0;
    for(int i = k; i < size; i++)
    {
        input[j] = pq.top();
        pq.pop();
        pq.push(input[i]);
        j++;
    }
    for(int i = 0; i < k; i++)
    {
        input[j] = pq.top();
        j++;
        pq.pop();
    }
    
}

//Smallest K elements
vector<int> kSmallest(int *input, int n, int k)
{
    priority_queue<int> pq;
    vector<int> ans;
    for(int i = 0; i < k; i++)
    {
        pq.push(input[i]);
    }
    for(int i = k; i < n; i++)
    {
        if(input[i] < pq.top())
        {
            pq.push(input[i]);
            pq.pop();
        }
    }
    for(int i = 0; i < k; i++)
    {
        ans.push_back(pq.top());
        pq.pop();
    }
    return ans;
}

//Largest K elements
vector<int> kLargest(int input[], int n, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> ans;
    for(int i = 0; i < k; i++)
    {
        pq.push(input[i]);
    }
    for(int i = k; i < n; i++)
    {
        if(input[i] > pq.top())
        {
            pq.push(input[i]);
            pq.pop();
        }
    }
    for(int i = 0; i < k; i++)
    {
        ans.push_back(pq.top());
        pq.pop();
    }
    return ans;
    
}

//Check HeapMax
bool checkMaxHeap(int arr[], int n)
{
    int ParentIndex = 0;
    int LCI = 2*ParentIndex + 1;
    int RCI = 2*ParentIndex + 2;
    while (LCI < n)
    {
        if(RCI < n && arr[ParentIndex] >= arr[LCI] && arr[ParentIndex] >= arr[RCI])
        {
            ParentIndex++;
            LCI = 2*ParentIndex + 1;
            RCI = 2*ParentIndex + 2;
            continue;
        }
        else if(arr[ParentIndex] >= arr[LCI])
        {
            ParentIndex++;
            LCI = 2*ParentIndex + 1;
            continue;
        }
        else return false;
    }
    return true;
}

//Kth Largest Element
int kthLargest (vector<int> arr, int n, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> ans;
    for(int i = 0; i < k; i++)
    {
        pq.push(arr[i]);
    }
    for(int i = k; i < n; i++)
    {
        if(arr[i] > pq.top())
        {
            pq.push(arr[i]);
            pq.pop();
        }
    }
    return pq.top();
}

// Merge K number of Sorted arrays
vector<int> mergeKSortedArrays(vector<vector<int>*> input)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> ans;
    for(int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i] -> size(); j++)
        {
            pq.push(input[i] -> at(j));
        }
    }
    for(int i = 0; i < pq.size(); i++)
    {
        ans.push_back(pq.top());
        pq.pop();
    }
    return ans;
}

void findMedian(int arr[], int n)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; i++)
    {
        vector<int> ans;
        for(int j = 0; j <= i; j++)
        {
            pq.push(arr[j]);
        }
        while (!pq.empty())
        {
            ans.push_back(pq.top());
            pq.pop();
        }
        if(i == 0)
        {
            cout << arr[0] << endl;
            continue;
        }
        if(ans.size() % 2 == 0)
        {
            cout << (ans.at(ans.size()/2) + ans.at(ans.size()/2 - 1))/2 << endl;
        }
        else cout << ans.at(ans.size()/2) << endl;
    }
}

int buyTicket (int *arr, int n, int k)
{
    priority_queue<int> pq;
    queue<int> p;
    for(int i = 0; i < n; i++)
    {
        pq.push(arr[i]);
        p.push(arr[i]);
    }
    int count = 0;
    while (pq.top() != arr[k])
    {
        if(pq.top() == p.front())
        {
            pq.pop();
            count++;
            p.pop();
        }
        else
        {
            int x = p.front();
            p.pop();
            p.push(x);
        }
    }
    return count + 1;
}




int main()
{
    int arr[] = {2,3,2,2,4};
    
    cout << "wallala" << endl;
    cout << buyTicket(arr, 5, 3) << endl;
    return 0;
}

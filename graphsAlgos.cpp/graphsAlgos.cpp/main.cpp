#include <vector>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Edge
{
    public:
    
    int source;
    int destination;
    int weight;
    Edge()
    {
        this -> source = 0;
        this -> destination = 0;
        this -> weight = 0;
    }

};

class Comp{
public:
    bool operator ()(const Edge& e1, const Edge& e2)
    {
        return e1.weight > e2.weight;
    }
};


int findParent(int v, int * parent)
{
    if (parent[v] == v)
    {
        return v;
    }
    return findParent(parent[v], parent);
}
void  kruskals(Edge * input, int n, int e)
{
    priority_queue<Edge, vector<Edge>, Comp> queue;
    for (int i = 0; i < e; i++)
    {
        queue.push(input[i]);
    }
    Edge * output = new Edge[n - 1];
    
    int * parent = new int[n];
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
    
    int count = 0;
    while (count != n - 1)
    {
        Edge currentEdge = queue.top();
        int sourceParent = findParent(currentEdge.source, parent);
        int destParent = findParent(currentEdge.destination, parent);
        
        if (sourceParent != destParent)
        {
            output[count] = currentEdge;
            count++;
            parent[sourceParent] = destParent;
        }
        queue.pop();
    }
    
    //cout << "MST: " << endl;
    for (int i = 0; i < n - 1; i++)
    {
        cout << min(output[i].source, output[i].destination) << " " << max(output[i].source, output[i].destination) << " " << output[i].weight << endl;
    }
    
}


int main()
{
    int n, e;
    cin >> n >> e;
    Edge * input = new Edge[e];
    
    for (int i = 0; i < e; i++)
    {
        int s, d, w;
        cin >> s >> d >> w;
        input[i].source = s;
        input[i].destination = d;
        input[i].weight = w;
    }
    kruskals(input, n, e);
}

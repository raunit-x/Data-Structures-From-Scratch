#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Vertex
{
public:
    int index;
    int weight;
    int parent;
    bool visited;
    Vertex()
    {
        this -> weight = INT_MAX;
        this -> visited = false;
    }
};
class Comp
{
public:
    
    bool operator()(const Vertex& v1, const Vertex& v2)
    {
        return v1.weight > v2.weight;
    }
    
};
bool compare(Vertex v1, Vertex v2)
{
    return v1.weight < v2.weight;
}
void prims(int ** edges, Vertex * input, int v, int e)
{
    Vertex currentVertex = input[0];
    currentVertex.parent = -1;
    currentVertex.weight = 0;
    currentVertex.visited = true;
    
    int count = 0;
    int j = 0;
    while (count != v - 1)
    {
        priority_queue<Vertex, vector<Vertex>, Comp> queue;
        for (int i = 0; i < v; i++)
        {
            if (edges[i][j])
            {
                if (input[i].visited)
                {
                    continue;
                }
                if (edges[i][j] < input[i].weight)
                {
                    input[i].weight = edges[i][j];
                    input[i].parent = j;
                }
            }
        }
        for (int i = 0; i < v; i++)
        {
            if(!input[i].visited)
            {
                queue.push(input[i]);
            }
        }
        j = queue.top().index;
        input[j].visited = true;
        count++;
    }
    sort(input + 1, input + v, compare);
    cout << "MST: " << endl;
    for (int i = 1; i < v; i++)
    {
        cout << min(input[i].index, input[i].parent) << " " << max(input[i].index, input[i].parent) << " " << input[i].weight << endl;
    }
    
}

int main()
{
    int v, e;
    cin >> v >> e;
    int ** edges = new int*[v];
    for (int i = 0; i < v; i++)
    {
        edges[i] = new int[v];
        for (int j = 0; j < v; j++)
        {
            edges[i][j] = 0;
        }
    }
    // take input in the form of the adjacency matrix
    for (int i = 0; i < e; i++)
    {
        int s, d, w;
        cin >> s >> d >> w;
        edges[s][d] = w;
        edges[d][s] = w;
    }
    
    Vertex * input = new Vertex[v];
    for (int i = 0; i < v; i++)
    {
        input[i].index = i;
    }
    prims(edges, input, v, e);
    
    return 0;
}

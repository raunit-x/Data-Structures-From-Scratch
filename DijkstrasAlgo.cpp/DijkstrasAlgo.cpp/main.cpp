#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Vertex
{
public:
    int index;
    int distance;
    bool visited;
};
class Comp
{
public:
    
    bool operator()(const Vertex& v1, const Vertex& v2)
    {
        return v1.distance > v2.distance;
    }
    
};
void dijkstras(int ** edges, int v, Vertex * input)
{
    int count = 0;
    int j = 0;
    int sum = 0;
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
                if (sum + edges[i][j] < input[i].distance)
                {
                    input[i].distance = sum + edges[i][j];
                }
            }
        }
        for (int i = 0; i < v; i++)
        {
            if (!input[i].visited)
            {
                queue.push(input[i]);
            }
            else continue;
        }
        j = queue.top().index;
        input[j].visited = true;
        sum = queue.top().distance;
        count++;
    }
    cout << "Distances: " << endl;
    for (int i = 0; i < v; i++)
    {
        cout << input[i].index << " " << input[i].distance << endl;
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
        if (i)
        {
            input[i].distance = INT_MAX;
            input[i].visited = false;
        }
        else
        {
            input[i].visited = true;
            input[i].distance = 0;
        }
       
    }
    dijkstras(edges, v, input);
    
    
    return 0;
}

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;
void printBFS(int ** edges, int v, int sv, bool * visited)
{
    queue<int> pendingVertices;
    pendingVertices.push(sv);
    while (!pendingVertices.empty())
    {
        for (int i = 0; i < v; i++)
        {
            if (edges[pendingVertices.front()][i])
            {
                if(i == pendingVertices.front())
                    continue;
                if(visited[i] == false)
                pendingVertices.push(i);
                visited[i] = true;
            }
        }
        cout << pendingVertices.front() << endl;
        visited[pendingVertices.front()] = true;
        pendingVertices.pop();
    }
    
}

void printDFS(int ** edges, int v, int sv, bool * visited)
{
    cout << sv << endl;
    visited[sv] = true;
    for (int i = 0; i < v; i++)
    {
        if(i == sv)
            continue;
        if(visited[i] == true)
            continue;
        if (edges[sv][i] == 1)
        {
            printDFS(edges, v, i, visited);
        }
    }
}

void BFS(int ** edges, int v)
{
    bool * visited = new bool[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < v; i++)
    {
        if (!visited[i])
        {
            printBFS(edges,v,i,visited);
        }
    }
}

void DFS(int ** edges, int v)
{
    bool * visited = new bool[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < v; i++)
    {
        if (!visited[i])
        {
            printDFS(edges,v,i,visited);
        }
        else cout << "Another segment: " << endl;
    }
}

bool hasPath(int ** edges, int v, bool * visited, int ev, int sv)
{
    if (edges[sv][ev] == 1)
    {
        return true;
    }
    else
    {
        visited[sv] = true;
        for (int i = 0; i < v; i++)
        {
            if (edges[sv][i] == 1 && i != sv)
            {
                if(visited[i] == false)
                {
                    bool a = hasPath(edges, v, visited, ev, i);
                    if(a)
                        return true;
                    else continue;
                }
                else continue;
            }
        }
        return false;
    }
}

vector<int> * getPathDFS(int ** edges, int v, bool * visited, int ev, int sv)
{
    vector<int> * ans = new vector<int>();
    if (ev == sv)
    {
        ans -> push_back(sv);
        return ans;
    }
    visited[sv] = true;
    for (int i = 0; i < v; i++)
    {
        if (edges[sv][i] == 1)
        {
            if (visited[i] == false)
            {
                vector<int> * smallAns = getPathDFS(edges, v, visited, ev, i);
                if (smallAns)
                {
                    smallAns -> push_back(sv);
                    return smallAns;
                }
                else continue;
            }
        }
    }
    return NULL;
}
vector<int> * getPathBFS(int ** edges, int v, bool * visited, int ev, int sv)
{
    unordered_map<int, int> ourMap;
    queue<int> pendingVertices;
    vector<int> * ans = new vector<int>();
    pendingVertices.push(sv);
    visited[sv] = true;
    while (pendingVertices.front() != ev)
    {
        
        for (int i = 0; i < v; i++)
        {
            if (edges[pendingVertices.front()][i] == 1)
            {
                if (visited[i] == false)
                {
                    ourMap[i] = pendingVertices.front();
                    pendingVertices.push(i);
                    visited[i] = true;
                   // cout << i << endl;
                    if (i == ev) {
                        break;
                    }
                }
            }
        }
        pendingVertices.pop();
        if (pendingVertices.empty())
        {
            break;
        }
    }
    if (ourMap.count(ev) > 0)
    {
        ans -> push_back(ev);
        int k = ev;
        while (ourMap[k] != sv)
        {
            ans -> push_back(ourMap[k]);
            k = ourMap[k];
        }
        ans -> push_back(sv);
        return ans;
    }
    else return NULL;

}
void getComponent(int ** edges, int v, int sv, bool * visited, vector<int>* ans)
{
    ans -> push_back(sv);
    visited[sv] = true;
    for (int i = 0; i < v; i++)
    {
        if(i == sv)
            continue;
        if(visited[i] == true)
            continue;
        if (edges[sv][i] == 1)
        {
            getComponent(edges, v, i, visited, ans);
        }
    }
}
void returnConnectedComponents(int ** edges, int v, int sv, bool * visited, vector<vector<int>* > * ans)
{
    
    for (int i = 0; i < v; i++)
    {
        if (visited[i] == false)
        {
            vector<int> * smallAns = new vector<int>();
            getComponent(edges, v, i, visited, smallAns);
            ans -> push_back(smallAns);
        }
    }
}

void printPriorityQueue(priority_queue<int, vector<int>, greater <int> > queue)
{
    while (!queue.empty())
    {
        cout << queue.top() << " ";
        queue.pop();
    }
}
int main()
{
    
    int v, e;
    cin >> v >> e;
    int ** edges = new int*[v];
    for(int i = 0; i < v; i++)
    {
        edges[i] = new int[v];
        for (int j = 0; j < v; j++)
        {
            edges[i][j] = 0;
        }
    }
    for (int i = 0; i < e; i++)
    {
        int f, s;
        cin >> f >> s;
        edges[f][s] = 1;
        edges[s][f] = 1;
    }
    
    bool * visited = new bool[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
    }
    vector<vector<int>* >*  ans = new vector<vector<int>* >();
    returnConnectedComponents(edges, v, 0, visited, ans);
    for (int i = 0; i < ans -> size(); i++)
    {
        priority_queue<int, vector<int>, greater <int> > queue;
        for (int j = 0; j < ans -> at(i) -> size(); j++)
        {
            queue.push(ans -> at(i) -> at(j));
        }
        printPriorityQueue(queue);
        cout << endl;
        
    }
   
    for (int i = 0; i < v; i++)
    {
        delete []edges[i];
    }
    delete []edges;
    delete []visited;
    
    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

void check(int ** edges, int v, int sv, bool * visited)
{
    visited[sv] = true;
    for (int i = 0; i < v; i++)
    {
        if(i == sv)
            continue;
        if(visited[i] == true)
            continue;
        if (edges[sv][i] == 1)
        {
            check(edges, v, i, visited);
        }
    }
}

int solve(int n, int m, vector<int> u, vector<int> v)
{
    int ** edges = new int*[n];
    for (int i = 0; i < n; i++)
    {
        edges[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            edges[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        edges[u.at(i) - 1][v.at(i) - 1] = 1;
        edges[v.at(i) - 1][u.at(i) - 1] = 1;
    }
    
    bool * visited = new bool[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            check(edges, n, i, visited);
            count++;
        }
        
    }
    return count;
    
}


void printVector(vector<int> v)
{
    for (int i = 0; i< v.size(); i++)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> u;
    vector<int> v;
    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        u.push_back(x);
    }
    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        v.push_back(x);
    }
    cout << "Answer: ";
    cout << solve(n, m, u, v) << endl;
    
}

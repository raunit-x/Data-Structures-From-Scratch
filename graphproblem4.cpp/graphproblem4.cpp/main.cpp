#include <iostream>
#include <vector>

using namespace std;




bool check(int i, int j, int k, bool *** visited)
{
    return visited[i][j][k] && visited[j][k][i] && visited[i][k][j] && visited[j][i][k] && visited[k][j][i] && visited[k][i][j];
}
void check2(int i, int j, int k, bool *** visited)
{
    visited[i][j][k] = true;
    visited[j][k][i] = true;
    visited[i][k][j] = true;
    visited[j][i][k] = true;
    visited[k][j][i] = true;
    visited[k][i][j] = true;
}

int solve(int n,int m,vector<int>u,vector<int>v)
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
    bool *** visited = new bool**[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = new bool*[n];
        for (int j = 0; j < n; j++)
        {
             visited[i][j] = new bool[n];
            for (int k = 0; k < n; k++)
            {
                visited[i][j][k] = false;
            }
        }
    }
    
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (edges[i][j])
            {
                for (int k = 0; k < n; k++)
                {
                    if (edges[j][k])
                    {
                        if (edges[i][k] && !check(i, j, k, visited))
                        {
                            check2(i, j, k, visited);
                            count++;
                        }
                    }
                }
            }
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


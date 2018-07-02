#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Coordinates
{
public:
    int row;
    int column;
    Coordinates()
    {
        this -> row = 10;
        this -> column = 10;
    }
};

bool withinLimits(int r, int i, int j)
{
    if (i < r && i >= 0)
    {
        if (j < r && j >= 0)
        {
            return true;
        }
    }
    return false;
}

int dfs(char ** cake, int v, Coordinates a, bool ** visited)
{
    if (visited[a.row][a.column])
    {
        return 0;
    }
    visited[a.row][a.column] = true;
    int count = 1;
    int arr1[] = {0, -1, 0, 1};
    int arr2[] = {-1, 0, 1, 0};
    for (int i = 0; i < 4; i++)
    {
        int dx = a.row + arr1[i];
        int dy = a.column + arr2[i];
        if (withinLimits(v,dx,dy) && cake[dx][dy] == '1')
        {
            Coordinates b;
            b.row = dx;
            b.column = dy;
            count = count + dfs(cake, v, b, visited);
        }
    }
    return count;
}


int solve(int n,char ** cake)
{
    
    int Max = 0;
    bool ** visited = new bool*[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = new bool[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!visited[i][j] && cake[i][j] == '1')
            {
                Coordinates b;
                b.row = i;
                b.column = j;
                Max = max(Max, dfs(cake, n, b, visited));
            }
        }
        
    }
    return Max;
}


int main()
{
    int n;
    cin >> n;
    char ** cake = new char*[n];
    for (int i = 0; i < n; i++)
    {
        cake[i] = new char[n];
        
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char ch;
            cin >> ch;
            cake[i][j] = ch;
        }
    }

    
    
    cout << " ->" << endl;
    cout << solve(n, cake) << endl;
    
}

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Coordinates
{
public:
    int row;
    int column;
    bool found;
    Coordinates()
    {
        this -> row = 10;
        this -> column = 10;
        this -> found = false;
    }
    Coordinates(int row, int column)
    {
        this -> row = row;
        this -> column = column;
        this -> found = true;
    }
};

bool withinLimits(int r, int c, int i, int j)
{
    if (i < r && i >= 0)
    {
        if (j < c && j >= 0)
        {
            return true;
        }
    }
    return false;
}

Coordinates forC(char ** Graph,int r, int c, bool ** visited)
{
    Coordinates a;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (Graph[i][j] == 'C' && !visited[i][j])
            {
                a.row = i;
                a.column = j;
                a.found = true;
                return a;
            }
        }
    }
    return a;
}

Coordinates searchCharacter(char ** Graph,int r, int c, int x, Coordinates a, bool ** visited)
{
    unordered_map<int, char> ourMap;
    ourMap[0] = 'O';
    ourMap[1] = 'D';
    ourMap[2] = 'I';
    ourMap[3] = 'N';
    ourMap[4] = 'G';
    ourMap[5] = 'N';
    ourMap[6] = 'I';
    ourMap[7] = 'N';
    ourMap[8] = 'J';
    ourMap[9] = 'A';
    
    Coordinates b;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            if (withinLimits(r, c, a.row + i, a.column + j))
            {
                if (Graph[a.row + i][a.column + j] == ourMap[x] && !visited[a.row + i][a.column + j])
                {
                    visited[a.row + i][a.column + j] = true;
                    Coordinates B(a.row + i, a.column + j);
                   // cout << ourMap[x] << ":" << B.row << " " << B.column << endl;
                    return B;
                }
            }
            else continue;
        }
    }
   // cout << "WAzza!" << endl;
    return b;
}
int solve(char ** Graph,int r, int c)
{
    bool ** visited = new bool*[c];
    for (int i = 0; i < c; i++)
    {
        visited[i] = new bool[r];
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            visited[i][j] = false;
        }
    }
    Coordinates A = forC(Graph, r, c, visited);
   // cout << A.row << " " << A.column << endl;
    if (A.found)
    {
        visited[A.row][A.column] = true;
        for (int i = 0; i < 10; i++)
        {
            A = searchCharacter(Graph, r, c, i, A, visited);
            if (!A.found)
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int main()
{
    int r, c;
    cin >> r >> c;
    char ** Graph = new char*[c];
    for (int i = 0; i < c; i++)
    {
        Graph[i] = new char[r];
        
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            char ch;
            cin >> ch;
            Graph[i][j] = ch;
        }
    }
    if (solve(Graph, r, c))
    {
       cout << "true" << endl;
    }
    else cout << "false" << endl;
    return 0;
}










/*class Coordinates
{
public:
    int row;
    int column;
    bool found;
    Coordinates()
    {
        this -> row = 10;
        this -> column = 10;
        this -> found = false;
    }
    Coordinates(int row, int column)
    {
        this -> row = row;
        this -> column = column;
        this -> found = true;
    }
};

Coordinates func(int x, int y)
{
    Coordinates C(x,y);
    return C;
}


int main()
{
    int x = 1, y = 1;
    cout << func(x, y).row << " " << func(x, y).column << endl;
    Coordinates a = func(x, y);
    cout << a.row << " " << a.column << endl;
}
    */
    
    


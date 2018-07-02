#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <unordered_map>
#include <queue>

using namespace std;


int fibo_DP(int n)
{
    int * ans = new int[n + 1];
    ans[0] = 0;
    ans[1] = 1;
    for (int i = 2; i < n + 1; i++)
    {
        ans[i] = ans[i - 1] + ans[i - 2];
    }
    
    return ans[n];
}


int fibo_memoization(int n, int * ans)
{
    if (ans[n-1] == -1)
    {
        ans[n-1] = fibo_memoization(n - 1, ans);
    }
    if (ans[n-2] == -1)
    {
        ans[n-2] = fibo_memoization(n - 2, ans);
    }
    
    ans[n] = ans[n - 1] + ans[n - 2];
    return ans[n];
}


int fibo_memoization(int n)
{
    int * ans = new int[n + 1];
    for (int i = 0 ; i < n + 1; i++)
    {
        ans[i] = -1;
    }
    return fibo_memoization(n, ans);
}



int countStepsTo1(int n, int * ans)
{
    if(n == 1)
    {
        ans[1] = 0;
        return 0;
    }
    
    if (ans[n - 1] == -1)
    {
        ans[n - 1] = countStepsTo1(n - 1, ans);
    }
    
    int y = INT_MAX;
    int z = INT_MAX;
    if (n % 2 == 0)
    {
        if (ans[n / 2] == -1)
        {
            ans[n / 2] = countStepsTo1(n/2, ans);
            
        }
        y = ans[n/2];
    }
    
    if (n % 3 == 0)
    {
        if (ans[n/3] == -1)
        {
            ans[n/3] = countStepsTo1(n/3, ans);
            
        }
        z = ans[n/3];
    }
    
    ans[n] = min(ans[n - 1], min(y, z)) + 1;
    return ans[n];
}

int countStepsTo1(int n)
{
    int * ans = new int[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        ans[i] = -1;
    }
    return countStepsTo1(n, ans);
}


long staircase(int n)
{
    if(n <= 2)
        return n;
    if (n == 3)
    {
        return 4;
    }
    long * ans = new long[n + 1];
    ans[1] = 1;
    ans[2] = 2;
    ans[2] = 3;
    for (int i = 4; i <= n; i++)
    {
        ans[i] = ans[i - 1] + ans[i - 2] + ans[i - 3];
    }
    return ans[n];
}


int minCount(int n, int * ans)
{
    if (n <= 1)
    {
        ans[n] = n;
        return ans[n];
    }
    int x = pow(n, 0.5);
    int min = INT_MAX;
    for (int i = 1; i <= x; i++)
    {
        if (ans[n - int(pow(i, 2))] == -1)
        {
            ans[n - int(pow(i, 2))] = minCount(n - pow(i, 2), ans) + 1;
        }
        int a = ans[n - int(pow(i, 2))];
        if (a < min)
        {
            min = a;
        }
    }
    ans[n] = min;
    
    return ans[n];
}

int minCount(int x)
{
    int * ans = new int[x + 1];
    for (int i = 0; i < x + 1; i++)
    {
        ans[i] = -1;
    }
    
    return minCount(x, ans);
}

int balancedBTs(int h)
{
    if (h <= 1)
    {
        return 1;
    }
    long x = (balancedBTs(h - 1)) % (int(pow(10,9)) + 7);
    long y = (balancedBTs(h - 2)) % (int(pow(10,9)) + 7);
    
    return (x * x + 2 * x * y) % (int(pow(10,9)) + 7);
}

long binaryTreesOfHeightH(int h, long * ans)
{
    if (h <= 1)
    {
        ans[h] = 1;
        return ans[h];
    }
    if (ans[h - 1] == -1)
    {
        ans[h - 1] = (binaryTreesOfHeightH(h - 1, ans)) % (int(pow(10,9)) + 7);
    }
    long x = ans[h - 1];
    if (ans[h - 2] == -1)
    {
        ans[h - 2] = (binaryTreesOfHeightH(h - 2, ans)) % (int(pow(10,9)) + 7);
    }
    long y = (binaryTreesOfHeightH(h - 2, ans)) % (int(pow(10,9)) + 7);
    ans[h] = (x * x + 2 * x * y) % (int(pow(10,9)) + 7);
    return ans[h];
}
long binaryTreesOfHeightH(int h)
{
    long * ans = new long[h + 1];
    for (int i = 0; i < h + 1; i++)
    {
        ans[i] = -1;
    }
    return binaryTreesOfHeightH(h, ans);
    
}

class Coordinates
{
public:
    int row;
    int column;
    
    Coordinates(int row, int column)
    {
        this -> row = row;
        this -> column = column;
    }
    
};

bool withinLimits(int m, int n, int i, int j)
{
    return (i <= m - 1 && j <= n - 1);
}


int minCostPath_better(int **input, int m, int n, int i, int j, int ** ans)
{
    if (i == m - 1 && j == n - 1)
    {
        return input[m -1][n - 1];
    }
    
    if (i > m - 1  || j > n - 1)
    {
        return INT_MAX;
    }
    
    if (ans[i][j] != -1)
    {
        return ans[i][j];
    }
    
    int x = minCostPath_better(input, m, n, i, j + 1, ans);
    if (x < INT_MAX)
    {
        ans[i][j + 1] = x;
    }
    int y = minCostPath_better(input, m, n, i + 1, j + 1, ans);
    if (y < INT_MAX)
    {
        ans[i + 1][j + 1] = y;
    }
    int z = minCostPath_better(input, m, n, i + 1, j, ans);
    if (z < INT_MAX)
    {
        ans[i + 1][j] = z;
    }
    
    ans[i][j] = min(x, min(y, z)) + input[i][j];
    
    return ans[i][j];
}

int minCostPathDP(int **input, int m, int n)
{
    int ** ans = new int*[m];
    for (int i = 0; i < m; i++)
    {
        ans[i] = new int[n];
    }
    ans[m - 1][n - 1] = input[m - 1][n - 1];
    
    for (int i = m - 2; i >= 0; i--)
    {
        ans[n - 1][i] += ans[n - 1] [i + 1];
    }
    
    for (int i = n - 2; i >= 0; i--)
    {
        ans[i][m - 1] += ans[i + 1] [m - 1];
    }
    
    for (int i = m - 2; i >= 0; i--)
    {
        for (int j = m - 2; j >= 0; j--)
        {
            ans[i][j] = input[i][j] + min(ans[i + 1][j], min(ans[i + 1][j + 1], ans[i][j + 1]));
        }
    }
    
    return ans[0][0];
}


int minCostPath(int **input, int m, int n, Coordinates a)
{
    if (a.row == m - 1 && a.column == n - 1)
    {
        return input[m -1][n - 1];
    }
    int arr1[] = {0, 1, 1};
    int arr2[] = {1, 1, 0};
    
    int min = INT_MAX;
    
    for (int i = 0 ; i < 3; i++)
    {
        int dx = a.row + arr1[i];
        int dy = a.column + arr2[i];
        if (withinLimits(m, n, dx, dy))
        {
            Coordinates b(dx, dy);
            int minTemp = minCostPath(input, m, n, b);
            if (minTemp < min)
            {
                min = minTemp;
            }
        }
        else continue;
    }
    
    return min + input[a.row][a.column];
}

int minCostPath(int **input, int m, int n)
{
    int ** ans = new int*[m];
    for (int i = 0; i < m; i++)
    {
        ans[i] = new int[n];
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ans[i][j] = -1;
        }
    }
    return minCostPath_better(input, m, n, 0, 0, ans);
}


int LCS_DP(string s, string t)
{
    int m = int(s.size());
    int n = int(t.size());
    
    int ** ans = new int*[m + 1];
    for (int i = 0; i < m + 1; i++)
    {
        ans[i] = new int[n + 1];
        for (int j = 0; j < n + 1; j++)
        {
            ans[i][j] = 0;
        }
    }
    

    for (int i = 1; i < m + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (s[m - i] == t[n - j])
            {
                ans[i][j] = 1 + ans[i - 1][j - 1];
            }
            else
            {
                ans[i][j] = max(ans[i][j - 1], ans[i - 1][j]);
            }
        }
    }
    
    return ans[m][n];
}

int LCS_better(string s, string t, int ** ans)
{
    if (!s.size() || !t.size())
    {
        return 0;
    }
    
    int m = int(s.size());
    int n = int(t.size());
    
    if (ans[m][n] != -1)
    {
        return ans[m][n];
    }
    
    if (s[0] == t[0])
    {
        ans[m - 1][n - 1] = LCS_better(s.substr(1), t.substr(1), ans);
        ans[m][n] = 1 + ans[m - 1][n - 1];
        return ans[m][n];
    }
    
    if (ans[m - 1][n] == -1)
    {
        ans[m - 1][n] = LCS_better(s.substr(1), t, ans);
    }
    int a = LCS_better(s.substr(1), t, ans);
    if (ans[m][n - 1] == -1)
    {
        ans[m][n - 1] = LCS_better(s, t.substr(1), ans);
    }
    int b = LCS_better(s, t.substr(1), ans);
    
    ans[m][n] = max(a, b);
    
    return ans[m][n];

}


int LCS_better(string s, string t)
{
    int m = int(s.size());
    int n = int(t.size());
    
    int ** ans = new int*[m + 1];
    for (int i = 0; i < m + 1; i++)
    {
        ans[i] = new int[n + 1];
        for (int j = 0; j < n + 1; j++)
        {
            ans[i][j] = -1;
        }
    }
    
    return LCS_better(s, t, ans);
}



int editDistance_DP(string s, string t)
{
    int m = int(s.size());
    int n = int(t.size());
    
    int ** ans = new int*[m + 1];
    for (int i = 0; i < m + 1; i++)
    {
        ans[i] = new int[n + 1];
    }
    
    for (int i = 0; i < m + 1; i++)
    {
        ans[i][0] = i;
    }
    
    for (int j = 0; j < n + 1; j++)
    {
        ans[0][j] = j;
    }
    
    for (int i = 1; i < m + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                ans[i][j] = ans[i - 1][j -1];
            }
            else
            {
                ans[i][j] = min(ans[i - 1][j], min(ans[i - 1][j - 1], ans[i][j - 1])) + 1;
            }
        }
    }
    
    return ans[m][n];
}


int editDistance(string s1, string s2)
{
    if (s1.size() == 0)
    {
        return int(s2.size());
    }
    if (s2.size() == 0)
    {
        return int(s1.size());
    }
    
    if (s1[0] == s2[0])
    {
        return editDistance(s1.substr(1), s2.substr(1));
    }
    else
    {
        int a = editDistance(s1, s2.substr(1));
        int b = editDistance(s1.substr(1), s2);
        int c = editDistance(s1.substr(1), s2.substr(1));
        return min(a,min(b,c)) + 1;
    }
    
}


int getMaxMoney(int * arr, int n, int * ans)
{
    if (n == 0)
    {
        return 0;
    }
    if (ans[n - 1] == -1)
    {
        ans[n - 1] = getMaxMoney(arr + 1, n - 1, ans);
    }
    
    if (ans[n - 2] == -1)
    {
        ans[n - 2] = getMaxMoney(arr + 2, n - 2, ans);
    }
    
    ans[n] = max(ans[n - 2] + arr[0], ans[n - 1]);
    
    return ans[n];
}

int getMaxMoney(int * arr, int n)
{
    int * ans = new int[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        ans[i] = -1;
    }
    
    return getMaxMoney(arr, n, ans);
}
    
int lis(int arr[], int n)
{
    unordered_map<int, int> ourMap;
    priority_queue<int> queue;
    ourMap[arr[0]] = 1;
    for (int i = 1; i < n; i++)
    {
        int max = 0;
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] < arr[i])
            {
                if (ourMap[arr[j]] > max)
                {
                    max = ourMap[arr[j]];
                }
            }
        }
        ourMap[arr[i]] = max + 1;
        cout << i << ": " << ourMap[arr[i]] << endl;
    }
    for (int i = 0; i < n; i++)
    {
        queue.push(ourMap[arr[i]]);
    }
    
    return queue.top();
}

int countWaysToMakeChange(int denominations[], int numDenominations, int value, int * ans)
{
    if (value == 0)
    {
        ans[0] = 0;
        return 0;
    }
    if (ans[value] != -1)
    {
        return ans[value];
    }
    unordered_map<int, int> ourMap;
    int sum = 0;
    for (int i = 0; i < numDenominations; i++)
    {
        if(value - denominations[i] < 0)
            continue;
        
        if (ans[value - denominations[i]] == -1)
        {
            ans[value - denominations[i]] = countWaysToMakeChange(denominations, numDenominations, value - denominations[i], ans) + 1;
        }
        sum += ans[value - denominations[i]];
    }
    
    ans[value] = sum;
    
    return ans[value];
    
}

int countWaysToMakeChange(int denominations[], int numDenominations, int value)
{
    int * ans = new int[value + 1];
    for (int i = 0; i < value + 1; i++)
    {
        ans[i] = -1;
    }
    return countWaysToMakeChange(denominations, numDenominations, value, ans);
}

void swap(char str1[], char str2[], int size1, int size2)
{
    
}

int main()
{
    
    return 0;
}

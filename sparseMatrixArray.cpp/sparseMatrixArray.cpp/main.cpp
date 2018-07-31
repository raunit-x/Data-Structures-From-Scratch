#include <iostream>

using namespace std;

int main()
{
    // Assume 4x5 sparse matrix
    int sparseMatrix[4][5] =
    {
        {0 , 0 , 3 , 0 , 4 },
        {0 , 0 , 5 , 7 , 0 },
        {0 , 0 , 0 , 0 , 0 },
        {0 , 2 , 6 , 0 , 0 }
    };
    int size = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (sparseMatrix[i][j] != 0)
            {
                size++;
            }
        }
    }
    
    int compactMatrix[3][size]; // 3 rows here represent: Row -> 0, Column -> 1 and Value -> 2
    int k = 0;
    
    // forming the compact matrix
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (sparseMatrix[i][j] != 0)
            {
                compactMatrix[0][k] = i;
                compactMatrix[1][k] = j;
                compactMatrix[2][k] = sparseMatrix[i][j];
                k++;
            }
        }
    }
    cout << "Row     : ";
    for(int i = 0; i < size; i++)
    {
        cout << compactMatrix[0][i] << " ";
    }
    cout << "\nColumn  : ";
    for(int i = 0; i < size; i++)
    {
        cout << compactMatrix[1][i] << " ";
    }
    cout << "\nValue   : ";
    for(int i = 0; i < size; i++)
    {
        cout << compactMatrix[2][i] << " ";
    }
    cout << endl;
}

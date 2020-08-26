#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

/**
 * Initialize an matrix.
 *
 * @param columns Number of columns.
 * @param rows Number of rows.
 * @return Matrix initialized
 */
vector<vector<int> > initializeMatrix(int columns, int rows) {
    vector<vector<int> > a;
    for (size_t i = 0; i < rows; i++)
    {
        vector<int> ac;
        for (size_t j = 0; j < columns; j++)
        {
            ac.push_back(rand() % 100);
        }
        a.push_back(ac);
    }
    return a;
}

/**
 * Compute the matrix multiplication.
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix multiplication between A and B
 */
vector<vector<int> > computeMult(vector<vector<int> > a, vector<vector<int> > b) {
    vector<vector<int> > mult;
    for (size_t i = 0; i < a.size(); i++)
    {
        vector<int> res(a.size(), 0);
        for (size_t j = 0; j < a[i].size(); j++)
        {
            for (size_t k = 0; k < a[i].size(); k++)
            {
                res[j] += a[i][k] * b[k][j];
            }
        }
        mult.push_back(res);
    }
    return mult;
}

/**
 * Visualize a determinate matrix.
 *
 * @param a Matrix instance.
 */
void visualizeArray(vector<vector<int> > a) {
    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < a[i].size(); j++)
        {
            cout << a[i][j] << "|";
            if (j == a[i].size() - 1)
            {
                cout << "\n";
                for (size_t ch = 0; ch < (a.size() * 2) + a.size(); ch++)
                {
                    cout << "-";
                }
                cout << "\n";
            }
        }
    }
}

/**
 * Main function.
 * 
 * @return State of the process
 */
int main()
{
    vector<vector<int> > a, b, mult;
    int rows, columns;
    cout << "Ingrese el número de filas: ";
    cin >> rows;
    cout << "Ingrese el número de columnas: ";
    cin >> columns;
    a = initializeMatrix(columns, rows);
    b = initializeMatrix(columns, rows);

    mult = computeMult(a, b);
    cout << "Elementos de la matriz A: \n";
    visualizeArray(a);

    cout << "Elementos de la matriz B: \n";
    visualizeArray(b);

    cout << "Resultado:  \n";
    visualizeArray(mult);
    return 0;

}

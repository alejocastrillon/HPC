#include <iostream>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <thread>
#include <functional>
#include "timer.hh"

using namespace std;

/**
 * Initialize an matrix.
 *
 * @param columns Number of columns.
 * @param dimensions Number of dimensions.
 * @return Matrix initialized
 */
vector<vector<int>> initializeMatrix(int dimensions)
{
    vector<vector<int>> a;
    for (size_t i = 0; i < dimensions; i++)
    {
        vector<int> ac;
        for (size_t j = 0; j < dimensions; j++)
        {
            ac.push_back(rand() % 100);
        }
        a.push_back(ac);
    }
    return a;
}

/**
 * Compute the  result of a cell of matrix multiplication.
 *
 * @param a Matrix A
 * @param b Matrix B
 * @param i Column index
 * @param j Row index
 * @param sum Result of a multiplication cell
 */
void computeCell(const vector<vector<int>> &a, const vector<vector<int>> &b, int i, int j, int &sum)
{
    for (size_t k = 0; k < a.size(); k++)
    {
        sum += a[i][k] * b[k][j];
    }
}

/**
 * Assignment the matrix multiplication at threads.
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix multiplication between A and B
 */
vector<vector<int>> assingMult(vector<vector<int>> a, vector<vector<int>> b)
{
    vector<vector<int>> mult;
    vector<thread> threads;
    for (size_t i = 0; i < a.size(); i++)
    {
        mult.push_back(vector<int>(a.size(), 0));
        for (size_t j = 0; j < a[i].size(); j++)
        {
            int &result = mult[i][j];
            threads.push_back(thread(computeCell, cref(a), cref(b), i, j, ref(result)));
        }
    }
    /* const auto processorCount = thread::hardware_concurrency();
    int iteration = threads.size() / processorCount; */
    for (thread &t : threads)
        t.join();
    return mult;
}

/**
 * Visualize a determinate matrix.
 *
 * @param a Matrix instance.
 */
void visualizeArray(vector<vector<int>> a)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < a[i].size(); j++)
        {
            cout << a[i][j] << "|";
            if (j == a[i].size() - 1)
            {
                cout << endl;
                for (size_t ch = 0; ch < (a.size() * 2) + a.size(); ch++)
                {
                    cout << "-";
                }
                cout << endl;
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
    vector<vector<int>> a, b, mult;
    int dimensions;
    cout << "Ingrese el número de dimensiones: ";
    cin >> dimensions;
    Timer t;
    a = initializeMatrix(dimensions);
    b = initializeMatrix(dimensions);

    mult = assingMult(a, b);
    cout << "Elementos de la matriz A: " << endl;
    visualizeArray(a);

    cout << "Elementos de la matriz B: " << endl;
    visualizeArray(b);

    cout << "Resultado: " << endl;
    visualizeArray(mult);

    cout << "Tiempo de ejecución: " << t.elapsed() << "ms" << endl;

    return 0;
}

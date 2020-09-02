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
int** initializeMatrix(int dimensions)
{
    int** a;
    a = new int*[dimensions];
    for (size_t i = 0; i < dimensions; i++)
    {
        a[i] = new int[dimensions];
        for (size_t j = 0; j < dimensions; j++)
        {
            a[i][j] = rand() % 100;
        }
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
void computeCell(const vector<vector<int>> &a, const vector<vector<int>> &b, int i, vector<int> &sum)
{
    for (size_t j = 0; j < a.size(); j++)
    {
        for (size_t k = 0; k < a.size(); k++)
        {
            sum[j] += a[i][k] * b[k][j];
        }
    }
}

/**
 * Assignment the matrix multiplication at threads.
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix multiplication between A and B
 */
int** assingMult(int** a, int** b)
{
    int** mult;
    vector<thread> threads;
    for (size_t i = 0; i < sizeof(a); i++)
    {
        mult[i] = new int[sizeof(a)];
        int* &result = mult[i];
        threads.push_back(thread(computeCell, cref(a), cref(b), i, ref(result)));
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
void visualizeArray(int** a)
{
    for (size_t i = 0; i < sizeof(a); i++)
    {
        for (size_t j = 0; j < sizeof(a[i]); j++)
        {
            cout << a[i][j] << "|";
            if (j == sizeof(a[i]) - 1)
            {
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
    int** a;
    int** b;
    int** mult;
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

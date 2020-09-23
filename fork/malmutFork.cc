#include <iostream>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <unistd.h>
#include <functional>
#include <sys/wait.h>
#include "../timer.hh"

using namespace std;

/**
 * Initialize a matrix.
 *
 * @param dimensions Number of dimensions.
 * @return Matrix initialized
 */
int **initializeMatrix(int dimensions)
{
    int **a = new int *[dimensions];
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
 * Visualize a determinate matrix.
 *
 * @param a Matrix instance
 * @param dimensions Matrix dimensions number
 */
void visualizeArray(int **a, int dimensions)
{
    for (size_t i = 0; i < dimensions; i++)
    {
        for (size_t j = 0; j < dimensions; j++)
        {
            cout << a[i][j] << "|";
            if (j == dimensions - 1)
            {
                cout << endl;
            }
        }
    }
}

/**
 * Compute the  result of a cell of matrix multiplication.
 *
 * @param a Matrix A
 * @param b Matrix B
 * @param i Column index
 * @param dimensions Matrix dimensions number
 * @param sum Result of a multiplication cell
 */
void computeCell(int **&a, int **&b, int i, int dimensions, int *&sum)
{
    for (size_t j = 0; j < dimensions; j++)
    {
        sum[j] = 0;
        for (size_t k = 0; k < dimensions; k++)
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
 * @param dimensions Matrix dimension number
 * @return Matrix multiplication between A and B
 */
int **assingMult(int **a, int **b, int dimensions)
{
    int **mult = new int *[dimensions];
    pid_t procesosHijos[dimensions];
    int status[dimensions];
    for (size_t i = 0; i < dimensions; i++)
    {
        mult[i] = new int[dimensions];
        int *&result = mult[i];
        if (procesosHijos[i] = fork() < 0)
        {
            cout << "No se pudo crear el subproceso" << endl;
            exit(0);
        }
        else if (procesosHijos[i] == 0)
        {
            computeCell(ref(a), ref(b), i, dimensions, ref(result));
        }
    }
    for (size_t i = 0; i < dimensions; i++)
    {
        waitpid(procesosHijos[i], &status[i], 0);
    }
    return mult;
}

/**
 * Main function.
 * 
 * @return State of the process
 */
int main()
{
    int **a;
    int **b;
    int **mult;
    int dimensions;
    cout << "Ingrese el número de dimensiones: ";
    cin >> dimensions;
    a = initializeMatrix(dimensions);
    b = initializeMatrix(dimensions);
    Timer t;
    cout << "Entro" << endl;
    mult = assingMult(a, b, dimensions);
    cout << "Elementos de la matriz A: " << endl;
    visualizeArray(a, dimensions);

    cout << "Elementos de la matriz B: " << endl;
    visualizeArray(b, dimensions);
    cout << "Resultado: " << endl;
    visualizeArray(mult, dimensions);

    cout << "Tiempo de ejecución: " << t.elapsed() << "ms" << endl;

    return 0;
}

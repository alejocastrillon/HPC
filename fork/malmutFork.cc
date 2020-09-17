#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "../timer.hh"

using namespace std;

/**
 * Initialize an matrix.
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
 * Compute the matrix multiplication.
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix multiplication between A and B
 */
int **computeMult(int **a, int **b, int dimensions)
{
    int **mult = new int *[dimensions];
    for (size_t i = 0; i < dimensions; i++)
    {
        mult[i] = new int[dimensions];
        for (size_t j = 0; j < dimensions; j++)
        {
            mult[i][j] = 0;
            for (size_t k = 0; k < dimensions; k++)
            {
                mult[i][j] += a[i][k] * b[k][j];
            }
            cout << mult[i][j] << " | ";
        }
        cout << endl;
    }
    return mult;
}

/**
 * Visualize a determinate matrix.
 *
 * @param a Matrix instance.
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
                cout << "\n";
                for (size_t ch = 0; ch < (dimensions * 2) + dimensions; ch++)
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
    int **a;
    int **b;
    int **mult;
    int pid;
    int pipefd[2];
    int dimensions;
    cout << "Ingrese el número de dimensiones: ";
    cin >> dimensions;
    Timer t;
    a = initializeMatrix(dimensions);
    b = initializeMatrix(dimensions);

    cout << "Elementos de la matriz A: \n";
    visualizeArray(a, dimensions);

    cout << "Elementos de la matriz B: \n";
    visualizeArray(b, dimensions);
    pipe(pipefd);
    if (pipefd < 0)
    {
        cout << "Pipe error" << endl;
    }
    pid = fork();
    if (pid == -1)
    {
        cout << "Can't fork" << endl;
    }
    if (pid == 0)
    {
        mult = computeMult(a, b, dimensions);
    }

    /* cout << "Resultado:  \n";
    visualizeArray(mult, dimensions); */

    cout << "Tiempo de ejecución: " << t.elapsed() << "ms" << endl;

    return 0;
}

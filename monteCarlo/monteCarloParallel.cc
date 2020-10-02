/* C++ program for estimation of Pi using Monte 
   Carlo Simulation */
#include <bits/stdc++.h>
#include <vector>
#include <thread>
#include "../timer.hh"

// Defines precision for x and y values. More the
// interval, more the number of significant digits
#define INTERVAL 1000
using namespace std;

void monteCarlo(int &circlePoints, int &squarePoints, double &pi, int minRange, int maxRange)
{
    double randX, randY, originDist;
    for (size_t i = minRange; i < maxRange; i++)
    {
        // Randomly generated x and y values
        randX = double(rand() % (INTERVAL + 1)) / INTERVAL;
        //cout << "aleatorio x " << randX;
        randY = double(rand() % (INTERVAL + 1)) / INTERVAL;
        //cout << "aleatorio y " << randY;
        // Distance between (x, y) from the origin
        originDist = randX * randX + randY * randY;
        // Checking if (x, y) lies inside the define
        // circle with R=1
        //cout << originDist;
        if (originDist <= 1)
            circlePoints++;
        // Total number of points generated
        squarePoints++;
        // estimated pi after this iteration
        pi = double(4 * circlePoints) / squarePoints;
        // For visual understanding (Optional)
        /*cout << i << randX << " " << randY << " " << circlePoints
             << " " << squarePoints << " - " << pi << endl
             << endl;*/
    }
}

int main()
{
    int interval, i;
    double pi;
    int circlePoints = 0, squarePoints = 0;
    int cantidadHilos;
    cout << "Ingrese la cantidad de hilos:" << endl;
    cin >> cantidadHilos;
    // Initializing rand()
    srand(time(NULL));
    int cantidadMuestra = round((INTERVAL * INTERVAL) / cantidadHilos);
    int minRange = 0;
    int maxRange = cantidadMuestra;
    vector<thread> threads;
    for (size_t i = 0; i < cantidadHilos; i++)
    {
        /* cout << "Minimo Rango: " << minRange << endl;
        cout << "Maximo Rango: " << maxRange << endl; */
        minRange += cantidadMuestra;
        if (i == (cantidadHilos - 1))
        {
            maxRange = INTERVAL * INTERVAL;
        }
        else
        {
            maxRange += cantidadMuestra;
        }
        threads.push_back(thread(
            monteCarlo, ref(circlePoints), ref(squarePoints), ref(pi), minRange, maxRange));
    }
    Timer t;
    for (thread &t : threads)
        t.join();
    cout << "Tiempo de ejecución: " << t.elapsed() << "ms" << endl;
    // Final Estimated Value
    cout << "\nFinal Estimation of Pi = " << pi << endl;

    return 0;
}

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <thread>
#include "../timer.hh"

#define NUMDARTS 100000
using namespace std;

void dartBoard(int &numHits, int &cont, int minRange, int maxRange)
{
    double x_cor = 0;
    double y_cor = 0;
    double x_sum = 0;
    double y_sum = 0;
    double x_y_total = 0;
    if (NUMDARTS != 0)
    {
        for (int i = minRange; i < maxRange; i++)
        {

            x_cor = rand() * (1.0 / RAND_MAX);
            y_cor = rand() * (1.0 / RAND_MAX);
            x_sum = (x_cor * x_cor);
            y_sum = (y_cor * y_cor);
            x_y_total = (x_cor * x_cor) + (y_cor * y_cor);
            if (x_y_total < 1)
            {
                numHits++;
            }
            else
            {
                cont++;
            }
        }
    }
}

int main()
{
    int numHits = 0;
    int cont = 0;
    double piAprox = 0;
    int cantidadHilos = 100;
    int cantidadMuestra;
    /* cout << "Ingrese la cantidad de hilos: " << endl;
    cin >> cantidadHilos; */
    cantidadMuestra = round(NUMDARTS / cantidadHilos);
    int minRange = 0;
    int maxRange = cantidadMuestra;
    vector<thread> threads;
    for (size_t i = 0; i < cantidadHilos; i++)
    {
        threads.push_back(thread(dartBoard, ref(numHits), ref(cont), minRange, maxRange));
        minRange += cantidadMuestra;
        if (i == (cantidadHilos - 1))
        {
            maxRange = NUMDARTS;
        }
        else
        {
            maxRange += cantidadMuestra;
        }
    }
    Timer t;
    for (thread &t : threads)
        t.join();
    cout << "Tiempo de ejecution: " << t.elapsed() << "ms" << endl;
    piAprox = double(4 * numHits) / NUMDARTS;
    cout << " El valor de pi es: " << piAprox << endl;
    cout << cont << endl;
    return 0;
}

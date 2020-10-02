/* C++ program for estimation of Pi using Monte 
   Carlo Simulation */
#include <bits/stdc++.h>
#include "../timer.hh"
  
// Defines precision for x and y values. More the 
// interval, more the number of significant digits 
#define INTERVAL 1000
using namespace std; 
  
int main() 
{ 
    int interval, i; 
    double rand_x, rand_y, origin_dist, pi; 
    int circle_points = 0, square_points = 0; 
  
    // Initializing rand() 
    srand(time(NULL)); 
  
    // Total Random numbers generated = possible x 
    // values * possible y values
    Timer t;
    for (i = 0; i < (INTERVAL * INTERVAL); i++) { 
        // Randomly generated x and y values 
        rand_x = double(rand() % (INTERVAL + 1)) / INTERVAL; 
        //cout << "aleatorio x " << rand_x;
        rand_y = double(rand() % (INTERVAL + 1)) / INTERVAL; 
   		//cout << "aleatorio y " << rand_y;
        // Distance between (x, y) from the origin 
        origin_dist = rand_x * rand_x + rand_y * rand_y; 
        // Checking if (x, y) lies inside the define 
        // circle with R=1
        //cout << origin_dist;
        if (origin_dist <= 1) 
            circle_points++; 
        // Total number of points generated 
        square_points++; 
        // estimated pi after this iteration 
        pi = double(4 * circle_points) / square_points; 
        // For visual understanding (Optional) 
        /* cout << i << rand_x << " " << rand_y << " " << circle_points 
             << " " << square_points << " - " << pi << endl << endl; */ 
    }
    cout << "Tiempo de ejecución: " << t.elapsed() << "ms" << endl;
    // Final Estimated Value 
    cout << "\nFinal Estimation of Pi = " << pi << endl; 
  
    return 0; 
} 

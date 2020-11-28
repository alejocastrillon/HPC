#include <iostream>
#include <stdlib.h>

using namespace std;


void display(bool* rails, int railsNumber) {
    for (int i = 0; i < railsNumber; i++)
    {
        if (rails[i])
        {
            cout << "X";
        }
        else
        {
            cout << "_";
        }
    }
    cout << endl;
}

void updateTime(bool* targetIteration, bool* nextIteration, int railsNumber) {
    for (int i = 0; i < railsNumber; i++)
    {
        targetIteration[i] = nextIteration[i];
    } 
}

void nextIteration(bool* actualIteration, int railsNumber) {
    bool nextIteration[railsNumber];
    for (size_t i = 0; i < railsNumber; i++)
    {
        if (actualIteration[i])
        {
            if (i == railsNumber - 1)
            {
                nextIteration[i] = actualIteration[0];
            }
            else
            {
                nextIteration[i] = actualIteration[i + 1];
            }
            
        }
        else
        {
            if (i == 0)
            {
                nextIteration[i] = actualIteration[railsNumber - 1];
            }
            else
            {
                nextIteration[i] = actualIteration[i - 1];
            }
        }
    }
    updateTime(actualIteration, nextIteration, railsNumber);
}

void initRails(bool* rails, int railsNumber) {
    for (int i = 0; i < railsNumber; i++)
    {
        rails[i] = rand() % 2;
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int railsNumber = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    bool rails[railsNumber];
    initRails(rails, railsNumber);
    display(rails, railsNumber);
    for (int i = 0; i < iterations; i++)
    {
        nextIteration(rails, railsNumber);
        display(rails, railsNumber);
    }
    return 0;
}
#include <iostream>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

void nextIteration(bool* actualIteration, bool* nextIteration, int numRanks,  int railsNumber) {
    for (size_t i = 1; i < railsNumber / (numRanks + 1); i++)
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
    int tagOne = 1;
    int tagTwo = 11;
    int myRank, numRanks, length;
    bool rails[railsNumber];
    bool senderRails[railsNumber];
    bool getterRails[railsNumber];
    bool resultRails[railsNumber];
    initRails(rails, railsNumber);
    display(rails, railsNumber);
    char hostname[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &numRanks);
    MPI_Get_processor_name(hostname, &length);
    double startTime = MPI_Wtime();
    MPI_Scatter(&rails[(myRank * railsNumber) / (numRanks + 1)], (railsNumber / numRanks), MPI_C_BOOL, &rails[1], (railsNumber / numRanks), MPI_C_BOOL, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    int previous = myRank - 1;
    int next = myRank + 1;
    if (previous < 0) {
        previous = numRanks - 1;
    }
    if (next == numRanks) {
        next = 0;
    }

    if (numRanks > 1) {
        MPI_Send(&senderRails[1], 1, MPI_C_BOOL, previous, tagOne * myRank, MPI_COMM_WORLD);
        MPI_Recv(&senderRails[railsNumber / (numRanks + 1)], 1, MPI_C_BOOL, next, tagOne * next, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Send(&senderRails[railsNumber / numRanks], 1, MPI_C_BOOL, next, tagTwo * myRank, MPI_COMM_WORLD);
        MPI_Recv(&senderRails[0], 1, MPI_C_BOOL, previous, tagTwo * previous, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    for (int i = 0; i < iterations; i++)
    {
        nextIteration(senderRails, getterRails, numRanks, railsNumber);
        previous = myRank - 1;
        next = myRank + 1;
        if (previous < 0) {
            previous = numRanks - 1;
        }
        if (next == numRanks) {
            next = 0;
        }
        if (numRanks > 1) {
            MPI_Send(&getterRails[1], 1, MPI_C_BOOL, previous, tagOne * myRank, MPI_COMM_WORLD);
            MPI_Recv(&getterRails[railsNumber / (numRanks + 1)], 1, MPI_C_BOOL, next, tagOne * next, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            MPI_Send(&getterRails[railsNumber / numRanks], 1, MPI_C_BOOL, next, tagTwo * myRank, MPI_COMM_WORLD);
            MPI_Recv(&getterRails[0], 1, MPI_C_BOOL, previous, tagTwo * previous, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        MPI_Barrier(MPI_COMM_WORLD);

        for (size_t i = 0; i < railsNumber / (numRanks + 2); i++) {
            senderRails[i] = getterRails[i];
        }

        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Gather(&getterRails[1], railsNumber / numRanks, MPI_C_BOOL, &resultRails[(railsNumber / numRanks) * (myRank + 1)], MPI_C_BOOL, 0, MPI_COMM_WORLD);
    resultRails[railsNumber + 1] = resultRails[1];
    resultRails[0] = resultRails[railsNumber];

    double endTime = MPI_Wtime();

    if (myRank == 0) {
        cout << endTime - startTime;
    }

    MPI_Finalize();
    return 0;
}
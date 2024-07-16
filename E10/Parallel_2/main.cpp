#include "function.h"     // Some functions
#include "random.h"       // Generation pseudo-random number
#include "TSP.h"          // Traveling salesman problem	
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) 
{
    int size, rank;                                     // Number of cores and their ranks
    MPI_Init(&argc, &argv);                             // Inizialized MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &size);               // Number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);               // Rank of process

    int n_travel = 3;                                 // Number of travels 
    int n_generation = 30000;                            // Number of generation

    double T_start = 0.001;                             // Min value of temperature
    double T_end =2.;                                   // Max value of temperature
    vector<double> temp = Temp(T_start, T_end, rank, size, n_travel);   // Vector of temperature

    TSP TSP(n_generation, n_travel, Read_position("cap_prov_ita.dat"), rank, size, temp);  // TSP with italian cities

    TSP.Evolution();    // Evolution TSP with cities on circumference

    MPI_Finalize();             // End MPI environment

    return 0;
}
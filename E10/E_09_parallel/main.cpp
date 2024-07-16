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

    int n_city = 34;                                    // Number of cities 
    int n_travel = 1;                                   // Number of travels 
    int n_generation = 2500;                             // Number of generation

    double T_start = 0.0001;                             // Min value of temperature
    double T_end =2.;                                   // Max value of temperature
    vector<double> temp = Temp(T_start, T_end, size);   // Vector of temperature

    // File output 
    string namefile_c = "c"; 
    string namefile_s = "s"; 

    TSP TSP_circ(n_generation, n_travel, sampled_circ(n_city), rank, size, temp[rank]);         // TSP with cities on circumference
    TSP TSP_square(n_generation, n_travel, sampled_square(n_city), rank, size, temp[rank]);     // TSP with cities inside square

    TSP_circ.Evolution(namefile_c);     // Evolution TSP with cities on circumference
    TSP_square.Evolution(namefile_s);   // Evolution TSP with cities inside square

    MPI_Finalize();     // End MPI environment

    return 0;
}
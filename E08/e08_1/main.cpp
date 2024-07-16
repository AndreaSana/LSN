#include "function.h"     // Some functions
#include "wavefunction.h" // Operations with wave function
#include "random.h"       // Generation pseudo-random number	
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    int M = 1e7;            // Number of total throwns
    int N = 100;            // Number of blocks
    int L = int(M / N);     // Throwns in each block
    int block_eq = 40;      // Number of blocks for equilibration
    Random rn;              // Pseudo-random number generator

    // Parameters mu and sigma 
    vector<vector<double>> parameters = 
    {
        {0., 1.},
        {0., 0.5},
        {1., 1.},
        {1., 0.5}
    };

    for (int k = 0; k < int(parameters.size()); k++)     // Loop over parameters' values
    {
        cout << "mu = " << parameters[k][0] << " sigma = " << parameters[k][1] << endl;     // Values of parameters
        Wavefunction wf(parameters[k][0], parameters[k][1]);                                // Wave function
        
        string namefile = "data_" + to_string(k);  // Name file to print data

        // File output <H>
        ofstream outfile(namefile + "_mean.dat");
        outfile << parameters[k][0] << endl;
        outfile << parameters[k][1] << endl;
   
        // File output coordinates
        ofstream outfile2(namefile + "_cord.dat");
        outfile2 << parameters[k][0] << endl;
        outfile2 << parameters[k][1] << endl;

        metropolis_algorithm(rn, wf, N, block_eq, L, namefile);     // Metropolis algorithm
    }

    return 0;
}
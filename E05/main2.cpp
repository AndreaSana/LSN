#include "funzioni.h"       // Some functions
#include "random.h"         // Generation pseudo-random number
#include "Posizione.h"      // Class position
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////
// This code calculats the mean of radial position for two wave fuctions with different repetitions in each block
/////////////////////////////////////////////////////

int main() 
{
    double step_1 = 1.22461;    // Step for uniformly trasition probability to have 50% of acceptation 1° wave fuctions
    double step_2 = 2.96875;    // Step for uniformly trasition probability to have 50% of acceptation 2° wave fuctions
    int M = 10e3;               // Number of repetitions
    int N = 100;                // Number of blocks
    int eq_block = 10;          // Block for equilibration

    // Loop over the number of repetitions
    while (M <= 10e8)
    {
        int L = int(M / N);     // Number of throws for block
        Random rn;              // Variable to generate pseudo-random

        // Output file
        ofstream sout("Data/data_steps_" + to_string(int(log10(L))) + ".dat");
        sout << "#Blocks mean_1 uncer_1 mean_2 uncer_2" << endl;    // Columns names

        // Variables to store values of radial distance of blocks
        double sum_1 = 0.;
        double sum_q_1 = 0.;
        double sum_2 = 0.;
        double sum_q_2 = 0.;

        // Inizialize positions
        Posizione x_1(0, 0, 0);
        Posizione x_2(0, 0, 0);

        for (int j = 0; j < N + eq_block; j++) // Loop over blocks
        {   
            // Variables to accumulate radial distance and acceptations in each block
            double accumulator_1 = 0.;
            double accumulator_2 = 0.;
            
            for (int k = 0; k < L; k++) // Loop over throws for each block + steps for equilibration
            {
                // Metropolis algorithm
                x_1 = metropolis(rn, x_1, 0, 0, step_1);
                x_2 = metropolis(rn, x_2, 1, 0, step_2);
                
                // Ignore non equilibrated steps
                if (j < eq_block) 
                    continue;

                // Add contributions of the radial distance
                accumulator_1 += x_1.GetR();
                accumulator_2 += x_2.GetR();
            }

            // Ignore non equilibrated steps
            if (j < eq_block)   
                continue;
            
            // Calculate mean
            accumulator_1 /= L; 
            accumulator_2 /= L; 

            // Sum the contribution of the block to the others
            sum_1 += accumulator_1;                         
            sum_q_1 += pow(accumulator_1, 2);       
            sum_2 += accumulator_2;                         
            sum_q_2 += pow(accumulator_2, 2);       

            // Print data
            sout << j - eq_block + 1 << " " << sum_1 / (j - eq_block + 1) <<  " " << errore(sum_1 / (j - eq_block + 1), sum_q_1 / (j - eq_block + 1), j - eq_block) << " " << sum_2 / (j - eq_block + 1) <<  " " << errore(sum_2 / (j - eq_block + 1), sum_q_2 / (j - eq_block + 1), j - eq_block) << endl;
        }

        sout.close();

        M *= 10;        // Increase number of repetitions for a 10 factor
    }

    return 0;
}
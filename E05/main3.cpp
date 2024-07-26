#include "funzioni.h"       // Some functions
#include "random.h"         // Generation pseudo-random number
#include "Posizione.h"      // Class position
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////
// This code calculats the mean of radial position for two wave fuctions with different starting points
/////////////////////////////////////////////////////

int main() 
{
    int M = 10e7;           // Number of repetitions
    int N = 100;            // Number of blocks
    int L = int(M / N);     // Number of throws for block
    int eq_block = 10;      // Block for equilibration

    double step_1 = 1.22461;    // Step for uniformly trasition probability to have 50% of acceptation 1° wave fuctions
    double step_2 = 2.96875;    // Step for uniformly trasition probability to have 50% of acceptation 2° wave fuctions

    vector<double> point_in = {10, 100, 1000};  // Distance for starting points

    for (int j = 0; j < int(point_in.size()); j++)      // Loop over starting positions
    {
        // Output files
        ofstream sout("Data/data_pos_" + to_string(j) + ".dat");                    // File mean position with different starting points
        sout << "#Blocks mean_1 uncer_1 mean_2 uncer_2 mean_3 uncer_3" << endl;     // Columns names
        ofstream sout_2("Data/data_path_" + to_string(j) + ".dat");                 // Positions in equilibration with different starting points
        sout_2 << "x_1 y_1 z_1 x_2 y_2 z_2 x_3 y_3 z_3" << endl;                    // Columns names
        
        Random rn;      // Variable to generate pseudo-random

        // Variables to store values of radial distance of blocks
        double sum_1 = 0.;
        double sum_q_1 = 0.;
        double sum_2 = 0.;
        double sum_q_2 = 0.;
        double sum_3 = 0.;
        double sum_q_3 = 0.;
                    
        // Inizialize positions
        Posizione x_1(point_in[j], 0, 0);
        Posizione x_2(point_in[j], 0, 0);
        Posizione x_3(0, 0, point_in[j]);
        
        for (int k = 0; k < N + eq_block; k++)  // Loop over blocks
        {               
            // Variables to accumulate radial distance in each block
            double accumulator_1 = 0.;
            double accumulator_2 = 0.;
            double accumulator_3 = 0.;
            
            for (int l = 0; l < L; l++)     // Loop over throws for each block + steps for equilibration
            {
                // Metropolis algorithm
                x_1 = metropolis(rn, x_1, 0, 0, step_1);
                x_2 = metropolis(rn, x_2, 1, 0, step_2);
                x_3 = metropolis(rn, x_3, 1, 0, step_2);

                // Ignore non equilibrated steps and print positions
                if (k < eq_block)
                {
                    if (l % 100 == 0)
                        sout_2 << x_1.GetX() << " " << x_1.GetY() << " " << x_1.GetZ() << " " << x_2.GetX() << " " << x_2.GetY() << " " << x_2.GetZ() << " " << x_3.GetX() << " " << x_3.GetY() << " " << x_3.GetZ() << endl;
                    continue;
                }

                // Add contributions of the radial distance
                accumulator_1 += x_1.GetR();
                accumulator_2 += x_2.GetR();
                accumulator_3 += x_3.GetR();
            }
                            
            // Ignore non equilibrated steps
            if (k < eq_block)
                continue;

            // Calculate mean
            accumulator_1 /= L; 
            accumulator_2 /= L; 
            accumulator_3 /= L; 
            
            // Sum the contribution of the block to the others
            sum_1 += accumulator_1;                         
            sum_q_1 += pow(accumulator_1, 2);       
            sum_2 += accumulator_2;                         
            sum_q_2 += pow(accumulator_2, 2);       
            sum_3 += accumulator_3;                         
            sum_q_3 += pow(accumulator_3, 2);       

            // Print data
            sout << k - eq_block + 1 << " " << sum_1 / (k - eq_block + 1) <<  " " << errore(sum_1 / (k - eq_block + 1), sum_q_1 / (k - eq_block + 1), k - eq_block) << " " << sum_2 / (k - eq_block + 1) <<  " " << errore(sum_2 / (k - eq_block + 1), sum_q_2 / (k - eq_block + 1), k - eq_block) << " " << sum_3 / (k - eq_block + 1) <<  " " << errore(sum_3 / (k - eq_block + 1), sum_q_3 / (k - eq_block + 1), k - eq_block) << endl;
        }
        sout.close();
    } 
    
    return 0;
}

#include "funzioni.h"     	// Some functions
#include "random.h"       	// Generation pseudo-random number
#include "Posizione.h" 		// Class position
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////
// This code calculats the mean of radial position for two wave fuctions and their acceptation. Also finds the step of the uniform transition probability and the std. dev. of the gaussian trasition probability in order to obtain 50% of acceptance
/////////////////////////////////////////////////////

int main() 
{
	int M = 10e7; 			// Number of repetitions
	int N = 100; 			// Number of blocks
	int L = int(M / N); 	// Number of throws for block
	int eq_block = 10;		// Block for equilibration
	
	for (int i  = 0; i < 2; i++)  // Loop over the type of wavefuctions
	{
		// Print step and std. dev. to have 50% of acceptation 
		//cout << "Funzione d'onda #" << i + 1 << endl;
		//cout << "Uniform transition probability" << endl;
		double step = rule_50(i, 0); 	// Step for uniformly trasition to have 50% of acceptation
		//cout << "Gaussian transition probability" << endl;
		double sigma = rule_50(i, 1); 	// Std. dev. for gaussian trasition to have 50% of acceptation

		// Output file
		ofstream sout("Data/r_" + to_string(i) + ".dat");
		sout << "#Blocks mean_unif uncer_unif mean_gaus uncer_gaus mean_acc_unif uncer_acc_unif mean_acc_gaus uncer_acc_gaus" << endl; 	// Columns names
		
		Random rn;		// Variable to generate pseudo-random

		// Variables to store values of radial distance of blocks
		double sum_unif = 0.;
		double sum_q_unif = 0.;
		double sum_gaus = 0.;
		double sum_q_gaus = 0.;

		// Variables to store values of acceptations of blocks
		double sum_acc_unif = 0.;
		double sum_q_acc_unif = 0.;
		double sum_acc_gaus = 0.;
		double sum_q_acc_gaus = 0.;

		for (int j = 0; j < N + eq_block; j++)		// Loop over blocks
		{	
			// Inizialize positions
			Posizione x_unif(0, 0, 0);
			Posizione x_gaus(0, 0, 0);

			// Variables to accumulate radial distance and acceptations in each block
			double accumulator_unif = 0.;
			double accumulator_gaus = 0.;
			double accumulater_acc_unif = 0;
			double accumulater_acc_gaus = 0;
			
			for (int k = 0; k < L; k++)  // Loop over throws for each block + steps for equilibration
			{
				// Metropolis algorithm
				x_unif = metropolis(rn, x_unif, i, 0, step, accumulater_acc_unif);
				x_gaus = metropolis(rn, x_unif, i, 1, sigma, accumulater_acc_gaus);

				// Ignore non equilibrated steps
				if (j < eq_block) 	
					continue;

				// Add contributions of the radial distance
				accumulator_unif += x_unif.GetR();
				accumulator_gaus += x_gaus.GetR();
			}

			// Ignore non equilibrated steps
			if (j < eq_block) 	
				continue;

			// Calculate mean
			accumulator_unif /= L;	
			accumulator_gaus /= L;	
			accumulater_acc_unif /= L;	
			accumulater_acc_gaus /= L;	

			// Sum the contribution of the block to the others
			sum_unif += accumulator_unif;											
			sum_q_unif += pow(accumulator_unif, 2);						
			sum_gaus += accumulator_gaus;											
			sum_q_gaus += pow(accumulator_gaus, 2);						 
			sum_acc_unif += accumulater_acc_unif;							
			sum_q_acc_unif += pow(accumulater_acc_unif, 2);		
			sum_acc_gaus += accumulater_acc_gaus;							
			sum_q_acc_gaus += pow(accumulater_acc_gaus, 2);		

			// Print data
			sout << j - eq_block + 1 << " " << sum_unif / (j - eq_block + 1) <<  " " << errore(sum_unif / (j - eq_block + 1), sum_q_unif / (j - eq_block + 1), j - eq_block) << " " << sum_gaus / (j - eq_block + 1) <<  " " << errore(sum_gaus / (j - eq_block + 1), sum_q_gaus / (j - eq_block + 1), j - eq_block) << " " << sum_acc_unif / (j - eq_block + 1) <<  " " << errore(sum_acc_unif / (j - eq_block + 1), sum_q_acc_unif / (j - eq_block + 1), j - eq_block) << " " << sum_acc_gaus / (j - eq_block + 1) <<  " " << errore(sum_acc_gaus / (j - eq_block + 1), sum_q_acc_gaus / (j - eq_block + 1), j - eq_block) << endl;
		}

		sout.close();
	}
	
	
	return 0;
}
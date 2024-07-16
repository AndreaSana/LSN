#include "FunzioneBase.h" // Function to integrate
#include "funzioni.h"     // Some functions
#include "random.h"       // Generation pseudo-random number
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
	int M = 1e6;    		// Number of throws
	int N = 100;       		// Number of blocks
	int L = int(M / N); 	// Number of throws for block
	Random rn;    			// Variable to generate pseudo-random number
	
	// Extremes of integration
	double x_max = 1.;
	double x_min = 0.;

	// Cosine parameters k * cos(w * x + phi)
	double k = M_PI / 2;		
	double w = M_PI / 2;
	double phi = 0.;
	Coseno f(k, w, phi); 		// Function initialization

	// Polinomial parameters k_2 * (a + b * x + c * x^2)
	double k_2 = 2;
	double a = 1;
	double b = -1;
	double c = 0;
	Pol2 p(k_2, a, b, c);  	// Function initialization

	// File output
	ofstream outfile("data.dat"); 
	outfile << "blocchi mean devstd mean_imp devstd_imp" << endl; 	// Name of columns

	double sum = 0;  		// Sum of block contributions uniform sampling
	double sum_q = 0;		// Square sum of block contributions uniform sampling 
	double sum_2 = 0; 		// Sum of block contributions importance sampling 
	double sum_q_2 = 0;		// Square sum of block contributions importance sampling 

	for (int i = 0; i < N; i++) 		// Loop over number of blocks
	{
		double I = 0; 		// Integral value uniform sampling
		double I_2 = 0;		// Integral value importance sampling

		for (int j = 0; j < L; j++) 	// Loop over each block
		{
			// Uniform sampling
			I += f.Eval(rn.Rannyu(x_min, x_max)); 	// Evaluete integral uniform sampling
			
			// Importance sampling
			double x = sqrt(1 - rn.Rannyu(x_min, x_max)) + 1; 	// Generate pseudo-random number with p(x) = 2(1-x) with x€[0, 1)
			I_2 += f.Eval(x)/p.Eval(x); 						// Evaluete integral importance sampling
		}

		I = I / L * (x_max - x_min); 	// Value of integral in each block uniform sampling
		I_2 /= L; 						// Value of integral in each block importance sampling

		sum += I; 						// Sum the contribution of the block uniform sampling
		sum_q += pow(I, 2);				// Sum the square contribution of the block uniform sampling
		sum_2 += I_2;					// Sum the contribution of the block uniform sampling
		sum_q_2 += pow(I_2, 2);			// Sum the square contribution of the block uniform sampling


		// Print data
		outfile << i + 1 << " " << sum / (i + 1) << " "	<< errore(sum / (i + 1), sum_q / (i + 1), i + 1) << " " << sum_2 / (i + 1) << " " << errore(sum_2 / (i + 1), sum_q_2 / (i + 1), i + 1) << endl;		
	}

	outfile.close(); 		// Close file output

	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"		// Generation pseudo-random number
#include "funzioni.h" 	// Some functions

using namespace std;

int main ()
{
// Point 1 and 2
	
	int M = 1e7; 		// Number of throws
	int N = 100; 		// Number of blocks
	int L = int(M/N); 	// Number of throws for block
	
	Random rnd; 		// Create a variable to generate pseudo-random numbers

	ofstream outFile ("data.dat"); 							// File to save data
	outFile << "#blocchi media err var var_err" << endl; 	// Columns names

	double somma = 0.; 		// Mean throw blocks
	double somma_2 = 0.; 	// Square mean throw blocks
	double inc = 0.; 		// Variance throw blocks 
	double inc_2 = 0.; 		// Square variance throw blocks 
	
	for (int i = 0; i < N; i++) 		// Loop over blocks
	{	
		double somma_blocco = 0.; 	// Mean throw single block
		double var_blocco = 0.; 	// Variance throw single blocks 

		for (int j = 0; j < L; j++) 	// Loop over throws for block
		{
			double x = rnd.Rannyu(); 			// Generation psudo-random number
			somma_blocco += x; 					// Add to mean
			var_blocco += pow(x - 0.5, 2); 		// Add to variance
		}

		somma_blocco /= L; 		// Mean of block
		var_blocco /= L; 		// Variance of block
		
		// Add contribution of the new block to the olds
		somma += somma_blocco; 
		somma_2 += pow(somma_blocco, 2);
		inc += var_blocco;
		inc_2 += pow(var_blocco, 2);

		// Print data making mean on the number of block considered (i+1)
		outFile << i + 1 << " " << somma / (i + 1) <<  " " << errore(somma / (i + 1), somma_2 / (i + 1), i) <<  " " << inc / (i + 1) <<  " " << errore(inc / (i + 1), inc_2 / (i + 1), i) << endl;
	}

	outFile.close();

// Point 3

	M = 100; 			// Number of subintervals 
	N = 1e4; 			// Number of throws for repetitions 
	int R = 1e4; 		// Number of repetitions

	ofstream outFile2 ("data2.dat"); 			// File to save data
	outFile2 << "#ripetizione chi_2 " << endl; 	// Column names

	for (int i = 0; i < R; i++) 				// Loop over the repetitions
	{
		double chi_2 = 0; 						// Chi square
		vector<int> n(N, 0); 					// Array which counts the number of throws in a subinterval
		
		for (int j = 0; j < N; j++) 			// Loop over number of throws	
			n[floor(rnd.Rannyu() * M)]++; 		// Increase the counter of that subinterval where the pseudo-random number between [0;1) falls  
		
		// Calcolate chi square
		for (int j = 0; j < M; j++) 	// Loop over the number of subintervals
			chi_2 += pow(n[j] - N / M, 2);		

		chi_2 /= N / M;

		outFile2 << i + 1 << " " << chi_2 << endl; // Print chi square
	}
	
	outFile.close();
	
	return 0;
}
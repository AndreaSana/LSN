#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h" 	// Generation pseudo-random number
#include "funzioni.h" 	// Some functions

using namespace std;

int main ()
{
	double d = 1.5; 		// Distance between lines 
	double L = 1.; 			// Lenght needle
	int M = 1e7; 			// Number throws
	int N = 100; 			// Number blocks
	int D = int(M/N); 		// Number throws for block
	double mean = 0.; 		// Mean blocks
	double mean_2 = 0.; 	// Square mean blocks

	// File to print data
	ofstream outfile("data.dat"); 
	outfile << "#blocchi mean dev" << endl;
	
	Random rnd; 			// Create a variable to generate pseudo-random numbers

	for (int i = 0; i < N; i++) 		// Loop over blocks
	{
		double pi = 0.; 				// Number of hit

		for (int j = 0; j < D; j++) 	// Loop over throw in each block
		{
			double c = rnd.Rannyu(0., d);	 // Position center of needle between lines
			double x, y; 					 // Position x and y
			
			// Loop to have the point in the unit circle
			do  
				{
					x = rnd.Rannyu();				
					y = rnd.Rannyu();			
				}
			while (sqrt(x * x + y * y) > 1);	
			
			double distance = L / 2. * y / sqrt(x * x + y * y);  	// Projection onto the row axis
			
			if (c - distance <= 0. || c + distance >= d)	 		// Check if the needle cross lines
				pi++;			
		}

		pi = 2. * L * D / (d * pi); 	// Calculate pi

		mean += pi; 			// Mean of the block
		mean_2 += pow(pi, 2); 	// Square mean of block

		// Print data
		outfile << i + 1 << " " << mean / (i +1) <<  " " << errore(mean / (i+1), mean_2 / (i+1), i) << endl; 
	}

	return 0;
}
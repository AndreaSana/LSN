#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h" 	// Generation pseudo-random number

using namespace std;

int main ()
{
	int M = 1e4; 									// Number of attempts
	vector<int> N = {1, 2, 10, 100}; 				// Number of pseudo-random number used
	vector<string> name = {"unif", "exp", "CL"}; 	// Name of the distribution

	double lambda = 1.; 							// Costant for exponential distribution
	double mu = 0.; 								// Costant for Cauchy-Lorentz distribution
	double gamma = 1.; 								// Costant for Cauchy-Lorentz distribution

	for (int k = 0; k < 3; k++) 					// Loop over the 3 distribution
	{
		// File to save data
		string filename = "data_" + name[k] + ".dat"; 
		ofstream outfile(filename);
		
		Random rnd; 	// Create a variable to generate pseudo-random numbers

		for (int i = 0; i < int(N.size()); i++) 	// Loop over the different numbers for the mean
		{
			outfile << to_string(N[i]); 			// Print number of throws used
			
			for (int j = 0; j < M; j++) 			// Loop over the attempts
			{
				double sum = 0.;					// Inizialization mean

				for (int l = 0; l < N[i]; l++) 		// Loop over the number of throws
				{						
					double x; 						// Pseudo-random number
					
					switch(k) 						// Generate number according to the correct distribution
					{
						case 0:
							x = rnd.Rannyu();
							break;
						case 1:
							x = rnd.Exp(lambda);
							break;
						case 2:
							x = rnd.CL(gamma, mu);
							break;
					}
						
					sum += x; 	// Add the contribute to the mean
				}

				outfile << " " << sum / N[i]; // Print mean
			}

			outfile << endl;
		}
		
		outfile.close();
	}
	
	return 0;
}
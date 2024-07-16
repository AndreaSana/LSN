#include "funzioni.h"     	// Some functions
#include "random.h"       	// Generation pseudo-random number
#include "Posizione.h" 		// Class position
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////
// This code gives data to plot the positions of two wave fuctions
/////////////////////////////////////////////////////

int main() 
{
	int M = 10e4;					// Number of repetitions
	int eq_step = 100; 				// Steps to reach equilibration
	
	for (int i  = 0; i < 2; i++)  	// Loop over the wave fuctions
	{
		// Choose step according to the wave fuctions to have 50% of acceptation
		double step;  
		
		if (i == 0)
			step = 1.22461;
		if(i == 1)
			step = 2.96875;

		// output file
		ofstream sout("data_graf_" + to_string(i) + ".dat");
		sout << "x y z R" << endl;
		
		Random rn;				// Variable to generate pseudo-random
		Posizione x(0, 0, 0);  	// Inizialize position
		
		for (int j = 0; j < M; j++)		// Loop over repetitions
		{		
			x = metropolis(rn, x, i, 0, step); 	// Metropolis algorithm
			sout << x.GetX() << " " << x.GetY() << " " << x.GetZ() << " " << x.GetR()<< endl;  // Print coordinates
		}
		sout.close();
	}
	return 0;
}
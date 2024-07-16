#include "funzioni.h"     	// Some functions
#include "random.h"       	// Generation pseudo-random number
#include "Posizione.h" 		// Class position
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
	// Point 1 e 2
	int M = 1e4; 					// Number of repetitions
	int N = 100; 					// Number of blocks
	int L = int(M / N); 			// Number of throws for block
	int n = 100; 					// Number of step
	Random rn;						// Variable to generate pseudo-random
	double a = 1; 					// Lattice constant
	vector<Posizione> p_d(M);		// Array position of M discrete random walks 
	vector<Posizione> p_c(M);		// Array position of M continuous random walks
	
	// File to save data at each step
	ofstream outfile("steps.dat"); 	 
	outfile << "step mean_d devstd_d mean_c devstd_c" << endl;  // Name of columns
	outfile << "0 0 0 0 0" << endl; 							// Data at t = 0
	
	// Print coordinates of one random walk
	ofstream outfile2("rw.dat"); 	 
	outfile2 << "x_d y_d z_d x_c y_c z_c" << endl;  			// Name of columns
	outfile2 << "0 0 0 0 0 0" << endl;

	// Print coordinates 1° step continuous random walks
	ofstream outfile3("first_step.dat"); 	 
	outfile3 << "x_c y_c z_c" << endl;  			// Name of columns

	for (int i = 0; i <= n; i++) 			// Loop over the number of step
	{
		double sum_d = 0;		// Sum of block contributions discrete RW
		double sum_q_d = 0;		// Square sum of block contributions discrete RW
		double sum_c = 0;		// Sum of block contributions continuous RW
		double sum_q_c = 0;		// Square sum of block contributions continuous RW
		
		for (int j = 0; j < N; j++)			// Loop over the number oh blocks
		{
			double r_d = 0;  		// Mean square displacement discrete RW
			double r_c = 0;			// Mean square displacement continuous RW
			
			for (int k = 0; k < L; k++)  	// Loop over the random walks in each block
			{
				RW3d_d(a, p_d[j*N + k], rn);  					// Update position discrete RW
				r_d += pow(p_d[j*N + k].Distanza(0,0,0), 2);  	// Add contribution of new position discrete RW

				RW3d_c(a, p_c[j*N + k], rn); 					// Update position continuous RW
				r_c += pow(p_c[j*N + k].Distanza(0,0,0), 2); 	// Add contribution of new position continuous RW
			
			// Print coordinates 1° step
			if(i==0)
				outfile3 << p_c[j*N + k].GetX() << " " << p_c[j*N + k].GetY() << " " << p_c[j*N + k].GetZ() << endl; 
			}
			
			r_d = sqrt(r_d / L);  		// Calculate root of mean of each block discrete RW
			r_c = sqrt(r_c / L);			// Calculate root of mean of each block continuous RW
			
			sum_d += r_d;							// Sum the contribution of the block discrete RW
			sum_q_d += pow(r_d, 2);		// Sum the square contribution of the block discrete RW
			sum_c += r_c;							// Sum the contribution of the block continuous RW
			sum_q_c += pow(r_c, 2);		// Sum the square contribution of the block continuous RW
		}

		sum_d /= N; 		// Mean of the blocks discrete RW
		sum_q_d /= N;		// Square mean of the blocks discrete RW
		sum_c /= N;   	  	// Mean of the blocks continuous RW
		sum_q_c /= N; 	  	// Square mean of the blocks continuous RW
		
		outfile << i + 1 << " " << sum_d << " " << errore(sum_d, sum_q_d, N) << " " << sum_c << " " << errore(sum_c, sum_q_c, N) << endl;   	// Print data
	
		// Print coordinates of the 1° random walk
		outfile2 << p_d[0].GetX() << " " << p_d[0].GetY() << " " << p_d[0].GetZ() << " " << p_c[0].GetX() << " " << p_c[0].GetY() << " " << p_c[0].GetZ() << endl; 
			
	}
	
	// Close files output
	outfile.close();  
	outfile2.close();  	
	outfile3.close();  	

	return 0;
}
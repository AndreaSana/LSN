#include "funzioni.h"     // Some functions
#include "random.h"       // Generation pseudo-random number	
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{

	double T = 1.;  			// Delivery time
	double t = 0.; 				// Time
	double K = 100.;			// Strike price
	double S_0 = 100.; 			// Asset price at t = 0
	double r = 0.1;  			// Risk-free interest rate:
	double sigma = 0.25; 		// Volatility
	int n_discretized = 100;  	// Number of intervals for discretized GBM path
	
	ofstream outfile_c("data_C.dat"); 		// Output file "call"
	ofstream outfile_p("data_P.dat"); 		// Output file "put"
	outfile_c << "block mean_dir devstd_dir mean_dis devstd_dis" <<  endl; 	// Columns name
	outfile_p << "block mean_dir devstd_dir mean_dis devstd_dis" <<  endl; 	// Columns name

	int M = 1e7; 						// Number of repetitions
	int N = 100; 						// Number of blocks
	int L = int(M / N); 				// Number of throws for block

	Random rn;							// Variable to generate pseudo-random
	double sum_p_direct = 0;			// Sum of block contributions "call"
	double sum_q_p_direct = 0;			// Square sum of block contributions "call"
	double sum_c_direct = 0;			// Sum of block contributions "put"
	double sum_q_c_direct = 0;			// Square sum of block contributions "put"
	double sum_p_discretized = 0;		// Sum of block contributions "call"
	double sum_q_p_discretized = 0;		// Square sum of block contributions "call"
	double sum_c_discretized = 0;		// Sum of block contributions "put"
	double sum_q_c_discretized = 0;		// Square sum of block contributions "put"
	
	for (int i = 0; i < N; i++) 	 	// Loop over blocks
	{
		double C_direct = 0;    		// "Call" with direct method
		double P_direct = 0;			// "Put" with direct method
		double C_discretized = 0;		// "Call" with discretized method
		double P_discretized = 0;		// "Put" with discretized method
		
		for (int j = 0; j < L; j++) 	// Loop over throws in each blocks
		{
			C_direct += exp(- r * T) * max(0., S_direct(S_0, r, sigma, T, rn) - K);  		// Calculate and increment "call" value with direct method
			P_direct += exp(- r * T) * max(0., - S_direct(S_0, r, sigma, T, rn) + K); 		// Calculate and increment "put" value with direct method
			C_discretized += exp(- r * T) * max(0., S_discretized(S_0, r, sigma, T, n_discretized, rn) - K); 		// Calculate and increment "call" value with discretized method
			P_discretized += exp(- r * T) * max(0., - S_discretized(S_0, r, sigma, T, n_discretized, rn) + K); 		// Calculate and increment "put" value with discretized method
		}
		
		// Calculate mean in each block
		C_direct /= L; 				
		P_direct /= L; 				
		C_discretized /= L; 	
		P_discretized /= L; 	
		
		// Sum the contribution of the block
		sum_c_direct += C_direct; 											 
		sum_q_c_direct += pow(C_direct, 2); 						
		sum_p_direct += P_direct; 											
		sum_q_p_direct += pow(P_direct, 2); 						
		sum_c_discretized += C_discretized; 						
		sum_q_c_discretized += pow(C_discretized, 2);		
		sum_p_discretized += P_discretized; 						
		sum_q_p_discretized += pow(P_discretized, 2); 	
	
		// Print data of "call"
		outfile_c << i + 1 << " " << sum_c_direct / (i + 1) << " " << errore(sum_c_direct / (i + 1), sum_q_c_direct / (i + 1), i + 1) << " "  << sum_c_discretized / (i + 1) << " " << errore(sum_c_discretized / (i + 1), sum_q_c_discretized / (i + 1), i + 1) << endl;  
		
		// Print data of "put"
		outfile_p << i + 1 << " " << sum_p_direct / (i + 1) << " " << errore(sum_p_direct / (i + 1), sum_q_p_direct / (i + 1), i + 1) << " " << sum_p_discretized / (i + 1) << " " << errore(sum_p_discretized / (i + 1), sum_q_p_discretized / (i + 1), i + 1) << endl;
	}
	
	// Close file output
	outfile_c.close();  	
	outfile_p.close(); 
	
	return 0;
}
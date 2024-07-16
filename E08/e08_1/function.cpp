#include "function.h"

using namespace std;

// Function for mean square root
double errore(double mean, double mean_2, int n)
{
	if (n == 0)
		return 0;
	else
		return sqrt((mean_2 - pow(mean, 2)) / n);
}

// Metropolis step 
void metropolis_step(Random& rn, Wavefunction wf, double& x_prec, double delta)
{
    double x_new = x_prec + rn.Rannyu(-delta, delta);  				// New position

    double A = min(1., wf.Modq_wf(x_new) / wf.Modq_wf(x_prec));  	// Transition probability with |\psi(x)|^2 

	// Accept or reject new position
    if (rn.Rannyu() < A)
        x_prec = x_new;
}

// Metropolis step with acceptance
void metropolis_step(Random& rn, Wavefunction wf, double& x_prec, double delta, int& acceptance)
{
    double x_new = x_prec + rn.Rannyu(-delta, delta);				// New position

    double A = min(1., wf.Modq_wf(x_new) / wf.Modq_wf(x_prec)); 	// Transition probability with |\psi(x)|^2 

	// Accept  or reject new position
    if (rn.Rannyu() <= A)
    {
        x_prec = x_new;
        acceptance ++;
    }    
}

// Metropolis algorithm, value only last block
void metropolis_algorithm(Random& rn, Wavefunction wf, int N, int block_eq, int L, double& mean, double& unc)
{
	double x = 0.; 									// Initial position
	double delta = rule_50(wf); 					// Find step for uniformly transition probability to have 50% of acceptation

	for (int i  = 0; i < N + block_eq; i++)    		// Loop over blocks
    {
        double accum = 0.; 							// Accumulator within each block

        for (int j = 0; j < L; j++)     			// Loop over throwns in each block
        {
            metropolis_step(rn, wf, x, delta); 		// Metropolis step

            // Not consider value before equilibration
            if (i < block_eq)
                continue;
        
            accum += wf.Hamiltonian(x);     		// Add contribution
        } 

        // Not consider value before equilibration
        if (i < block_eq)
            continue;
                
        accum /= L;  	// Calculate mean of block

		// Add contribution data blocking
        mean += accum;  
        unc += pow(accum, 2);
    }

	// Mean and uncertantly with all blocks
	mean /= N;
	unc = errore(mean, unc / N, N);
}

// Metropolis algorithm, values each block
void metropolis_algorithm(Random& rn, Wavefunction wf, int N, int block_eq, int L, string namefile)
{
	double x = 0.; 					// Initial position
	double delta = rule_50(wf); 	// Find step for uniformly transition probability to have 50% of acceptation
	
    double sum = 0.;				// Accumulator value for blocks
    double sum_q = 0.; 				// Accumulator square value for blocks

	// File output 
    ofstream outfile(namefile + "_mean.dat", ios::app);
    outfile << "#blocks mean unc" << endl;  	// Name columns

	// File output 
    ofstream outfile2(namefile + "_cord.dat", ios::app);

	for (int i  = 0; i < N + block_eq; i++)     // Loop over blocks
    {
        double accum = 0.; 						// Accumulator within each block

        for (int j = 0; j < L; j++)    			// Loop over throwns in each block
        {
            metropolis_step(rn, wf, x, delta);	// Metropolis step

            // Not consider value before equilibration
            if (i < block_eq)
                continue;

			outfile2 << x << endl;  			// Print coordinates
        
            accum += wf.Hamiltonian(x);     	// Add contribution
        } 

        // Not consider value before equilibration
        if (i < block_eq)
            continue;
                
        accum /= L;  	// Calculate mean of block

		// Add contribution data blocking
        sum += accum;
        sum_q += pow(accum, 2);

		// Print values
    	outfile << i + 1 - block_eq << " " << sum / (i + 1 - block_eq) << " " << errore(sum / (i + 1 - block_eq), sum_q / (i + 1 - block_eq), i + 1 - block_eq) << endl;
    }

	// Close file 
	outfile.close();
	outfile2.close();
}

// Estimate acceptance
double calc_acceptance(double delta, Wavefunction wf)
{
    Random rn;    			// Pseudo-random number generator
    double x = 0.;   		// Initial position
	int N = 1e7;	    	// Number of steps
	int acceptance = 0;     // Number accepted

	// Loop over steps 
	for (int i = 0; i < N; i++)
		metropolis_step(rn, wf, x, delta, acceptance); 		// Metropolis step 

	return double(acceptance) / N; 		// Fraction of accepted steps
}

// Find step for uniformly trasition probability to have 50% of acceptation
double rule_50(Wavefunction wf)
{
	double delta_max = 10.;  								// Max value
	double delta_min = 0.;   								// Min value
	double accepted_max = calc_acceptance(delta_max, wf);  	// Acceptation with max value 
	double accepted_min = calc_acceptance(delta_min, wf);	// Acceptation with min value 
	double delta;											// Value to control
	double accepted; 										// Value of acceptation

	//cout << "Step_delta  |accepted - 0.5|" << endl; // Print table with value and relative acceptation

	// Loop to find the value to have 50% of acceptation
	while(abs(accepted - 0.5) > 10e-4 && abs(accepted_max - accepted_min) > 10e-4)  // Loop stops when the value goes under a fixed precision
	{
		delta = (delta_max + delta_min) / 2; 						// Mid point
		accepted = calc_acceptance(delta, wf); 						// Acceptation mid point
		//cout << delta << " " << abs(accepted - 0.5) << endl;		// Print value and acceptation

		// Find the new subinterval in which search between the one on the right and on the left of the mid point
		double accepted_1 = calc_acceptance((delta_min + delta) / 2, wf);
		double accepted_2 = calc_acceptance((delta_max + delta) / 2, wf);

		if (abs(accepted_1 - 0.5) < abs(accepted_2 - 0.5))
		{
			delta_max = delta;
			accepted_max = accepted;

		}
		else
		{
			delta_min = delta;
			accepted_min = accepted;
		}
	}
	
	//cout << "Step to have 50% acceptance: " << delta << endl << endl;  // Print value 50% of acceptation

	return delta;
}

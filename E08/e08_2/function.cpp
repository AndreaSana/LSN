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

	// Accept  or reject new position
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
	double x = 0.; 							   // Initial position
	double delta = rule_50(wf); 			   // Find step for uniformly transition probability to have 50% of acceptation

	for (int i  = 0; i < N + block_eq; i++)    // Loop over blocks
    {
        double accum = 0.; 					   // Accumulator within each block

        for (int j = 0; j < L; j++)            // Loop over throwns in each block
        {
            metropolis_step(rn, wf, x, delta); // Metropolis step

            // Not consider value before equilibration
            if (i < block_eq)
                continue;
        
            accum += wf.Hamiltonian(x);        // Add contribution
        } 

        // Not consider value before equilibration
        if (i < block_eq)
            continue;
                
        accum /= L;  // Calculate mean of block

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
	double delta = rule_50(wf);		// Find step for uniformly transition probability to have 50% of acceptation
	
    double sum = 0.;				// Accumulator value for blocks
    double sum_q = 0.; 				// Accumulator square value for blocks

	// File output 
    ofstream outfile(namefile + "_mean.dat");
    outfile << "#blocks mean unc" << endl;  		// Name columns

	// File output 
    ofstream outfile2(namefile + "_cords.dat");

	for (int i = 0; i < N + block_eq; i++)    // Loop over blocks
    {
        double accum = 0.; 					  // Accumulator within each block

        for (int j = 0; j < L; j++)           // Loop over throwns in each block
        {
            metropolis_step(rn, wf, x, delta);

            // Not consider value before equilibration
            if (i < block_eq)
                continue;

			outfile2 << x << endl;  		// Print coordinates
        
            accum += wf.Hamiltonian(x);     // Add contribution
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

	outfile.close();
	outfile2.close();
}

// Estimate acceptance
double calc_acceptance(double delta, Wavefunction wf)
{
    Random rn;    			// Pseudo-random number generator
    double x = 0.;   		// Initial position
	int N = 1e7;	    	// Number of steps
	int acceptance = 0;    	// Number accepted

	// Loop over steps 
	for (int i = 0; i < N; i++)
		metropolis_step(rn, wf, x, delta, acceptance); 	// Metropolis algorithm 

	return double(acceptance) / N; 						// Fraction of accepted steps
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
		delta = (delta_max + delta_min) / 2; 	 					// Mid point
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

// Simulated Annealing algorithm
vector<double> simul_annealing(Random& rn, Wavefunction& wf, double T_i, double T_f, double T_step, string namefile)
{
	int M = 1e5;     			// Number of total throwns
    int N = 100;        		// Number of blocks
	int L = int(M / N); 		// Throwns in each block
	int block_eq = 40;   		// Number of step for equilibration
    double T = T_i;  			// Current temperature

	double mean, unc;  											// Corrent mean and uncertainty
	metropolis_algorithm(rn, wf, N, block_eq, L, mean, unc);  	// Metropolis algorithm with original parameters

	double mean_best = mean; 			// Best value of cost function
	vector<double> best_parameters; 	// Best parameters that minimized the cost function

	// File output 
    ofstream outfile(namefile + ".dat");
    outfile << "beta mean unc mu sigma" << endl;  // Name columns

    while (T > T_f)       // Loop over temperature
    {
		// New parameters
		double mu = abs(wf.Get_mu() + rn.Rannyu(-1, 1) * 0.5 * T);
		double sigma = abs(wf.Get_sigma() + rn.Rannyu(-1, 1) * 0.25 * T);

		Wavefunction wf_new(mu, sigma); 										// New wave fuction
		double mean_new = 0., unc_new = 0.; 									// New mean and uncertainty
		metropolis_algorithm(rn, wf_new, N, block_eq, L, mean_new, unc_new); 	// Metropolis algorithm with new parameters

	    double A = min(1., exp(- 1. / T * (mean_new - mean)));  				// Transition probability with |\psi(x)|^2 

		// Accept or reject new position
		if (rn.Rannyu() < A)
		{
			// Update variables
			mean = mean_new;
			unc = unc_new;
			wf.Set_mu(wf_new.Get_mu());
			wf.Set_sigma(wf_new.Get_sigma());
		}
		
		// Print beta, mean, uncertainty, 
		outfile << 1. / T << " " << mean << " " << unc << " " << wf.Get_mu() << " " << wf.Get_sigma() << endl;

        T *= T_step; 	// Decrease temperature

		// Update best parameters
		if (mean < mean_best)
		{
			mean_best = mean;
			best_parameters = {wf.Get_mu(), wf.Get_sigma()};
		}
    }

    outfile.close();

	return best_parameters;
}
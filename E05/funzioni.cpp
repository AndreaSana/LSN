#include "funzioni.h"

// Calculate acceptance
double calc_accepted(int type_wf, int type_T, double step)
{
	Posizione x(0, 0, 0);
	Random rn;
	int N = 10e6;			// Number of steps
	double accepted = 0.;  	// Acceptance

	// Loop over steps 
	for (int i = 0; i < N; i++)
		x = metropolis(rn, x, type_wf, type_T, step, accepted); 	// Metropolis algorithm 

	return accepted / N; 	// Fraction of accepted steps
}

// Find step for uniformly trasition probability or std. dev. for gaussian trasition probability to have 50% of acceptation
double rule_50(int type_wf, int type_T)
{
	// Output file
	ofstream sout;
	sout.open("Data/accepted_" + to_string(type_wf) + "_" + to_string(type_T) + ".dat");  

	double max = 3.;  // Max value
	double min= 0.;   // Min value
	double accepted_max = calc_accepted(type_wf, type_T, max);  // Acceptation with max value 
	double accepted_min = calc_accepted(type_wf, type_T, min);	// Acceptation with min value 
	double step;		// Value to control
	double accepted; 	// Acceptation

	// Print table with value and relative acceptation
	sout << "STEP ACCEP" << endl;

	// Loop to find the value to have 50% of acceptation
	while(abs(accepted - 0.5) > 10e-4 && abs(accepted_max - accepted_min) > 10e-4)  // Loop stops when the value goes under a fixed precision
	{
		step = (max + min) / 2; 	 						// Mid point
		accepted = calc_accepted(type_wf, type_T, step); 	// Acceptation mid point

		sout << step << " " << abs(accepted) << endl;		// Print value and acceptation

		// Find the new subinterval in which search between the one on the right and on the left of the mid point
		double accepted_1 = calc_accepted(type_wf, type_T, (min + step) / 2);
		double accepted_2 = calc_accepted(type_wf, type_T, (max + step) / 2);

		if (abs(accepted_1 - 0.5) < abs(accepted_2 - 0.5))  // Choose the subinterval with the nearest value to 50%
		{
			max = step;
			accepted_max = accepted;

		}
		else
		{
			min = step;
			accepted_min = accepted;
		}
	}
	
	//cout << "Step per avere 50% di accettazione: " << step << endl << endl;  // Print value 50% of acceptation
	sout.close();  // Close file
	return step;
}

// Metropolis algorithm
Posizione metropolis (Random& rn, Posizione& x, int type_wf, int type_T, double& parameter)
{
	Posizione x_2;
	if (type_T == 0)  	    // New point uniformly distributed
	{
		x_2.SetX(x.GetX() + rn.Rannyu(-parameter, parameter));
		x_2.SetY(x.GetY() + rn.Rannyu(-parameter, parameter));
		x_2.SetZ(x.GetZ() + rn.Rannyu(-parameter, parameter));
	}
	else if (type_T == 1)   // New point gaussian distributed
	{
		x_2.SetX(x.GetX() + rn.Gauss(0., parameter));
		x_2.SetY(x.GetY() + rn.Gauss(0., parameter));
		x_2.SetZ(x.GetZ() + rn.Gauss(0., parameter));
	}
	else
	{
		cout << "Tipo probabilità di transizione non nota" << endl;		
		exit(1);
	}

	// Acceptance probability
	double A = min(1., norm(wave_function(x_2, type_wf)) / norm(wave_function(x, type_wf)));

	// Accept new point with probability A
	if (rn.Rannyu() <= A)
		return x_2;
	else
		return x;
}

// Metropolis algorithm with number of accepted trasitions
Posizione metropolis (Random& rn, Posizione& x, int type_wf, int type_T, double& parameter, double& acc)
{
	Posizione x_2;
	if (type_T == 0)			// New point uniformly distributed
	{
		x_2.SetX(x.GetX() + rn.Rannyu(-parameter, parameter));
		x_2.SetY(x.GetY() + rn.Rannyu(-parameter, parameter));
		x_2.SetZ(x.GetZ() + rn.Rannyu(-parameter, parameter));
	}
	else if (type_T == 1) 		// New point gaussian distributed
	{
		x_2.SetX(x.GetX() + rn.Gauss(0., parameter));
		x_2.SetY(x.GetY() + rn.Gauss(0., parameter));
		x_2.SetZ(x.GetZ() + rn.Gauss(0., parameter));
	}
	else
	{
		cout << "Tipo probabilità di transizione non nota" << endl;		
		exit(1);
	}
		
	// Acceptance probability
	double A = min(1., norm(wave_function(x_2, type_wf)) / norm(wave_function(x, type_wf)));
	
	// Accept new point with probability A
	if (rn.Rannyu() <= A)
	{
		acc ++; 		// Increase number of accepted trasitions
		return x_2;
	}
	else
		return x;
}

// Minimum between two numbers
double min(double a, double b)
{
	if (a > b)
		return b;
	else
		return a;
}

// Calculate wave_fuction according to type (0 for (1, 0, 0) quantum numbers and 1 for (2, 1, 0) quantum numbers)
double wave_function(Posizione& x, int& type)
{
	if (type == 0)
		return pow(a_0, -1.5) / sqrt(M_PI) * exp(-x.GetR());
	if (type == 1)
		return pow(a_0, -2.5) / 8 * sqrt(2. / M_PI) * x.GetR() * exp(-x.GetR() / 2.) * cos(x.GetPhi());
	else
	{
		cout << "Funzione d'onda non implementata" << endl;
		return -1;
	}
}

// Function for mean square root
double errore(double mean, double mean_2, int n)
{
	if (n == 0)
		return 0;
	else
		return sqrt((mean_2 - pow(mean, 2)) / n);
}

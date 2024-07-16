#include "funzioni.h"

// Function for mean square root
double errore(double mean, double mean_2, int n)
{
	if (n == 0)
		return 0;
	else
		return sqrt((mean_2 - pow(mean, 2)) / n);
}

// Direct sampling of final asset price 
double S_direct(double& S_0, double& mu, double& sigma, double& t, Random& rn) 
{
	return S_0 * exp((mu - 0.5 * pow(sigma, 2)) * t + sigma * rn.Gauss(0, t));
}

// Discretized sampling of final asset price 
double S_discretized(double& S_0, double& mu, double& sigma, double& t, int n, Random& rn) 
{
	double S = S_0;
	
	for (int i = 0; i < n; i++) // Loop on the interations
		S = S * exp((mu - 0.5 * pow(sigma, 2)) * t / n + sigma * rn.Gauss(0, 1) * sqrt(t / n)) ;
	
	return S;
}
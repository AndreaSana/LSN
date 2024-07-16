#include <iostream>
#include <cmath>
#include "random.h"

using namespace std;

double errore(double mean, double mean_2, int n);		// Function for mean square root
double S_direct(double& S_0, double& mu, double& sigma, double& t, Random& rn); 	// Direct sampling of final asset price 
double S_discretized(double& S_0, double& mu, double& sigma, double& t, int n, Random& rn); 	// Discretized sampling of final asset price 

#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>
#include "Posizione.h"
#include "random.h"

using namespace std;

const double a_0 = 0.0529e-9;	// Bohr radius in nm

Posizione metropolis (Random& rn, Posizione& x, int type_wf, int type_T, double& parameter, double& acc); 	// Metropolis algorithm with number of accepted trasitions
Posizione metropolis (Random& rn, Posizione& x, int type_wf, int type_T, double& parameter); 			    // Metropolis algorithm 
double accepted(int type_wf, int type_T, double step);                                                      // Calculate acceptance
double rule_50(int type_wf, int type_T);								                                    // Find step for uniformly trasition probability or std. dev. for gaussian trasition probability to have 50% of acceptation
double wave_function(Posizione& x, int& type);  				                                            // Calculate wave_fuction using quantum numbers
double min(double a, double b);										                            			// Minimum between two numbers
double errore(double mean, double mean_2, int n);				                                            // Function for mean square root

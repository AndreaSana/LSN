#ifndef __function_h__
#define __function_h__

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include "random.h"
#include "wavefunction.h"

using namespace std;

double errore(double mean, double mean_2, int n);                                                                       // Function for mean square root
void metropolis_step(Random& rn, Wavefunction wf, double& x_prec, double delta);                                        // Metropolis step
void metropolis_step(Random& rn, Wavefunction wf, double& x_prec, double delta, int& acceptance);                       // Metropolis algorithm with accptance
void metropolis_algorithm(Random& rn, Wavefunction wf, int N, int block_eq, int L, double& mean, double& unc);          // Metropolis algorithm, value only last block
void metropolis_algorithm(Random& rn, Wavefunction wf, int N, int block_eq, int L, string namefile);                    // Metropolis algorithm, values each block
double calc_acceptance(double delta, Wavefunction wf);                                                                  // Estimate acceptance
double rule_50(Wavefunction wf);                                                                                        // Find step for uniformly trasition probability to have 50% of acceptations
vector<double> simul_annealing(Random& rn, Wavefunction& wf, double T_i, double T_f, double T_step, string namefile);   // Simulated Annealing algorithm

#endif
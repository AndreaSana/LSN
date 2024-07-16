#include <iostream>
#include <cmath>
#include "Posizione.h"
#include "random.h"

using namespace std;

double errore(double& mean, double& mean_2, int& n);		// Function for mean square root
void RW3d_d(double& d, Posizione& p, Random& rn);		// Function for discrete 3D random walk
void RW3d_c(double& d, Posizione& p, Random& rn);		// Function for continue 3D random walk

#include "funzioni.h"

// Function for mean square root
double errore(double& mean, double& mean_2, int& n)
{
	if (n == 0)
		return 0;
	else
		return sqrt((mean_2 - pow(mean, 2)) / n);
}

// Function for discrete 3D random walk
void RW3d_d (double& d,  Posizione& p, Random& rn)
{
	int n = floor(rn.Rannyu(1, 7)); 	// Generate psuedo-random number between [1, 6]
	
	switch(n) 	// Make a specific shift according to n
	{
		case 1:
				p.SetX(p.GetX() + d);
				break;
		case 2:
				p.SetX(p.GetX() - d);
				break;
		case 3:
				p.SetY(p.GetY() + d);
				break;
		case 4:
				p.SetY(p.GetY() - d);
				break;
		case 5:
				p.SetZ(p.GetZ() + d);
				break;
		case 6:
				p.SetZ(p.GetZ() - d);
				break;
	}
}

// Function for continuous 3D random walk
void RW3d_c(double& d, Posizione& p, Random& rn)
{
	double phi = rn.Rannyu(0, 2. * M_PI);			// Generate pseudo-random number uniformly between (0, 2 * pi)
	double theta = acos(1. - 2. * rn.Rannyu());		// Generate pseudo-random number with p(x) = 0.5 * sin(x) with x€(0, 1]
	
	p.SetX(p.GetX() + d * cos(phi) * sin(theta)); 	// Set x coordinate
	p.SetY(p.GetY() + d * sin(phi) * sin(theta));	// Set y coordinate
	p.SetZ(p.GetZ() + d * cos(theta)); 				// Set z coordinate
}
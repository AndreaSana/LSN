#ifndef __Random__
#define __Random__

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

// This class contains functions for generating random numbers using the RANNYU algorithm
class Random {

private:
	int m1,m2,m3,m4,l1,l2,l3,l4,n1,n2,n3,n4;

protected:

public:
	// Default constructor
	Random();
	// Destructor
	~Random();
	// Method to set the seed for the RNG
	void SetRandom(int * , int, int);
	// Method to save the seed to a file
	void SaveSeed();
	// Method to generate a random number in the range [0,1)
	double Rannyu(void);
	// Method to generate a random number in the range [min,max)
	double Rannyu(double min, double max);
	// Method to generate a random number with a Gaussian distribution
	double Gauss(double mean, double sigma);
	// Method to generate a number from an exponential distribution y = lambda * exp(- lambda * x)
	double Exp(double lambda);
	// Method to generate a number from Cauchi-Lorentz distribution y = gamma * tan(M_PI * (x - 0.5)) + mu 
	double CL(double gamma, double mu);
	};

#endif // __Random__
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"

using namespace std;

// Default costructure
Random :: Random()
{
	int seed[4];
	int p1, p2;
	ifstream Primes("Primes");
	if (Primes.is_open())
	{
		Primes >> p1 >> p2 ;
	} 
	else 
		cerr << "PROBLEM: Unable to open Primes" << endl;
	Primes.close();

	ifstream input("seed.in");
	string property;
	if (input.is_open())
	{
		while ( !input.eof() )
		{
			input >> property;
			if( property == "RANDOMSEED" )
			{
					input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
					SetRandom(seed,p1,p2);
			}
		}
		input.close();
	}
	else cerr << "PROBLEM: Unable to open seed.in" << endl;
}

Random :: ~Random(){} // Default destructor, does not perform any action

// This function saves the current state of the random number generator to a file "seed.out"
void Random :: SaveSeed()
{
	 ofstream WriteSeed;
	 WriteSeed.open("seed.out");
	 if (WriteSeed.is_open())
	 {
			WriteSeed << "RANDOMSEED	" << l1 << " " << l2 << " " << l3 << " " << l4 << endl;;
	 } 
	 else 
		 cerr << "PROBLEM: Unable to open random.out" << endl;
	WriteSeed.close();
	return;
}

 // This function generates a random number from a Gaussian distribution with given mean and sigma
double Random :: Gauss(double mean, double sigma) 
{
	 double s=Rannyu();
	 double t=Rannyu();
	 double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
	 return mean + x * sigma;
}

// This function generates a random number in the range [min, max)
double Random :: Rannyu(double min, double max)
{
	 return min+(max-min)*Rannyu();
}

// This function generates a random number in the range [0,1)
double Random :: Rannyu(void)
{
	const double twom12=0.000244140625;
	int i1,i2,i3,i4;
	double r;

	i1 = l1*m4 + l2*m3 + l3*m2 + l4*m1 + n1;
	i2 = l2*m4 + l3*m3 + l4*m2 + n2;
	i3 = l3*m4 + l4*m3 + n3;
	i4 = l4*m4 + n4;
	l4 = i4%4096;
	i3 = i3 + i4/4096;
	l3 = i3%4096;
	i2 = i2 + i3/4096;
	l2 = i2%4096;
	l1 = (i1 + i2/4096)%4096;
	r=twom12*(l1+twom12*(l2+twom12*(l3+twom12*(l4))));

	return r;
}

// This function generates a random number with exponential distribution y = lambda * exp(- lambda * x)
double Random :: Exp(double lambda) 
{
	return - log(1- Rannyu()) / lambda;
}

// This function generates a random number with Cauchy-Lorentz distribution y = gamma * tan(M_PI * (x - 0.5)) + mu 
double Random :: CL(double gamma, double mu) 
{
	return gamma * tan(M_PI * (Rannyu() - 0.5)) + mu;
}

// This function sets the seed and parameters of the random number generator
void Random :: SetRandom(int * s, int p1, int p2)
{
	m1 = 502;
	m2 = 1521;
	m3 = 4071;
	m4 = 2107;
	l1 = s[0];
	l2 = s[1];
	l3 = s[2];
	l4 = s[3];
	n1 = 0;
	n2 = 0;
	n3 = p1;
	n4 = p2;

	return;
}
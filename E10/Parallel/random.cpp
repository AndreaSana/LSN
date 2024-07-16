#include "random.h"

using namespace std;

// Default constructor, does not perform any action
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

// Constructor with different primes
Random :: Random(const int& row)
{
	int seed[4];
	int p1, p2;
	ifstream Primes("Primes");
	int rank = -1; 	// Counter for rows
	do
	{
		rank++; // Increase row

		if (Primes.is_open())
		{
			Primes >> p1 >> p2 ;
		} 
		else 
			cerr << "PROBLEM: Unable to open Primes" << endl;
	}
	while(rank != row);

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

// Default destructor, does not perform any action
Random :: ~Random(){}

void Random :: SaveSeed(){
	 // This function saves the current state of the random number generator to a file "seed.out"
	 ofstream WriteSeed;
	 WriteSeed.open("seed.out");
	 if (WriteSeed.is_open()){
			WriteSeed << "RANDOMSEED	" << l1 << " " << l2 << " " << l3 << " " << l4 << endl;;
	 } else cerr << "PROBLEM: Unable to open random.out" << endl;
	WriteSeed.close();
	return;
}

// Get n_3
int Random :: Get_n3()
{
	return n3;
}

// Get n_4
int Random :: Get_n4()
{
	return n4;
}
	
// Set n_3
void Random :: Set_n3(const int& n)
{
	n3 = n;
}

// Set n_4
void Random :: Set_n4(const int& n)
{
	n4 = n;
}

double Random :: Gauss(double mean, double sigma) 
{
	 // This function generates a random number from a Gaussian distribution with given mean and sigma
	 double s=Rannyu();
	 double t=Rannyu();
	 double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
	 return mean + x * sigma;
}

double Random :: Rannyu(double min, double max){
	 // This function generates a random number in the range [min, max)
	 return min+(max-min)*Rannyu();
}

double Random :: Rannyu(void){
	// This function generates a random number in the range [0,1)
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

double Random :: Exp(double lambda) // y = lambda * exp(- lambda * x)
{
	return - log(1- Rannyu()) / lambda;
}

double Random :: CL(double gamma, double mu) // y = gamma * tan(M_PI * (x - 0.5)) + mu 
{
	return gamma * tan(M_PI * (Rannyu() - 0.5)) + mu;
}

void Random :: SetRandom(int * s, int p1, int p2){
	// This function sets the seed and parameters of the random number generator
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
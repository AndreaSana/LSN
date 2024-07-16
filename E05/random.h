#ifndef __Random__
#define __Random__

// This class contains functions for generating random numbers using the RANNYU algorithm
class Random 
{

	private:
		int m1,m2,m3,m4,l1,l2,l3,l4,n1,n2,n3,n4;

	protected:

	public:
		Random(); // Default constructor
		~Random(); // Destructor
		void SetRandom(int * , int, int); // Method to set the seed for the RNG
		void SaveSeed(); // Method to save the seed to a file
		double Rannyu(void); // Method to generate a random number in the range [0,1)
		double Rannyu(double min, double max); // Method to generate a random number in the range [min,max)
		double Gauss(double mean, double sigma); // Method to generate a random number with a Gaussian distribution
		double Exp(double lambda); // Method to generate a number from an exponential distribution y = lambda * exp(- lambda * x)
		double CL(double gamma, double mu); // Method to generate a number from Cauchi-Lorentz distribution y = gamma * tan(M_PI * (x - 0.5)) + mu 
};

#endif // __Random__
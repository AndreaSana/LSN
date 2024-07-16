#include "wavefunction.h"

using namespace std;

// Default constructor
Wavefunction :: Wavefunction ()
{
    _mu = 0.;
    _sigma = 1.;
}

// Constructor
Wavefunction :: Wavefunction (double mu, double sigma)
{
    _mu = mu;
    _sigma = sigma;
}

// Constructor
Wavefunction :: Wavefunction (vector<double> parameters)
{
    _mu = parameters[0];
    _sigma = parameters[1];
}

// Destructor
Wavefunction :: ~Wavefunction() {} 

// Calculate gaussian part of wavefunction
double Wavefunction :: Gaus (double x, bool sign)
{
    double mu = Get_mu();

    if (sign)
        mu *= -1;

    return exp(-pow(x + mu, 2) / (2 * pow(_sigma, 2)));
}

// Calculate wave function
double Wavefunction :: w_f(double x)
{
    return Gaus (x, 0) + Gaus (x, 1);
}

// Calculate wave function square module
double Wavefunction :: Modq_wf(double x)
{
    return pow(w_f(x), 2);
}

// Calculate analytically  second derivative
double Wavefunction :: Der_2 (double x)
{
    return (pow((x - _mu) / pow(_sigma, 2), 2) - pow(_sigma, -2)) * Gaus(x, 1) + (pow((x + _mu) / pow(_sigma, 2), 2) - pow(_sigma, -2)) * Gaus(x, 0);
}

// Calculate cinetic part of H
double Wavefunction :: Kinetic (double x) 
{
    return - pow(_h_bar, 2) / (2. * _m) * Der_2(x) / w_f(x);
}
    
// Calculate potentail part of H 
double Wavefunction :: Potential (double x) 
{
    return pow(x, 4) - 5. / 2. * pow(x, 2);
}

// Calculate Hamiltonian
double Wavefunction :: Hamiltonian(double x)
{
    return Kinetic(x) + Potential(x);
}

// Set mu
void Wavefunction :: Set_mu(double mu)
{
    _mu = mu;
}

// Get mu
double Wavefunction :: Get_mu()
{
    return _mu;
}

// Set sigma
void Wavefunction :: Set_sigma(double sigma)
{
    _sigma = sigma;
}

// Get sigma
double Wavefunction :: Get_sigma()
{
    return _sigma;
}

void Wavefunction :: Set_parameters(vector<double> parameters)
{
    _mu = parameters[0];
    _sigma = parameters[1];
}

// Get parameters
vector<double> Wavefunction :: Get_parameters()
{
    vector<double> parameters= {_mu, _sigma};
    return parameters;
}
#ifndef __Wavefunction_h__
#define __Wavefunction_h__

#include <iostream>
#include <complex>
#include <cmath> 
#include <vector>

using namespace std;

// Class to describe the wave function of the exercise
class Wavefunction
{
    public:
    Wavefunction ();                                    // Default constructor
    Wavefunction (double mu, double sigma);             // Constructor
    Wavefunction (vector<double> parameters);           // Constructor
    ~Wavefunction ();                                   // Destructor

    double Gaus (double x, bool sign);                  // Calculate gaussian part of wavefunction
    double w_f(double x);                               // Calculate wave function
    double Modq_wf (double x);                          // Calculate wave function square module
    double Der_2 (double x);                            // Calculate second derivative
    double Kinetic (double x);                          // Calculate cinetic part of H
    double Potential (double x);                        // Calculate potentail part of H
    double Hamiltonian(double x);                       // Calculate Hamiltonian

    void Set_mu(double mu);                             // Set mu
    double Get_mu();                                    // Get mu
    void Set_sigma(double mu);                          // Set sigma
    double Get_sigma();                                 // Get sigma
    void Set_parameters(vector<double> parameters);     // Set parameters
    vector<double> Get_parameters();                    // Get parameters

    private:
        double _sigma, _mu;                             // Mean and variace of gaussian function
        double _h_bar = 1., _m = 1.;                    // h bar e mass
};

#endif
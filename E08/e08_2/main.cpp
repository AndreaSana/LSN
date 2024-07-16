#include "function.h"     // Some functions
#include "wavefunction.h" // Operations with wave function
#include "random.h"       // Generation pseudo-random number	

using namespace std;

int main() 
{
    double T_i = 2.;                                    // Initial temperature
    double T_f = 0.01;                                  // Final temperature
    double T_step = 0.99;                               // Update temperature T_new =  T_step * T_old
    vector<double> starting_parameters = {1., 1.};      // starting parameters
    int M = 1e7;                                        // Number of total throwns
    int N = 100;                                        // Number of blocks
    int L = int(M / N);                                 // Throwns in each block
    int block_eq = 40;                                  // Number of blocks for equilibration
    Random rn;                                          // Pseudo-random number generator
    
    Wavefunction wf(starting_parameters);               // Initialized wave function with starting parameters
    
    string namefile = "data";                           // Name file output
    vector<double> best_parameters = simul_annealing(rn, wf, T_i, T_f, T_step, namefile);    // Simuleted annealing algorithm to find optimal parameters
    
    wf.Set_parameters(best_parameters);                 // Set best parameters
    
    metropolis_algorithm(rn, wf, N, block_eq, L, namefile);     // Metropolis algorithm with optimal parameters

    return 0;
}
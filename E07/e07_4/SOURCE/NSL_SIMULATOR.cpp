/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include "system.h"
#include "functions.h"

using namespace std;

int main (int argc, char *argv[])
{
	int nconf = 1;
	// Paths directories
	vector<string> phase = {"../SOLID/", "../LIQUID/", "../GAS/"}; 	// Phases
	vector<string> path = {"INPUT/", "OUTPUT/"}; 					// Input and output directories
	vector<string> simul = {"NVT/", "NVE/"}; 					// Simulation types
	vector<int> block_eq = {10, 10, 10, 10, 10, 10}; 						// Number of blocks for equilibration

	for (int k = 0; k < phase.size(); k++) 		// Loop over phases 
	{
		for (int l = 0; l < simul.size(); l++) 	// Loop over simulations
		{
			bool last_block = false; 	// Flag for last block

			// Initialize the system
			System SYS;
			SYS.initialize(phase[k] + simul[l] + path[0], phase[k] + simul[l] + path[1]);
			SYS.initialize_properties(phase[k] + simul[l] + path[0], phase[k] + simul[l] + path[1]);
			SYS.block_reset(0, phase[k] + simul[l] + path[1]);
		
			for (int i = 0; i < SYS.get_nbl() + block_eq[2 * k + l]; i++)   // Loop over blocks
			{
				if (i + 1 == SYS.get_nbl() + block_eq[2 * k + l]) 			// Check if last block
					last_block = true;

				for (int j = 0; j < SYS.get_nsteps(); j++)  	// Loop over steps in a block
				{
					SYS.step();     							// Perform a simulation step

					if (i < block_eq[2 * k + l])				// Skip measurements for equilibration
						continue;

					SYS.measure();  							// Measure properties of the system
				}

				if (i < block_eq[2 * k + l])					// Increase steps to equilibrate system 
					continue;	

				SYS.averages(i + 1 - block_eq[2 * k + l], phase[k] + simul[l] + path[1], "", last_block);   // Compute averages of properties
				SYS.block_reset(i + 1 - block_eq[2 * k + l], phase[k] + simul[l] + path[1]);  				// Reset block averages
			}
			SYS.finalize(phase[k] + simul[l] + path[1], phase[k] + simul[l] + path[1]);  					// Finalize the system
		}
	}

	return 0;
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

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
	vector<string> phase = {"../SOLID/", "../LIQUID/", "../GAS/"};
	vector<string> path = {"INPUT/", "OUTPUT/"};
	string namefile = "U_step.dat";

	int block_eq = 1; 	// Number of blocks for equilibration

	for (int k = 0; k < phase.size(); k++)   // Loop over phases
	{
		double delta = Accep_50(phase[k] + path[0], phase[k] + path[1]); 	// Find the correct delta to have 50% acceptance rate

		// File for enrgy at each step
		ofstream sout;
		sout.open(phase[k] + path[1] + namefile);
		sout << "STEP U" << endl;
		sout.close();

		// Inizialize system
		System SYS;
		SYS.initialize(phase[k] + path[0], phase[k] + path[1], -1., delta);
		SYS.initialize_properties(phase[k] + path[0], phase[k] + path[1]);
		SYS.block_reset(0, phase[k] + path[1]);

		for (int i = 0; i < SYS.get_nbl() + block_eq; i++)   // Loop over blocks
		{
			for (int j = 0; j < SYS.get_nsteps(); j++)  	// Loop over steps in a block
			{
				SYS.step();     // Perform a simulation step

				if (i < block_eq)	// Skip measurements for equilibration
					continue;

				SYS.measure();  // Measure properties of the system
				SYS.print_penergy(j + 1, phase[k] + path[1] + namefile); // Print potential energy each step
			}

			if (i < block_eq)	// Increase steps to equilibrate system 
				continue;	

			SYS.averages(i + 1 - block_eq, phase[k] + path[1]);     // Compute averages of properties
			SYS.block_reset(i + 1 - block_eq, phase[k] + path[1]);  // Reset block averages
		}

		SYS.finalize(phase[k] + path[1], phase[k] + path[1]);  // Finalize the system
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

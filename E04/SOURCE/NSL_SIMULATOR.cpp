/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include "functions.h" // Include some functions
#include "system.h"    // For use class system
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) 
{
  int nconf = 1;

  // Paths directories
  vector<string> phase = {"../SOLID/", "../LIQUID/", "../GAS/"};
  vector<string> simul = {"EQUILIBRATION/", "SIMULATION/"};
  vector<string> path = {"INPUT/", "OUTPUT/"};

  int block_eq = 5; 	// Number of blocks for equilibration

  for (int k = 0; k < phase.size(); k++)   // Loop over phases
  {
    bool sign = false;   // Increase temperature

    if (k == 2)
      sign = true; // Decrease temperature

    double temp = Equilibration_temp(phase[k] + simul[0] + path[0], phase[k] + simul[0] + path[1], phase[k] + simul[1] + path[0], sign); // Equilibrate the system
    
    // Inizialize system
    System SYS;
    SYS.initialize(phase[k] + simul[1] + path[0], phase[k] + simul[1] + path[1], temp);
    SYS.initialize_properties(phase[k] + simul[1] + path[0], phase[k] + simul[1] + path[1]);
    SYS.block_reset(0, phase[k] + simul[1] + path[1]);

    for (int i = 0; i < SYS.get_nbl() + block_eq; i++)       // Loop over blocks
    {
    
      for (int j = 0; j < SYS.get_nsteps(); j++)  // Loop over steps in a block
      {
        SYS.step();     // Perform a simulation step

        if (i < block_eq)	// Skip measurements for equilibration
						continue;

        SYS.measure();  // Measure properties of the system
      }

			if (i < block_eq)	// Increase steps to equilibrate system 
					continue;	

      SYS.averages(i + 1 - block_eq, phase[k] + simul[1] + path[1]);     // Compute averages of properties
      SYS.block_reset(i + 1 - block_eq, phase[k] + simul[1] + path[1]);  // Reset block averages
    }

    SYS.finalize(phase[k] + simul[1] + path[1], phase[k] + simul[1] + path[1]);  // Finalize the system
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

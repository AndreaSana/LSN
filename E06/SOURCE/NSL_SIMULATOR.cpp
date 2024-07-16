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

using namespace std;

int main (int argc, char *argv[])
{
  	int nconf = 1;

	// Paths directories
	vector<string> path = {"../INPUT/", "../OUTPUT/"};									// Paths directories
	vector<string> method = {"Metropolis/", "Metropolis_H/", "Gibbs/", "Gibbs_H/"};		// Methods
	string namefile = "Ising.dat";														// File output
	
	int block_eq = 5; 	// Number of blocks for equilibration
	
	// Temperature variables
	double t_in = 0.49; 		// Initial temperature														
	double t_end = 2.;		// End temperature														
	double t_incr = 0.01; 	// Temperature increment												

	for (int k = 0; k < 1; k++)  	// Loop over methods
	{
		// File output
		ofstream sout(path[1] + method[k] + namefile);
		sout << "T U Err_U M Err_M Cv Err_Cv X Err_X" << endl;  	// Columns name
		sout.close();

		for(int l = 0; l < (t_end - t_in) / t_incr + 1; l++)		// Loop over temperatures	
		{	
			double t = t_in + l * t_incr;	// Temperature
			bool last_block = false;		// Variable to identify the last block

			// Initialize system
			System SYS;
			SYS.initialize(path[0] + method[k], path[1] + method[k], t);
			SYS.initialize_properties(path[0] + method[k], path[1] + method[k]);
			SYS.block_reset(0, path[1] + method[k]);

			for(int i = 0; i < SYS.get_nbl() + block_eq; i++)	// Loop over blocks
			{ 
				// Identify the last block
				if(i + 1 == SYS.get_nbl() + block_eq)
					last_block = true;
				
				for(int j = 0; j < SYS.get_nsteps(); j++)	// Loop over steps in a block
				{ 
					SYS.step();
					if (i < block_eq)	// Skip measurements for equilibration
						continue;
				
					SYS.measure();
				}
				
				if (i < block_eq)	// Skip measurements for equilibration
					continue;	

				SYS.averages(i + 1 - block_eq, path[1] + method[k], namefile, last_block); 	// Compute averages of properties
				SYS.block_reset(i + 1 - block_eq, path[1] + method[k]); 					// Reset block averages
			}

			SYS.finalize(path[1] + method[k], path[1] + method[k]); 						// Finalize the system
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

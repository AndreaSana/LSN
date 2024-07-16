#include "system.h"

using namespace std;

double read_temp(const string& path_input);		// Find the desired temperature in the input file 

double Equilibration_temp(const string& path_input, const string& path_output, const string& path_output_2, const int& sign);  // Find the correct temperature in order to have the desired temperature at equilibrium


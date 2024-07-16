#include "system.h"

using namespace std;

double Read_word(const string& path_input, const string& word);      // Find the temperature in the input file
double Equilibration_temp(const string& path_input, const string& path_output, const string& path_output_2, const int& sign);  // Find the correct temperature in order to have the desired temperature at equilibrium
double Accep_50(const string& path_input, const string& path_output); // Find the delta to have the 50% acceptance rate
double calc_acceptance(const double& delta, const string& path_input, const string& path_output); // Calculate the acceptance rate
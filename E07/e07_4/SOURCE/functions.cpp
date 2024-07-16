#include "functions.h"

// Find the value in the input file corrispoding to the word
double Read_word(const string& path_input, const string& word)
{
	// Open file 
	ifstream sin(path_input + "input.dat");

	if (!sin.is_open()) 
	{
			cout << "Impossibile aprire il file input.dat." << endl;
			return 1;
	}

	string row;								
	double value = -1.;

	// Find the value of temperature finding the word in the file
	while (getline(sin, row))
	{
		if (row.find(word) != string::npos) 
		{  
			value = stod(row.substr(row.find(word) + word.length())); 
			break;
		}
	}

	if (value == -1.) 
	{
			cout << "Temperatura non trovata." << endl;
			return 1;
	}

	sin.close();

	return value;
}

// Find the correct temperature in order to have the desired temperature at equilibrium
double Equilibration_temp(const string& path_input, const string& path_output, const string& path_output_2, const int& sign)
{
	double temp_in = Read_word(path_input, "TEMP");		// Desired temperature
	double temp = temp_in;						// Current temperature
	double diff_prec = temp;					// Previous difference between temperature reached and the desired one
	double temp_prec = temp;					// Previous temperature
	bool temp_check = true;						// Check if temperature reaches the desired one
	double increase = 0.1;						// Temperature increment
	System SYS; 								// System
	int count = 0;								// Counter

	// Decrease temperature
	if (sign) 
		increase *= - 1;						

	// File equilibration temperature
	ofstream fout;				
	fout.open(path_output + "temp.dat");
	fout << "T_i T_f Uncer" << endl;

	// Loop until temperature reaches the desired one
	while (temp_check)
	{	
		// Convert counter to string
		ostringstream oss;
		oss << setw(2) << setfill('0') << count;
		string count_str = oss.str();

		// Inizialize system
		SYS.initialize(path_input, path_output + count_str, temp);
		SYS.initialize_properties(path_input, path_output + count_str);
		SYS.block_reset(0, path_output + count_str);

		for (int i = 0; i < SYS.get_nbl(); i++) 		// Loop over blocks
		{
			for (int j = 0; j < SYS.get_nsteps(); j++)  // Loop over steps in a block
			{
				SYS.step(); 	// Perform a simulation step
				SYS.measure();  // Measure properties of the system
			}
			SYS.averages(i + 1, path_output + count_str);  		// Compute averages of properties
      		SYS.block_reset(i + 1, path_output + count_str);	// Reset block averages
		}

		count++; 	// Increase counter

		// Print temperature reached, temperature uncertainty and desired temperature
		fout << temp << " " << SYS.get_temp_block(SYS.get_nbl()) << " " << SYS.get_temp_uncer_block(SYS.get_nbl()) << endl;

		// If increase is too small exit loop
		if (abs(increase) == 10e-5) 
			break;

		// If difference between temperature reached and the desired one is smaller than the previous, update
		if (abs(SYS.get_temp_block(SYS.get_nbl()) - temp_in) < diff_prec)
		{
			diff_prec = abs(SYS.get_temp_block(SYS.get_nbl()) - temp_in);
			temp_prec = temp;
		}
		else // If no, reduce increment and try again
		{
			increase /= 10.;
			temp = temp_prec + increase;
			continue;
		}

		// If difference between temperature reached and the desired one is bigger than stv. dev. try again with other temperature
		if(abs(SYS.get_temp_block(SYS.get_nbl()) - temp_in) > SYS.get_temp_uncer_block(SYS.get_nbl()))
			temp += increase;
		else 	// Exit loop
			temp_check = false;
	}

	fout.close(); 								// Close file
	SYS.finalize(path_output, path_output_2);	// Finalize system
	return temp;
}

// Calculate the acceptance rate
double calc_acceptance(const double& delta, const string& path_input, const string& path_output)
{
	// Inizialize system
	System SYS;
	SYS.initialize(path_input, path_output, -1., delta);
	SYS.initialize_properties(path_input, path_output);
	SYS.block_reset(0, path_output);
	int n_steps = 10000; 	// Number of steps

	for (int i = 0; i < n_steps; i++)  // Loop over steps
	{
		SYS.step(); 		// Perform a simulation step
		SYS.measure(); 		// Measure properties of the system
	}

	return SYS.get_acceptance(); 	// Return acceptance rate
}

// Find the delta to have the 50% acceptance rate
double Accep_50(const string& path_input, const string& path_output)
{
	// File for delta and acceptance
	ofstream sout;
	sout.open(path_output + "accep_delta.dat");
	sout << "delta accep" << endl;

	// Initial values				
	double delta_max = pow(Read_word(path_input, "NPART") / Read_word(path_input, "RHO"), 1. / 3.);  	// Max value is the side of the box
	double delta_min = 0.0005;   																		// Min value
	double accepted_max = calc_acceptance(delta_max, path_input, path_output);  						// Acceptation with max value 
	double accepted_min = calc_acceptance(delta_min, path_input, path_output);							// Acceptation with min value 
	double delta;																						// Value to control
	double accepted; 																					// Acceptation
	
	// Loop to find the value to have 50% of acceptation
	do
	{
		delta = (delta_max + delta_min) / 2; 							// Mid point
		accepted = calc_acceptance(delta, path_input, path_output); 	// Acceptation mid point
		sout << delta << " " << accepted << endl;						// Print value and acceptation

		// Find the new subinterval in which search between the one on the right and on the left of the mid point
		double accepted_1 = calc_acceptance((delta_min + delta) / 2, path_input, path_output);
		double accepted_2 = calc_acceptance((delta_max + delta) / 2, path_input, path_output);

		if (abs(accepted_1 - 0.5) < abs(accepted_2 - 0.5))
		{
			delta_max = delta;
			accepted_max = accepted;

		}
		else
		{
			delta_min = delta;
			accepted_min = accepted;
		}
	}
	while(abs(accepted - 0.5) > 10e-4 && abs(accepted_max - accepted_min) > 10e-4);

	sout.close();	

	return delta;
}
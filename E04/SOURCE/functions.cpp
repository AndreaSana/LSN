#include "functions.h"

// Find the desired temperature in the input file 
double read_temp(const string& path_input)
{
	// Open file 
	ifstream sin(path_input + "input.dat");

	if (!sin.is_open()) 
	{
			cout << "Impossibile aprire il file input.dat." << endl;
			return 1;
	}

	string row;								
	string word = "TEMP";
	double temp = -1.;

	// Find the value of temperature finding the word "TEMP" in the file
	while (getline(sin, row))
	{
		if (row.find(word) != string::npos) 
		{  
			temp = stod(row.substr(row.find(word) + word.length())); 
			break;
		}
	}

	if (temp == -1.) 
	{
			cout << "Temperatura non trovata." << endl;
			return 1;
	}

	sin.close();

	return temp;
}

// Find the correct temperature in order to have the desired temperature at equilibrium
double Equilibration_temp(const string& path_input, const string& path_output, const string& path_output_2, const int& sign)
{
	double temp_in = read_temp(path_input);		// Desired temperature
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

#include "function.h"

using namespace std;

// Check if the index is present in vector of indexes
bool check_index (const vector<int>& index, const int& x)
{
	bool check = false;  	// Check variable

	for (int n : index)  	// Loop over indexes
	{
		if (n == x)   		// Check if the index is present
        	check = true;
    }

	return check;
}

// Generate N positions on a circumference
vector<Position> sampled_circ(const int& N)
{
	Random rn; 				// Pseudo-number generator

	vector<Position> pos; 	// Vector of position

	for (int i = 0; i < N; i++) 	// Loop over number of travels
	{
		vector<double> coordinates; 				// Vector of coordinates of one city
		double theta = rn.Rannyu(0., 2. * M_PI); 	// Generate pseudo-random number for angle
		
		// Fill coordinates with x and y value
		coordinates.push_back(cos(theta));
		coordinates.push_back(sin(theta));

		pos.push_back(coordinates); 				// Fill vector of position
	}

	return pos;
}

// Generate N positions inside a square
vector<Position> sampled_square(const int& N)
{
	Random rn; 				// Pseudo-number generator

	vector<Position> pos; 	// Vector of position

	for (int i = 0; i < N; i++)		 // Loop over number of travels
	{
		vector<double> coordinates; 		// Vector of coordinates of one city
		
		double x = rn.Rannyu(-1., 1.); 		// Generate pseudo-random number x coordinate
		double y = rn.Rannyu(-1., 1.); 		// Generate pseudo-random number y coordinate
		
		// Fill coordinates with x and y value
		coordinates.push_back(x);
		coordinates.push_back(y);

		pos.push_back(coordinates); 		// Fill vector of position
	}

	return pos;
}

// Read position from file
vector<Position> Read_position(const string& namefile)
{
	ifstream sin(namefile);
	vector<Position> pos;  // Vector of positions

	while(!sin.eof())  // Loop over rows
	{
		// Input coordinate
		double x, y;
		sin >> x >> y;

		vector<double> coordinates;		// Vector of coordinates of one city
			
		// Fill coordinates with x and y value
		coordinates.push_back(x);
		coordinates.push_back(y);

		pos.push_back(coordinates);  // Fill vector of position
	}

	sin.close();

	return pos;
}


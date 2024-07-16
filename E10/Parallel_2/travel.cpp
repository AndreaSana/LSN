#include "travel.h"

// Default constructor
Travel :: Travel()
{

}

// Constructor with vector of position of cities arranging randomly
Travel :: Travel(Random& rn, vector<Position> v_pos)
{
	_n_city = v_pos.size(); 	// Assigned number cities
    vector<Position> v_copy; 	// Vector ordered ramdomly
	vector<int> index; 			// Vector of indexes of cities
	bool check = true; 			// Control variable to check if all elements of vector are chosen one time 

    // Set first city in order to break rotational degeneration
    index.push_back(0); 		// Add index of fisrt element
    City city(0, v_pos[0]); 	// Create a variable city
	_travel.push_back(city); 	// Add new element to vetor travel

	// Loop to take all cities one time
	do
	{
		int x = floor(rn.Rannyu(1, v_pos.size()));  // Generate integer pseudo-random number that represents an index of the vector

		// If the index has already chosen try again another one
		if(check_index(index, x))
			continue;

		index.push_back(x); 		// Add index of new element
        City city(x, v_pos[x]); 	// Create a variable city
		_travel.push_back(city); 	// Add new element to vector travel

		// If all elements are used exit loop
		if (index.size() == v_pos.size())
			check = false;
	} 
	while (check);
}

// Constructor with vector of cities arranging randomly
Travel :: Travel(Random& rn, vector<City> v_city)
{
	_n_city = v_city.size();  		// Assigned number cities
    vector<City> v_copy; 			// Vector of cities ordered ramdomly
	vector<int> index; 				// Vector of indexes of cities
	bool check = true; 				// Control variable to check if all elements of vector are take one time
    
    // Set first city in order to break rotational degeneration
    index.push_back(0); 			// Add index of first element
	_travel.push_back(v_city[0]); 	// Add first element to vector travel

	// Loop to take all cities one time
	do  
	{
		int x = floor(rn.Rannyu(1, v_city.size()));  	// Generate integer pseudo-random number that represents an index of the vector

		// If the index has already chosen try again another one
		if(check_index(index, x))
			continue;

		index.push_back(x); 				// Add index of new element
		_travel.push_back(v_city[x]); 		// Add new element

		// If all elements are used exit loop
		if (index.size() == v_city.size())
			check = false;
	} 
	while (check);
}

// Constructor with other travel
Travel :: Travel(const vector<City>& travel)
{
    _travel =  travel;
	_n_city = travel.size();
}

// Constructor empty with dimension
Travel :: Travel(const int& size)
{
	_n_city = size;   // Assigned number cities

	for (int i = 0; i < _n_city; i++)  	// Loop over cities
	{
		Position pos;
		City city(i, pos); 		// Create a variable city
		_travel.push_back(city); 	// Add new element to vector travel
	}
}

// Calculated cost function L_1
double Travel :: L_1() const
{
    double L = 0.; 		// Inizialized cost function

    for (int i = 0; i < _n_city - 1; i++) 		// Loop over elements of map (cities)
        L += sqrt((_travel[i].Get_position() - _travel[i + 1].Get_position()).norm()); 		// Add |x_i-x_{i+1}| 

    L += sqrt((_travel[_travel.size() - 1].Get_position() - _travel[0].Get_position()).norm()); 	// Close cicle

    return L;
}

// Calculated cost function L_2
double Travel :: L_2() const 
{
    double L = 0.; 		// Inizialized cost function

    for (int i = 0; i < _n_city - 1; i++) // Loop over elements of map (cities)
        L += (_travel[i].Get_position() - _travel[i + 1].Get_position()).norm(); 	// Add |x_i-x_{i+1}|^2 
    
    L += (_travel[_travel.size() - 1].Get_position() - _travel[0].Get_position()).norm(); 	// Close cicle

    return L;
}

// Get number of cities
int Travel :: Get_size() const
{
    return _n_city;
}

 // Get position i-th cities
Position Travel :: Get_position(const int& index) const
{
    return _travel[index].Get_position();
}
 
 // Get index of city in position of vector chosen 
int Travel :: Get_city_index(const int& index) const
{
    return _travel[index].Get_index();
}

// Get vector of cities
vector<City> Travel :: Get_cities() const
{
	return _travel;
}

// Operator = to assigned travel
Travel& Travel :: operator=(const Travel& travel)
{

    _travel = travel.Get_cities();
    _n_city = travel.Get_size();
    return (*this);
}

// Print in order the cities of travel
void Travel :: Print_travel(const int& n_gen) const
{
	// Create new file empty
	ostringstream oss;
    oss << "Travels/"  << setfill('0') << setw(4) << to_string(n_gen) << ".dat";
    string namefile = oss.str();
	ofstream sout(namefile);

	// Name columns
	if (Get_position(0).Get_dimension() == 2)
		sout << "x y" << endl;

	sout.close();

	for (int i = 0; i < _n_city; i++) 	// Loop over city
		_travel[i].Print_city(namefile); 	// Print position i-th city

	_travel[0].Print_city(namefile); 	// Print position of first city
}

// Get vector of indexes of cities
vector<int> Travel :: Get_index_cities() const
{
	vector<int> index;

	for (int i = 0; i < _n_city; i++)   	// Loop over cities
		index.push_back(_travel[i].Get_index());  	// Get index of city

	return index;
}

// Check that each city is visited one and only one time
void Travel :: Check_travel() const
{
	// Check number of cities
	if (int(_travel.size()) != _n_city)
	{
		cout << "Number of cities uncorrect" << endl;
		exit(-1);
	}

	// Check if all indexes are present the travel
	for(int i = 0; i < _n_city; i++) 	// Loop over indexes to search
	{
		if(!check_index(Get_index_cities(), i))   // Check if the index is present
		{
			cout << "City with index " << i << " not present" << endl;
			exit(-2);
		}
	}
}

// Set index-th city
void Travel :: Set_city(const int& index, const City& city)
{
	_travel[index] = city;
}

// Get index-th city
City Travel :: Get_city(const int& index) const
{
	return _travel[index];
}

// Set new travel using indexes
void Travel :: Set_index_travel(const vector<int>& index)
{	
	vector<City> travel = _travel;
	for (int i = 1; i < int(index.size()); i++)
	{
		for (int j = 1; j < int(index.size()); j++)
		{
			if(index[i] == travel[j].Get_index())
			{
				Set_city(i, travel[j]);
				break;
			}
				
		}
	}
}
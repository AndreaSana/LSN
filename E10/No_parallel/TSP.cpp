#include "TSP.h"

// Constructor with number of travels and position of cities
TSP :: TSP(const int& n_generation, const int& n_travels, vector<Position> pos_cities)
{
    _current_gen = 0;                       // Set number of current generation
    _n_generation = n_generation;           // Set number of generations
    _n_travels = n_travels;                 // Set number of travels each generation

    for (int i = 0; i < n_travels; i++)     // Loop over travels
    {
        Travel travel(_rn, pos_cities);     // Define variable travel
        travel.Check_travel();              // Check if each city is present one and only one time
        _travels.push_back(travel);         // Add travel to vector of travels
    }

    _travels = Sort(_travels);              // Order travels according cost function
}

// Constructor with number of travels and cities
TSP :: TSP(const int& n_generation, const int& n_travels, vector<City> cities)
{
    _current_gen = 0;                       // Set number of current generation
    _n_generation = n_generation;           // Set number of generations
    _n_travels = n_travels;                 // Set number of travels each generation
 
    for (int i = 0; i < _n_travels; i++)    // Loop over travels
    {
        Travel travel(_rn, cities);         // Define variable travel
        travel.Check_travel();              // Check if each city is present one and only one time
        _travels.push_back(travel);         // Add travel to vector of travels
    }

    _travels = Sort(_travels);              // Order travels according cost function
}

// Find travel with minimal cost function
Travel TSP :: Find_best() const
{
    double L_min = _travels[0].L_2();       // Inizialized cost function L minimal
    int index_min = 0;                      // Inizialized index of shortest travel

    for (int i = 1; i < _n_travels; i++)    // Loop over travels
    {
        double L = _travels[i].L_2();       // L of each travel

        // If L is smaller than L_min update variables
        if (L < L_min)
        {
            L_min = L;
            index_min = i;
        }
    }

    return _travels[index_min]; 
}

// Get vector of travels
vector<Travel> TSP :: Get_travels() const
{
    return _travels;
}

// Get number of generation
int TSP :: Get_generation() const 
{
    return _current_gen;
}

// Create _n_generation generations
void TSP :: Evolution()
{
    // Output file with names colums
    string namefile = "L.dat";	
	ofstream sout(namefile);
    sout << "Gen L" << endl;
    sout.close();
    string namefile2 = "L_half.dat";	
	ofstream sout2(namefile2);
    sout2 << "Gen L" << endl;
    sout2.close();

    _travels[0].Print_travel(_current_gen);   // Print best travel of generation
    
    while (_current_gen < _n_generation)            // Loop over generations
    {    
        _current_gen++;        // Increase generation

        // Print number generation        
	    ofstream sout(namefile, ios::app);
        sout << _current_gen << " ";
        sout.close();
	    ofstream sout2(namefile2, ios::app);
        sout2 << _current_gen << " ";
        sout2.close();

        _travels = New_generation(_rn, _travels);     // Create new generation
        _travels[0].Print_travel(_current_gen);       // Print best travel of new generation
    }
}

// Replace vector of travels with new one
void TSP :: Set_TSP(const vector<Travel>& travels)
{
    _travels = travels;
}

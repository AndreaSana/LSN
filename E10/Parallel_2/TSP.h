#ifndef __TSP_h__
#define __TSP_h__

#include <iostream>
#include <complex>
#include <cmath> 
#include <vector>
#include "gen_function.h"

using namespace std;

// Class for the traveling salesman problem
class TSP
{
    public: 
        // Constructor with number of travels and position of cities
        TSP(const int& n_generation, const int& n_travels, vector<Position> pos_cities, const int& row, const int& size, const vector<double>& temp);        
        // Constructor with number of travels and cities
        TSP(const int& n_generation, const int& n_travels, vector<City> cities, const int& row, const int& size, const vector<double>& temp);                
        // Destructor
        ~TSP(){};                                                                               

        // Get _travels
        vector<Travel> Get_travels() const;     
        // Replace vector of travels with new one                                                
        void Set_TSP(const vector<Travel>& travels);  
        // Find travel with minimal cost fuction                                          
        Travel Find_best() const;    
        // Create _n_generation generations                                                          
        void Evolution();                                    
        // Get number of generation          
        int Get_generation() const;
        // Get temperature
        double Get_temperature(const int& index) const;     
        // Get rank
        int Get_rank() const;                                                       

    private:
        vector<Travel> _travels;     // Vector of travels
        int _n_travels;              // Number of travels
        int _n_generation;           // Number of generation
        int _current_gen;            // Number of current generation
        Random _rn;                  // Generator of pseudo-random number
        vector<double> _temp;        // Temperature
        int _rank;                   // Rank of core
        int _size;                   // Number of core
};

#endif
#ifndef __travel_h__
#define __travel_h__

#include <iostream>
#include <complex>
#include <cmath> 
#include <vector>
#include <algorithm>
#include "function.h"

using namespace std;

// Class to describe a travel through cities in TSP
class Travel
{
    public:
        // Default constructor
        Travel();                                     
        // Constructor with vector of cities arranging randomly                      
        Travel(Random& rn, vector<City> v_city);                            
        // Constructor with vector of position of cities arranging randomly
        Travel(Random& rn, vector<Position> v_pos);              
        // Constructor with other travel           
        Travel(const vector<City>& travel);                              
        // Constructor empty with dimension   
        Travel(const int& size);                              
        // Destructor              
        ~Travel(){}                                
         // Calculated cost function L_1                         
        double L_1() const;                                        
        // Calculated cost function L_2        
        double L_2() const;  
        // Operator = to assigned city                                               
        Travel& operator=(const Travel& Travel);                
        // Get number of cities           
        int Get_size() const;                          
        // Get vector of cities
        vector<City> Get_cities() const;           
        // Get position i-th cities                         
        Position Get_position(const int& index) const;                
        // Get index of city in position of vector chosen      
        int Get_city_index(const int& index) const;     
        // Print in order the cities of travel                    
        void Print_travel(const int& n_gen) const;     
        // Check that each city is visited one and only one time 
        void Check_travel() const;                 
        // Get vector of indexes of cities                         
        vector<int> Get_index_cities() const;           
        // Set index-th city                    
        void Set_city(const int& index, const City& city);   
        // Get index-th city               
        City Get_city(const int& index) const;                              

    private:
        vector<City> _travel;    // Vector of cities
        int _n_city;             // Number of cities
};

#endif
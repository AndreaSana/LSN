#ifndef __city_h__
#define __city_h__

#include <iostream>
#include <complex>
#include <cmath> 
#include <vector>
#include "position.h"

using namespace std;

// Class to describe city of TSP
class City
{
    public:
        // Constructor 
        City(const int& index, const Position& pos); 
        // Destructor       
        ~City(){}                                           

        // Get position of city
        Position Get_position() const;
        // Set position of city                    
        void Set_position(const Position& pos);
        // Get index of city             
        int Get_index() const;
        // Set index of city                              
        void Set_index(const int& index);
        // Operator = to assigned city                   
        City& operator=(const City& city);
        // Print city's coordinates                  
        void Print_city(const string& namefile) const;      

    private:
        Position _pos;     // Position of city
        int _index;        // Index of city
};

#endif
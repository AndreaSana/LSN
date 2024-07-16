#ifndef __position_h__
#define __position_h__

#include <iostream>
#include <complex>
#include <cmath> 
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Class to describe the position of cities of TSP
class Position
{
    public:
        // Default constructor
        Position();         
        // Constructor with dimension                                        
        Position(const int& dim); 
        // Constructor with position                                  
        Position(const Position& coordinates);  
        // Constructor with vector of coordinates                    
        Position(const vector<double>& coordinates);  
        // Destructor              
        ~Position(){}                                        
        // Get value of the i-th coordinate       
        double Get_coordinate(const int& i) const;                  
        // Set value of the i-th coordinate
        void Set_coordinate(const double& value, const int& i);     
        // Get vector of coordinates of position
        vector<double> Get_position() const;                     
        // Set vector of coordinates of position   
        void Set_position(const vector<double>& pos);        
        // Get dimension of position       
        int Get_dimension() const;        
        // Operator - between position                          
        Position operator-(const Position& pos) const;         
        // Operator = to assigned Position     
        Position& operator=(const Position& pos);        
        // Norm of vector coordinates           
        double norm();                           
        // Print coordinates of position                   
        void Print_position(const string& namefile) const;          
    
    private:
        vector<double> _coordinates;   // Vector with coordinates
};

#endif
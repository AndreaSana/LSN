#include "position.h"

// Default constructor
Position :: Position()
{

}

// Constructor with dimension
Position :: Position(const int& dim)
{
    vector<double> coordinates(dim);
    _coordinates = coordinates;
}

// Constructor with position
Position :: Position(const Position& coordinates)
{
    _coordinates = coordinates.Get_position();
}

// Constructor with vector of coordinates
Position :: Position(const vector<double>& coordinates)
{
    _coordinates = coordinates;
}

// Operator - between position
Position Position :: operator-(const Position& pos) const 
{
    // If sizes are different exit
    if (Get_dimension() != pos.Get_dimension()) 
    {
        cout << "Vector have different size" << endl;
        exit (-1);
    }

    Position diff(Get_dimension());     // Difference between positions

    for (int i = 0; i < Get_dimension(); i++)   // Loop over dimension
        diff.Set_coordinate(_coordinates[i] - pos.Get_coordinate(i), i);    // Difference between coordinates 
    
    return diff;
}

// Operator = to assigned Position
Position& Position :: operator=(const Position& pos)
{
    _coordinates = pos.Get_position();
    return (*this);
}

// Get value of the i-th coordinate
double Position :: Get_coordinate(const int& i) const
{
    return _coordinates[i];
}  

// Set value of the i-th coordinate
void Position :: Set_coordinate(const double& value, const int& i)
{
    _coordinates[i] = value;
}

// Get vector of coordinates of position
vector<double> Position :: Get_position() const
{
    return _coordinates; // Constructor;
} 

// Get dimension of position
int Position :: Get_dimension() const
{
    return _coordinates.size();
}

// Set vector of coordinates of position
void Position :: Set_position(const vector<double>& pos)
{
    _coordinates = pos;
}

// Norm of vector coordinates
double Position :: norm() 
{
    double sum = 0.;

    for (int i = 0; i < Get_dimension(); i++)  // Loop over coordinates
        sum += pow(Get_coordinate(i), 2);     
    
    return sum;
}

// Print coordinates of position
void Position :: Print_position(const string& namefile) const
{
    ofstream sout(namefile, ios::app);

    for (int i = 0; i < Get_dimension(); i++)   // Loop over coordinates
        sout << Get_coordinate(i) << " ";       // Print i-th coordinate

    sout << endl;
}
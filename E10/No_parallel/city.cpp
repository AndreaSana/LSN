#include "city.h"

// Constructor        
City :: City(const int& index, const Position& pos)
{
    _index = index;
    _pos = pos;
}

// Get position of city
Position City :: Get_position() const
{
    return _pos;
}

// Set position of city        
void City :: Set_position(const Position& pos)
{
    _pos = pos;
}

// Get index of city        
int City :: Get_index() const
{
    return _index;
}

// Set index of city
void City :: Set_index(const int& index)
{
    _index = index;
}

// Operator = to assigned city
City& City :: operator=(const City& city)
{
    _index = city.Get_index();
    _pos = city.Get_position();
    return (*this);
}

// Print city's coordinates
void City :: Print_city(const string& namefile) const
{
	Get_position().Print_position(namefile);    // Print position of city
}
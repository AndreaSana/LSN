#include "Posizione.h"
#include <cmath>
#include <iostream>

using namespace std;

// Default costructore
Posizione::Posizione() 
{
  m_x = 0;
  m_y = 0;
  m_z = 0;
}

// Specific costructor
Posizione::Posizione(double x, double y, double z) 
{
  m_x = x;
  m_y = y;
  m_z = z;
}

// Destructor
Posizione::~Posizione() {}

// Get x coordinate
double Posizione::GetX() const 
{ 
	return m_x; 
}

// Get y coordinate
double Posizione::GetY() const 
{ 
	return m_y; 
}

// Get z coordinate
double Posizione::GetZ() const 
{ 
	return m_z; 
}

// Get radius
double Posizione::GetR() const 
{
  return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

// Get theta angle
double Posizione::GetTheta() const 
{ 
	return atan(m_y / m_x); 
}

// Get phi angle
double Posizione::GetPhi() const 
{ 
	return acos(m_z / GetR()); 
}

// Get radius in cylindrical coordinates
double Posizione::GetRho() const 
{ 
	return sqrt(m_x * m_x + m_y * m_y); 
}

// Distance from another point
double Posizione::Distanza(const Posizione &p) const 
{
  return sqrt(pow(GetX() - p.GetX(), 2) + pow(GetY() - p.GetY(), 2) +
              pow(GetZ() - p.GetZ(), 2));
}

// Distance from another point
double Posizione::Distanza(const double &x, const double &y, const double &z) const 
{
	return sqrt(pow(GetX() - x, 2) + pow(GetY() - y, 2) +
							pow(GetZ() - z, 2));
}

// Sum of positions
Posizione Posizione::operator+(Posizione p) const 
{
  Posizione sum;

  sum.SetX(p.GetX() + GetX());
  sum.SetY(p.GetY() + GetY());
  sum.SetZ(p.GetZ() + GetZ());

  return sum;
}

// Set x coordinate
void Posizione::SetX(double x) 
{ 
	m_x = x; 
}

// Set y coordinate
void Posizione::SetY(double y) 
{ 
	m_y = y; 
}

// Set z coordinate
void Posizione::SetZ(double z) 
{ 
	m_z = z; 
}

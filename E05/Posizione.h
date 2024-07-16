#ifndef __Posizione_h__
#define __Posizione_h__

class Posizione 
{
	public:
  Posizione();													// Default costructore
  Posizione(double, double, double);		// Specific costructor
  ~Posizione();													// Destructor

  // Metods
  Posizione operator+(Posizione p) const; // Sum positions
  void SetX(double); 
  void SetY(double);
  void SetZ(double);

  // Get cartesian coordinates
  double GetX() const;
  double GetY() const;
  double GetZ() const;

  // Get spherical coordinates
  double GetR() const;
  double GetTheta() const;
  double GetPhi() const;

  // Get cylindrical coordinates
  double GetRho() const;

  // Distance from another point
  double Distanza(const Posizione &) const;
	double Distanza(const double &x, const double &y, const double &z) const;

	private:
  double m_x, m_y, m_z; 		// Coordinates (x, y, z)
};

#endif
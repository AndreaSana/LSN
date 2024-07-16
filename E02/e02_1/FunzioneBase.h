#ifndef __FunzioneBase__
#define __FunzioneBase__

#include <cmath>

// Class for calculating the value of a function
class FunzioneBase 
{
	public:

	virtual double Eval (double) const = 0; // Calculate value of function
	virtual ~FunzioneBase() {;}; // Destructor
};

// Class coseno
class Coseno : public FunzioneBase 
{
	public:

	Coseno () {k = 1; w = 1; phi = 0;} // Default costructore
	Coseno (double a, double b, double c) {k = a; w = b; phi = c;} // Costructore with parameters
	virtual ~Coseno () {} // Destructor

	virtual double Eval (double x) const override {return k*cos(w*x + phi);} // Calculate value of function

	void SetK (double a) {k = a;} // Set k
	double GetK () const {return k;} // Get k
	void SetW (double b) {w = b;} // Set w
	double GetW () const {return w;} // Get w
	void SetPhi (double c) {phi = c;} // Set phi
	double GetPhi () const {return phi;} // Get phi

	private:

	double k, w, phi; // k*cos(w*x+phi))
};

// Class 2 degree polynomial
class Pol2 : public FunzioneBase 
{
	public:

	Pol2 () {k = 1; a = 1; b = 0; c = 1;} // Default costructore
	Pol2 (double c_1, double c_2, double c_3, double c_4) {k = c_1; a = c_2; b = c_3; c = c_4;} // Costructore with parameters
	virtual ~Pol2 () {} // Destructor

	virtual double Eval (double x) const override {return k*(a + b*x + c*x*x);} // Calculate value of function

	void SetK (double x) {k = x;} // Set k
	double GetK () const {return k;} // Get k
	void SetA (double x) {a = x;} // Set a
	double GetA () const {return a;} // Get a
	void SetB (double x) {b = x;} // Set b
	double GetB () const {return b;} // Get b
	void SetC (double x) {c = x;} // Set c
	double GetC () const {return c;} // Get c

	private:

	double a, b, c, k; // k*(a +b*x+c*x^2)
};

#endif
#include "funzioni.h"

// Function for mean square root
double errore(double mean, double mean_2, int n)
{
	if (n == 0)
		return 0;
	else
		return sqrt((mean_2 - pow(mean, 2)) / n);
}
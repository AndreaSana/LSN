#include "function.h"     // Some functions
#include "random.h"       // Generation pseudo-random number
#include "TSP.h"          // Traveling salesman problem	
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    int n_city = 34;            // Number of cities 
    int n_travel = 100;         // Number of individuals in a population 
    int n_generation = 300;     // Number of generation

    // File output 
    string namefile_c = "c"; 
    string namefile_s = "s"; 

    TSP TSP_circ(n_generation, n_travel, sampled_circ(n_city));         // TSP with cities on circumference
    TSP TSP_square(n_generation, n_travel, sampled_square(n_city));     // TSP with cities inside square

    TSP_circ.Evolution(namefile_c);     // Evolution TSP with cities on circumference
    TSP_square.Evolution(namefile_s);   // Evolution TSP with cities inside square

    return 0;
}
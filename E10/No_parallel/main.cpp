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
    int n_travel = 8;         // Number of individuals in a population 
    int n_generation = 30000;     // Number of generation
    
    TSP TSP(n_generation, n_travel, Read_position("cap_prov_ita.dat"));         // TSP with cities on circumference
    TSP.Evolution();     // Evolution TSP with cities on circumference

    return 0;
}
#ifndef __function_h__
#define __function_h__

#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "city.h"
#include "random.h"


using namespace std;

// Check if the index x is present in vector of indexes
bool check_index (const vector<int>& index, const int& x);      
// Generate N position on a circumference
vector<Position> sampled_circ(const int& N);        
// Generate N positions inside a square            
vector<Position> sampled_square(const int& N);                  

#endif
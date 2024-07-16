#ifndef __gen_function_h__
#define __gen_function_h__

# include "mpi.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "travel.h"

using namespace std;

// Order travels according to cost function
vector<Travel> Sort(vector<Travel> travels);                         
// Create a new generation                                       
vector<Travel> New_generation(Random& rn, const vector<Travel>& travels, const string& namefile, const double& temp, const int& n_gen, const int& rank, const int& size);   
// Selection individual acccording to cost fuction
vector<Travel> Selection(Random& rn, const vector<Travel>& generation);       
// Calculate vector of probability of selection according to the cost function                              
vector<double> L_prob(const int& index, const vector<Travel>& generation);    
// Select an individual sampling its index                              
void Find_block_L_prob(Random& rn, const vector<double>& L_rec, int& index);  
// Pair permutation                              
Travel Pair_permutation(Random& rn, const Travel& son);                                   
// Shift of block of cities                  
Travel Shift(Random& rn, const Travel& son);                   
// Block permutation                                             
Travel Block_permutation(Random& rn, const Travel& son);     
// Inversion                                               
Travel Inversion(Random& rn, const Travel& son);                     
// Crossover                                        
vector<Travel> Crossover(Random& rn, const vector<Travel>& parents);                              
// Print L best and mean of L of half population with L lower         
void Print_L(const vector<Travel>& generation, const string& name);                                         

#endif
#include "gen_function.h"

using namespace std;

// Order travels according to cost function
vector<Travel> Sort(const vector<Travel> travels)
{
	vector<Travel> v_copy = travels;    // Vector of travels

    // Bubble sort
     for (int i = 0; i < int(v_copy.size() - 1); i++) 
     {
        for (int j = i; j < int(v_copy.size()); j++) 
		{
            if (v_copy[i].L_2() > v_copy[j].L_2()) 
			{
				Travel temp = v_copy[j];
                v_copy[j] = v_copy[i];
				v_copy[i] = temp;
            }
        }
    }

	return v_copy;
}

// Create a new generation
vector<Travel> New_generation(Random& rn, const vector<Travel>& travels, const string& namefile, const double& temp, const int& n_gen, const int& rank, const int& size)
{
    Travel son = travels[0];   // New individual

    double p_mut = 1.;

    // Pair permutation
    if (rn.Rannyu() < p_mut)
        son = Pair_permutation(rn, son);

    double A = min(1., exp(-(son.L_2() - travels[0].L_2()) / temp));  	// Transition probability 
    
    // Reject new position
    if (rn.Rannyu() > A)
        son = travels[0];      // Restore previus travel
   
    // Shift of block of cities
    if (rn.Rannyu() < p_mut)
        son = Shift(rn, son);

    A = min(1., exp(-(son.L_2() - travels[0].L_2()) / temp));  	// Transition probability 
    
    // Reject new position
    if (rn.Rannyu() > A)
        son = travels[0];      // Restore previus travel

    // Block permutation
    if (rn.Rannyu() < p_mut)
        son = Block_permutation(rn, son);

    A = min(1., exp(-(son.L_2() - travels[0].L_2()) / temp));  	// Transition probability 
    
    // Reject new position
    if (rn.Rannyu() > A)
        son = travels[0];      // Restore previus travel

    // Inversion
    if (rn.Rannyu() < p_mut)
        son = Inversion(rn, son);
    
    A = min(1., exp(-(son.L_2() - travels[0].L_2()) / temp));  	// Transition probability 

    // Reject new position
    if (rn.Rannyu() > A)
        son = travels[0];      // Restore previus travel
    
    son.Check_travel();    // Check if each city is present one and only one time
    
    // Exchange between processes
    MPI_Status stat_1, stat_2, stat_3, stat_4;                    // Variable for status
    double temp_rec;                                              // Variable for temperature received
    double L_rec;                                                 // Variable for cost function received
    int tag_temp = 1, tag_L = 2, tag_index = 3, tag_bool = 4;     // Tags for messages
    bool check_exchange = false;                                  // Variable indicates exchange 
    bool check_rec;                                               // Variable indicates exchange received

    if(rank != 0 && rank % 2 == n_gen % 2)
    {
        MPI_Send(&temp, 1, MPI_DOUBLE, rank - 1, tag_temp, MPI_COMM_WORLD);                                      // Send temperature
        L_rec = son.L_2();                                                                                       // Cost function
        MPI_Send(&L_rec, 1, MPI_DOUBLE, rank - 1, tag_L, MPI_COMM_WORLD);                                        // Send cost function
        MPI_Send(son.Get_index_cities().data(), son.Get_size(), MPI_INT, rank - 1, tag_index, MPI_COMM_WORLD);   // Send indexes of travel
    }

    MPI_Barrier(MPI_COMM_WORLD);    // Synchronize all cores

    if(rank != size - 1 && rank % 2 != n_gen % 2) 
    {
        MPI_Recv(&temp_rec, 1, MPI_DOUBLE, rank + 1, tag_temp, MPI_COMM_WORLD, &stat_1);                         // Receive temperature
        MPI_Recv(&L_rec, 1, MPI_DOUBLE, rank + 1, tag_L, MPI_COMM_WORLD, &stat_2);                               // Receive cost function
        vector<int> index_rec(son.Get_size());                                                                   // Indexes of travel received
        MPI_Recv(index_rec.data(), son.Get_size(), MPI_INT, rank + 1, tag_index, MPI_COMM_WORLD, &stat_3);       // Receive indexes of travel

        // Exchange of paths between processes
        double A = min(1., exp(-(1. / temp - 1. / temp_rec)*(L_rec - son.L_2())));   // Transition probability 

        // Acceptance of exchange
        if (rn.Rannyu() < A)
        {
            check_exchange = true;
            MPI_Send(son.Get_index_cities().data(), son.Get_size(), MPI_INT, rank + 1, tag_index, MPI_COMM_WORLD);   // Send indexes of travel    
            son.Set_index_travel(index_rec);  // Set new travel
        }       

        MPI_Send(&check_exchange, 1, MPI_LOGICAL, rank + 1, tag_bool, MPI_COMM_WORLD);      // Send temperature
    }
    
    if(rank != 0 && rank % 2 == n_gen % 2)
    {
        MPI_Recv(&check_rec, 1, MPI_LOGICAL, rank - 1, tag_bool, MPI_COMM_WORLD, &stat_4);  // Receive temperature
        if(check_rec)
        {
            vector<int> index_rec(son.Get_size());
            MPI_Recv(index_rec.data(), son.Get_size(), MPI_INT, rank - 1, tag_index, MPI_COMM_WORLD, &stat_3);     // Receive indexes of travel
            son.Set_index_travel(index_rec);    // Set new travel
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);    // Synchronize all cores

    vector<Travel> new_generation;
    new_generation.push_back(son);          // Add new individual to new generation
    
    Print_L(new_generation, namefile);      // Print L best and mean of L of half population with L lower 
    return new_generation;                  // Update generation with new one
}

// Selection individual acccording to cost fuction
vector<Travel> Selection(Random& rn, const vector<Travel>& generation)
{
    // If there is only one element return it
    if(int(generation.size()) == 1)
        return generation;
    
    vector<Travel> parents;                                             // Vector parents
    int index_first_parent = -1;                                        // Inizialized index first parent
    vector<double> L_rec = L_prob(index_first_parent, generation);      // Calculated vector of selection probability
	Find_block_L_prob(rn, L_rec, index_first_parent);                   // Find which individual is selected
    parents.push_back(generation[index_first_parent]);                  // Update vector parents
    
    L_rec = L_prob(index_first_parent, generation);                     // Calculated vector of selection probability without the first parent
	Find_block_L_prob(rn, L_rec, index_first_parent);                   // Find which individual is selected
    parents.push_back(generation[index_first_parent]);                  // Update vector parents

    return parents;
}

// Calculate vector of probability of selection according to the cost function
vector<double> L_prob(const int& index, const vector<Travel>& generation)
{
    double L_sum = 0.;          // Inizialized sum all cost function
    vector<double> L_rec;       // Vector of reciprocal of cost function (probability according cost function)
    
    for (int i = 0; i < int(generation.size()); i++)    // Loop over travels
    {
        double x = pow(generation[i].L_2(), -4);        // Calculate probability according cost function

        // Parent already chosen doesn't give contribution
        if (i == index)
            x = 0.;

        L_sum += x;             // Increase value of L_sum
        L_rec.push_back(x);     // Fill vector of reciprocals
    }

    // Divide each element of vector of reciprocals by L_sum to obtain probability of selection
    for (auto& element : L_rec)
        element /= L_sum;

    return L_rec;
}

// Select an individual sampling its index
void Find_block_L_prob(Random& rn, const vector<double>& L_rec, int& index)
{
    double limit = 0.;          // Limit of blocks
    double x = rn.Rannyu();     // Pseudo-random number to understand which block it is in

    for (int i = 0; i < int(L_rec.size()); i++)     // Loop over travels
    {
        limit += L_rec[i];       // Extend limit of one block

        // If x is in the block, parent is found
        if (x <= limit)
        {
            index = i;
            break;
        }
    }
}

// Pair permutation
Travel Pair_permutation(Random& rn, const Travel& son)
{
    Travel copy = son;  // Copy of son
    
    int index_1 = floor(rn.Rannyu(1, copy.Get_size()));     // Generate first index  
    int index_2;                                            // Second index  

    // Find second index different from the first
    do
    {
        index_2 = floor(rn.Rannyu(1, copy.Get_size()));
    } 
    while (index_1 == index_2);

    // Switch elements
    City city = copy.Get_city(index_1);                    
    copy.Set_city(index_1, copy.Get_city(index_2));
    copy.Set_city(index_2, city);

    return copy;
} 

// Shift of block of cities
Travel Shift(Random& rn, const Travel& son)
{
    // Create a variable travel without the first city
    Travel copy(int(son.Get_size() - 1)); 
    for (int i = 0; i < int(son.Get_size() - 1); i++)
        copy.Set_city(i, son.Get_city(i + 1));

        
    int n_shift = floor(rn.Rannyu(1, copy.Get_size() - 1));     // Number of positions shifted
    int index_start = floor(rn.Rannyu(0, copy.Get_size()));     // Index start block
    int n_index = floor(rn.Rannyu(1, copy.Get_size()));;        // Block dimension

    for (int i = 0; i < n_shift; i++)           // Loop over number of position shifted
    {
        for (int j = 0; j < n_index; j++)       // Loop over index within block
        {
            // Find indexes
            int index_1 = (index_start + n_index + i - j - 1)%copy.Get_size();
            int index_2 = (index_1 + 1)%copy.Get_size();

            // Switch cities
            City city = copy.Get_city(index_1);
            copy.Set_city(index_1, copy.Get_city(index_2));
            copy.Set_city(index_2, city);
        }
    }

    // Add the first city to the new travel
    Travel copy_2(int(son.Get_size()));
    copy_2.Set_city(0, son.Get_city(0));
    for (int i = 1; i < int(son.Get_size()); i++)
        copy_2.Set_city(i, copy.Get_city(i - 1));

    return copy_2;
}

// Block permutation
Travel Block_permutation(Random& rn, const Travel& son)
{
    // Create a variable travel without the fisrt city
    Travel copy(int(son.Get_size() - 1)); 
    for (int i = 0; i < int(son.Get_size() - 1); i++)
        copy.Set_city(i, son.Get_city(i + 1));

    int n_index = floor(rn.Rannyu(1, floor(copy.Get_size() / 2.) + 1));     // Block dimension
    int index_1 = floor(rn.Rannyu(0, copy.Get_size()));                     // First index of first block
    int index_2;                                                            // First index of second block

    // Loop to avoid that first indexes distant less than block dimension
    do
    {
        index_2 = floor(rn.Rannyu(0, copy.Get_size()));
    } 
    while (((index_2 >= index_1) && (index_2 < ((index_1 + n_index)%copy.Get_size()))) || ((index_1 >= index_2) && ((index_2 + n_index)%copy.Get_size() > index_1)));

    // Switch blocks
    for (int i = 0; i < n_index; i++)
    {
        City city = copy.Get_city((index_1 + i)%copy.Get_size());
        copy.Set_city((index_1 + i)%copy.Get_size(), copy.Get_city((index_2 + i)%copy.Get_size()));
        copy.Set_city((index_2 + i)%copy.Get_size(), city);
    }

    // Add the first city to the new travel
    Travel copy_2(int(son.Get_size()));
    copy_2.Set_city(0, son.Get_city(0));
    for (int i = 1; i < int(son.Get_size()); i++)
        copy_2.Set_city(i, copy.Get_city(i - 1));

    return copy_2;
}

// Inversion
Travel Inversion(Random& rn, const Travel& son)
{
    // Create a variable travel without the fisrt city
    Travel copy(int(son.Get_size() - 1)); 
    for (int i = 0; i < int(son.Get_size() - 1); i++)
        copy.Set_city(i, son.Get_city(i + 1));

    int n_index = floor(rn.Rannyu(1, copy.Get_size()));         // Block dimension
    int index_start = floor(rn.Rannyu(0, copy.Get_size()));     // Starting index 

    for (int i = 0; i < floor(n_index / 2); i++)    // Loop over switches
    {
        // Find indexes
        int index_1 = (index_start + i)%copy.Get_size();
        int index_2 = (index_start + n_index - i - 1)%copy.Get_size();

        // Switch cities
        City city = copy.Get_city(index_1);
        copy.Set_city(index_1, copy.Get_city(index_2));
        copy.Set_city(index_2, city);
    }

    // Add the first city to the new travel
    Travel copy_2(int(son.Get_size()));
    copy_2.Set_city(0, son.Get_city(0));
    for (int i = 1; i < int(son.Get_size()); i++)
        copy_2.Set_city(i, copy.Get_city(i - 1));

    return copy_2;
}

// Crossover 
vector<Travel> Crossover(Random& rn, const vector<Travel>& parents)
{
    int index = floor(rn.Rannyu(2, parents[0].Get_size()));     // Index where cut
    vector<Travel> parent_crossover;                            // Vector parents after crossover

    // Fill with same cities before index and after empty
    for (int i = 0; i < 2; i++)                  // Loop over parents
    {
        Travel parent(parents[i].Get_size());   // Create new parent

        for (int j = 0; j < index; j++)     // Loop over indexes inaltereted
            parent.Set_city(j, parents[i].Get_city(j));   

        Position pos(2);          // Empty position
        City city(-1, pos);      // Empty city
        for (int j = index; j < parent.Get_size(); j++)    // Loop over indexes to fill
            parent.Set_city(j, city);                   // Fill with empty city

        parent_crossover.push_back(parent);
    }

    // Make crossover
    for(int i = 0; i < 2; i++)          // Loop over parents
    {
        int cont = index;       // Counter
        int index_consort;      // Index consort

        // Choose consort
        if (i == 0)
            index_consort = 1;
        else 
            index_consort = 0;
        
        vector<int> index_cities_consort = parents[index_consort].Get_index_cities();             // Index cities of consort

        for(int j = 1; j < parents[0].Get_size(); j++)    // Loop over number of indexes
        {
            if (!check_index(parent_crossover[i].Get_index_cities(), index_cities_consort[j]))    // Check if the index of consort is present
            {
                parent_crossover[i].Set_city(cont, parents[index_consort].Get_city(j));           // Add city
                cont ++;
            }
        }
    }

    return parent_crossover;
}

// Print L best
void Print_L(const vector<Travel>& generation, const string& namefile)
{
    // File to print L best
	ofstream sout(namefile, ios::app);
    sout << generation[0].L_2() << endl;
    sout.close();
}

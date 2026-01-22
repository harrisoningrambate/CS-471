#ifndef POPULATION
#define POPULATION
#include <vector>
#include <random>
using namespace std;

class Population {
public: 
	Population(size_t pop_size, size_t dimensions, float dist_low, float dist_high);

	vector<vector<float>> population;
	vector<float> fitness;

};

#endif

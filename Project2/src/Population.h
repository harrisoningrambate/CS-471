#ifndef POPULATION
#define POPULATION
#include <vector>
#include <random>
using namespace std;

class Population {
public: 
	/**
	* Constructor for Population initializes population matrix to be of size pop_size x dimensions
	* and fitness vector to size pop_size
	* @param[in] pop_size, dimensions
	*/
	Population(size_t pop_size, size_t dimensions);

	vector<vector<float>> population;
	vector<float> fitness;

};

#endif

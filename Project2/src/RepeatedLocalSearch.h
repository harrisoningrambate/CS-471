// Name: Harrison Ingram-Bate
#ifndef REPEATED_LOCAL_SEARCH
#define REPEATED_LOCAL_SEARCH

#include <memory>
#include <random>
#include <chrono>
#include "Population.h"

typedef std::unique_ptr<vector<uniform_real_distribution<float>>> Distributions;

/**
* Runs Repeated Local Search on a fitness function for pop_size iterations.
* @param[in] distribution_vec, fitness function, pop_size, step_size
* @param[out] Population (contains randomly generated population and calculated fitness vector)
*/
Population RepeatedLocalSearch(Distributions distribution_vec,
							   float (*fitness)(const vector<float>&),
							   size_t pop_size,
							   float step_size);

/**
* Helper function that sets current iteration of Repeated Local Search to the best vector
* from a randomly generated population.
* @param[in] distribution_vec, fitness function, random number generator, destination vector, population size
* @param[out] distribuiton_vec
*/
Distributions  SetBestVecFromRandPop(Distributions distribution_vec,
										  float (*fitness)(const vector<float>&),
										  mt19937& rand_gen,
										  vector<float>& dest_vec,
										  size_t pop_size);

/**
* Runs local search for one iteration of Repeated Local Search
* @param[in] distribution_vec, fitness function, result vector, step_size
* @param[out] distribution_vec
*/
Distributions LocalSearch(Distributions distribution_vec,
						  float (*fitness)(const vector<float>&),
						  vector<float>& best_vec,
						  float step_size);
#endif

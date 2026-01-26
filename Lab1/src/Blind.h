#ifndef BLIND
#define BLIND

#include <random>
#include <memory>
#include <chrono>
#include "Population.h"

/**
* Runs Blind Algorithm on a fitness function for pop_size iterations.
* @param[in] distribution_vec, fitness function, pop_size
* @param[out] Population (contains randomly generated population and calculated fitness vector)
*/
Population Blind(std::unique_ptr<vector<uniform_real_distribution<float>>>  distribution_vec,
				 float (*fitness)(const vector<float>&),
				 size_t pop_size);

#endif

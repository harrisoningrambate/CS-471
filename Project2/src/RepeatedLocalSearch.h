// Name: Harrison Ingram-Bate
#ifndef REPEATED_LOCAL_SEARCH
#define REPEATED_LOCAL_SEARCH

#include <memory>
#include <random>
#include <chrono>
#include "Population.h"

typedef std::unique_ptr<vector<uniform_real_distribution<float>>> Distributions;

Population RepeatedLocalSearch(Distributions distribution_vec,
							   float (*fitness)(const vector<float>&),
							   size_t pop_size,
							   float step_size);


Distributions  SetBestVecFromRandPop(Distributions distribution_vec,
										  float (*fitness)(const vector<float>&),
										  mt19937& rand_gen,
										  vector<float>& dest_vec,
										  size_t pop_size);

Distributions LocalSearch(Distributions distribution_vec,
						  float (*fitness)(const vector<float>&),
						  vector<float>& best_vec,
						  float step_size);
#endif

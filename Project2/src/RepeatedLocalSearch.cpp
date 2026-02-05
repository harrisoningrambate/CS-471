#include "RepeatedLocalSearch.h"
#include <limits>

typedef std::unique_ptr<vector<uniform_real_distribution<float>>> UniqueDistributions;

Population RepeatedLocalSearch(UniqueDistributions distribution_vec, // distribution for each dimension
							   float (*fitness)(const vector<float>&),
							   size_t pop_size)
{
	// setup
	size_t dimensions = distribution_vec->size();
	Population return_pop(pop_size, dimensions);
	mt19937 rand_gen(std::chrono::system_clock::now().time_since_epoch().count());

	
	for (int i = 0; i < pop_size; i++) {
		// select best vector from a randomly generated population
		distribution_vec = SetBestVecFromRandPop(std::move(distribution_vec), fitness, rand_gen, return_pop.population[i], pop_size);

		// apply local bounded local search

		
		return_pop.fitness[i] = fitness(return_pop.population[i]);
	}
	
	return return_pop;
}

UniqueDistributions SetBestVecFromRandPop(UniqueDistributions distribution_vec,
										  float (*fitness)(const vector<float>&),
										  mt19937& rand_gen,
										  vector<float>& dest_vec,
										  size_t pop_size)
{
	size_t dimensions = dest_vec.size();
	vector<float> best_vec(dimensions);
	float best_fit = std::numeric_limits<float>::max();

	for (int i = 0; i < pop_size; i++) {
		vector<float> temp_vec(dimensions);
		
		// generate random vector
		for (int j = 0; j < dimensions; j++)
			temp_vec[j] = (*distribution_vec)[j](rand_gen);
		
		// keep best vector
		int curr_fit = fitness(temp_vec);
		if (curr_fit < best_fit) {
			best_fit = curr_fit;
			best_vec = std::move(temp_vec);
		}
	}

	dest_vec = std::move(best_vec);
	return std::move(distribution_vec);
}

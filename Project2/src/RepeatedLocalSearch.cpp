// Name: Harrison Ingram-Bate
#include "RepeatedLocalSearch.h"
#include <limits>

Population RepeatedLocalSearch(Distributions distribution_vec, // distribution for each dimension
							   float (*fitness)(const vector<float>&),
							   size_t pop_size,
							   float step_size)
{
	// setup
	size_t dimensions = distribution_vec->size();
	Population return_pop(pop_size, dimensions);
	mt19937 rand_gen(std::chrono::system_clock::now().time_since_epoch().count());

	
	for (int i = 0; i < pop_size; i++) {
		// select best vector from a randomly generated population
		distribution_vec = SetBestVecFromRandPop(std::move(distribution_vec), fitness, rand_gen, return_pop.population[i], pop_size);

		// apply bounded local search
		distribution_vec = LocalSearch(std::move(distribution_vec), fitness, return_pop.population[i], step_size);
		
		return_pop.fitness[i] = fitness(return_pop.population[i]);
	}
	
	return return_pop;
}

Distributions SetBestVecFromRandPop(Distributions distribution_vec,
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

Distributions LocalSearch(Distributions distribution_vec,
						  float (*fitness)(const vector<float>&),
						  vector<float>& best_vec,
						  float step_size)
{
	size_t dimensions = best_vec.size();
	float best_fit = fitness(best_vec);
	

	bool stop = false;
	do {
		// initialize temp and solution vec
		vector<float> temp_vec = best_vec;
		vector<float> solution_vec(dimensions);
		
		// get solution vector
		for (int i = 0; i < dimensions; i++) {
			temp_vec[i] += step_size;
			solution_vec[i] = best_vec[i] - step_size * (fitness(temp_vec) - best_fit);
			temp_vec[i] -= step_size;
		}

		// bound solution_vec to the dimensions
		for (int i = 0; i < dimensions; i++) {
			if (solution_vec[i] > (*distribution_vec)[i].max())
				solution_vec[i] = (*distribution_vec)[i].max();
			else if (solution_vec[i] < (*distribution_vec)[i].min())
				solution_vec[i] = (*distribution_vec)[i].min();
		}
		
		// check if there is an improvement
		float solution_fit = fitness(solution_vec);
		if (solution_fit < best_fit) {
			best_vec = std::move(solution_vec);
			best_fit = solution_fit;
		}
		else stop = true;
	}
	while (!stop);

	return std::move(distribution_vec);
}

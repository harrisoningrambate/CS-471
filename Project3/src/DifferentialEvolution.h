#ifndef DIFFERENTIAL_EVOLUTION
#define DIFFERENTIAL_EVOLUTION

#include <memory>
#include <random>
#include <chrono>
#include "Population.h"

typedef std::unique_ptr<std::vector<std::uniform_real_distribution<float>>> Distributions;

Population DifferentialEvolution(Distributions distribution_vec,
								 float (*fitness)(const vector<float>&),
								 size_t result_pop_size,
								 size_t gen_pop_size,
								 float crossover,
								 float mutation,
								 unsigned int generations,
								 unsigned int strategy
								 );

vector<float> DEbest1exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation
						 );

vector<float> DErand1exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 );
vector<float> DErandbest1exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation
						 );

vector<float> DEbest2exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation
						 );
// TODO: Implement DE/rand/2/exp
// TODO: Implement DE/best/1/bin
// TODO: Implement DE/rand/1/bin
// TODO: Implement DE/rand-to-best/1/bin
// TODO: Implement DE/best/2/bin
// TODO: Implement DE/rand/2/bin

#endif

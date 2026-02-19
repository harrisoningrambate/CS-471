// Name: Harrison Ingram-Bate
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
								 float lambda,
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
						 float mutation,
						 float lambda
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

vector<float> DErand2exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 );

vector<float> DEbest1bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation
						 );

vector<float> DErand1bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 );

vector<float> DErandbest1bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation,
						 float lambda
						 );

vector<float> DEbest2bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation
						 );

vector<float> DErand2bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 );

#endif

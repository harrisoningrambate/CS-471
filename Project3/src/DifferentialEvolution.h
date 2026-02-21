// Name: Harrison Ingram-Bate
#ifndef DIFFERENTIAL_EVOLUTION
#define DIFFERENTIAL_EVOLUTION

#include <memory>
#include <random>
#include <chrono>
#include "Population.h"

typedef std::unique_ptr<std::vector<std::uniform_real_distribution<float>>> Distributions;

/**
* Runs result_pop_size iterations of differential evolution using a given strategy number
* @param[in]distribution vec, result_pop_size, gen_pop_size, crossover, mutation, lambda, generations, strategy
* @param[out] the resulting population of result_pop_size iterations holding the best value from each iteration
*/
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

/**
* The first strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, best_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
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

/**
* The second strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
vector<float> DErand1exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 );

/**
* The third strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, best_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
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

/**
* The fourth strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, best_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
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

/**
* The fifth strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
vector<float> DErand2exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 );

/**
* The sixth strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, best_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
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

/**
* The seventh strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
vector<float> DErand1bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 );

/**
* The eighth strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, best_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
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

/**
* The ninth strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, best_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
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

/**
* The tenth strategy for the crossover in Differential Evolution.
* @param[in] current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, curr_index, crossover, mutation
* @param[out] the resulting trial vector from a crossover.
*/
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

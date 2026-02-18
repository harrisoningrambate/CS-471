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

#endif

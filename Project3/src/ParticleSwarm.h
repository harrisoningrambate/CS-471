#ifndef PARTICLE_SWARM
#define PARTICLE_SWARM

#include <memory>
#include <random>
#include <chrono>
#include "Population.h"

typedef std::unique_ptr<std::vector<std::uniform_real_distribution<float>>> Distributions;

Population RepeatedParticleSwarm(Distributions distribution_vec,
						 float (*fitness)(const vector<float>&),
						 size_t result_size,
						 size_t particles,
						 float c1,
						 float c2,
						 float slowing_factor,
						 int generations);

Distributions ParticleSwarm(Distributions distribution_vec,
							float (*fitness)(const vector<float>&),
							uniform_real_distribution<float>& zero_to_one,
							mt19937& rand_gen,
							Population& particle_gen,
							Population& pBest,
							vector<vector<float>> velocity,
							int& global_best,
							float c1,
							float c2,
							float slowing_factor,
							int iterations);

#endif

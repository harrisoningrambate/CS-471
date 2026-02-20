#ifndef PARTICLE_SWARM
#define PARTICLE_SWARM

#include <memory>
#include <random>
#include <chrono>
#include "Population.h"

typedef std::unique_ptr<std::vector<std::uniform_real_distribution<float>>> Distributions;

Population ParticleSwarm(Distributions distribution_vec,
						 float (*fitness)(const vector<float>&),
						 size_t result_size,
						 size_t particles,
						 float c1,
						 float c2,
						 float w,
						 int generations);

#endif

#include "ParticleSwarm.h"

Population ParticleSwarm(Distributions distribution_vec,
						 float (*fitness)(const vector<float>&),
						 size_t result_size,
						 size_t particles,
						 float c1,
						 float c2,
						 float w,
						 int generations)
{
	// setup
	size_t dimensions = distribution_vec->size();
	Population result_pop(result_size, dimensions);
	Population current_gen(particles, dimensions);
	Population next_gen(particles, dimensions);
	

	return result_pop;
}

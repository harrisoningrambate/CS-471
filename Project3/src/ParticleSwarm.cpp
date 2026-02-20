#include "ParticleSwarm.h"
#include <iostream>
#include <iomanip>

Population RepeatedParticleSwarm(Distributions distribution_vec,
						 float (*fitness)(const vector<float>&),
						 size_t result_size,
						 size_t particles,
						 float c1,
						 float c2,
						 float slowing_factor,
						 int generations)
{
	// setup
	int dimensions = distribution_vec->size();
	Population result_pop(result_size, dimensions);
	Population particle_gen(particles, dimensions);
	vector<vector<float>> velocity(particles, vector<float>(dimensions));
	Population pBest(particles, dimensions);
	int best_index;
	mt19937 rand_gen(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_real_distribution<float> zero_to_one(0.0f, 1.0f);

	
	for (int i = 0; i < result_size; i++) {
		// run ParticleSwarm
		distribution_vec = ParticleSwarm(std::move(distribution_vec), fitness, zero_to_one, rand_gen, particle_gen, pBest, velocity, best_index, c1, c2, slowing_factor, generations);

		result_pop.population[i] = pBest.population[best_index];
		result_pop.fitness[i] = pBest.fitness[best_index];
	}
	

	return result_pop;
}

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
							int iterations)
{
	// constants
	int particles = particle_gen.population.size();
	int dimensions = distribution_vec->size();

	// initialize particles and starting velocities
	for (int i = 0; i < particles; i++) {
		for (int j = 0; j < dimensions; j++) {
			particle_gen.population[i][j] = (*distribution_vec)[j](rand_gen);
			velocity[i][j] = 0.5f * zero_to_one(rand_gen) * ((*distribution_vec)[j].max() - (*distribution_vec)[j].min());
		}
		particle_gen.fitness[i] = fitness(particle_gen.population[i]);

		// set pBest to the initial values of particle_gen
		pBest.population[i] = particle_gen.population[i];
		pBest.fitness[i] = particle_gen.fitness[i];
	}

	// get the index of global_best
	global_best = 0;
	for (int i = 1; i < particles; i++) {
		if (pBest.fitness[i] < pBest.fitness[global_best])
			global_best = i;
	}

	
	for (int i = 0; i < iterations; i++) {
		for (int j = 0; j < particles; j++) {
			for (int k = 0; k < dimensions; k++) {
				// calculate the new velocity
				velocity[j][k] = slowing_factor * (velocity[j][k] + c1 * zero_to_one(rand_gen) * (pBest.population[j][k] - particle_gen.population[j][k])
					+ c2 * zero_to_one(rand_gen) * (pBest.population[global_best][k] - particle_gen.population[j][k]));

				// update and bound particle
				particle_gen.population[j][k] += velocity[j][k];
				if (particle_gen.population[j][k] > (*distribution_vec)[k].max())
					particle_gen.population[j][k] = (*distribution_vec)[k].max();
				else if (particle_gen.population[j][k] < (*distribution_vec)[k].min())
					particle_gen.population[j][k] = (*distribution_vec)[k].min();
			}
			
			// calculate particles fitness
			particle_gen.fitness[j] = fitness(particle_gen.population[j]);

			// check if fitness has improved
			if (particle_gen.fitness[j] < pBest.fitness[j]) {
				pBest.population[j] = particle_gen.population[j];
				pBest.fitness[j] = particle_gen.fitness[j];

				// check if gBest has improved
				if (pBest.fitness[j] < pBest.fitness[global_best])
					global_best = j;
			}
		}
		std::cout << std::fixed << std::setprecision(2);
		std::cout << "Best Fit in after " << i << " migrations: " << pBest.fitness[global_best] << "\n";
	}

	return std::move(distribution_vec);
}

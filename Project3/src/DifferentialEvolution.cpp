#include "DifferentialEvolution.h"
#include <limits>
#include <iostream>
#include <iomanip>

Population DifferentialEvolution(Distributions distribution_vec,
								 float (*fitness)(const vector<float>&),
								 size_t result_pop_size,
								 size_t gen_pop_size,
								 float crossover,
								 float mutation,
								 unsigned int generations,
								 unsigned int strategy
								 )
{
	// setup
	size_t dimensions = distribution_vec->size();
	Population result_pop(result_pop_size, dimensions);
	mt19937 rand_gen(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> pop_index_distribution(0, gen_pop_size - 1);
	uniform_int_distribution<int> dimension_index_distribution(0, dimensions - 1);
	uniform_real_distribution<float> crossover_distribution(0.0f, 1.0f);

	// allocate space for two generations and noisy vec
	Population current_gen(gen_pop_size, dimensions);
	Population next_gen(gen_pop_size, dimensions);
	vector<float> noisy_vec(dimensions);
	
	for (int result = 0; result < result_pop_size; result++) {
		// generate random initial population
		for (int i = 0; i < gen_pop_size; i++) {
			for (int j = 0; j < dimensions; j++)
				current_gen.population[i][j] = (*distribution_vec)[j](rand_gen);
			current_gen.fitness[i] = fitness(current_gen.population[i]);
		}

		// TODO: Implement the 10 strategies as separate functions that return a trial vector
		int best_index;
		for (int gen = 0; gen < generations; gen++) {
			// track best fit and its index in current gen
			float best_fit = numeric_limits<float>::max();
			for (int i = 0; i < gen_pop_size; i++) {
				if (current_gen.fitness[i] < best_fit) {
					best_fit = current_gen.fitness[i];
					best_index = i;
				}
			}
			// NOTE: REMOVE WHEN FINISHED
			cout << std::fixed << std::setprecision(2);
			cout << "Best Vec for gen " << gen << " " << current_gen.fitness[best_index] << " | <";
			for (int j = 0; j < dimensions - 1; j++) {
				cout << current_gen.population[best_index][j] << ", ";
			}
			cout << current_gen.population[best_index][dimensions - 1] << ">\n";

			for (int i = 0; i <  gen_pop_size; i++) {
				// NOTE: This is DE/best/1/exp
				
				// select r1 and r2
				int r1 = i;
				while (r1 == i)
					r1 = pop_index_distribution(rand_gen);
				int r2 = i;
				while (r2 == i || r2 == r1)
					r2 = pop_index_distribution(rand_gen);
				
				// generate noisy vec
				for (int j = 0; j < dimensions; j++) {
					noisy_vec[j] = mutation * (current_gen.population[r2][j] - current_gen.population[r1][j]);
					noisy_vec[j] += current_gen.population[best_index][j];
				}

				// crossover
				vector<float> trial_vec = current_gen.population[i];
				int start_index = dimension_index_distribution(rand_gen);
				int components = 0;
				do {
					int index = (start_index + components) % dimensions;
					trial_vec[index] = noisy_vec[index];
					components++;
				} while (crossover_distribution(rand_gen) < crossover && components < dimensions);
				// NOTE: End DE/best/1/exp

				// bound trial vec
				for (int j = 0; j < dimensions; j++) {
					if (trial_vec[j] > (*distribution_vec)[j].max())
						trial_vec[j] = (*distribution_vec)[j].max();
					else if (trial_vec[j] < (*distribution_vec)[j].min())
						trial_vec[j] = (*distribution_vec)[j].min();
				}

				// Select either trial_vec  or current_gen vec for next_gen
				float trial_fit = fitness(trial_vec);
				if (trial_fit < current_gen.fitness[i]) {
					next_gen.population[i] = std::move(trial_vec);
					next_gen.fitness[i] = trial_fit;
				} else {
					next_gen.population[i] = current_gen.population[i];
					next_gen.fitness[i] = current_gen.fitness[i];
				}
			}

			// swap next_gen and current gen for next iteration
			Population temp_gen = std::move(current_gen);
			current_gen = std::move(next_gen);
			next_gen = std::move(temp_gen);
		}
		
		// add best vector from last generation to the result population
		result_pop.population[result] = current_gen.population[best_index];
		result_pop.fitness[result] = current_gen.fitness[best_index];
	}

	return result_pop;
}

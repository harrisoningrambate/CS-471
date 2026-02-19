// Name: Harrison Ingram-Bate
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
								 float lambda,
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
	
	for (int result = 0; result < result_pop_size; result++) {
		std::cout << "Running iteration " << result + 1 << " of " << result_pop_size << " with " << generations << " generations...\n";
		// generate random initial population
		for (int i = 0; i < gen_pop_size; i++) {
			for (int j = 0; j < dimensions; j++)
				current_gen.population[i][j] = (*distribution_vec)[j](rand_gen);
			current_gen.fitness[i] = fitness(current_gen.population[i]);
		}

		// get the starting best_index
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
			
			// get trial vector specific to the strategy we're using
			for (int i = 0; i <  gen_pop_size; i++) {
				vector<float> trial_vec;
				switch (strategy) {
					case 1:
						trial_vec = DEbest1exp(current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, i, best_index, crossover, mutation);
						break;
					case 2:
						trial_vec = DErand1exp(current_gen, pop_index_distribution, dimension_index_distribution,crossover_distribution, rand_gen, i, crossover, mutation);
						break;
					case 3:
						trial_vec = DErandbest1exp(current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, i, best_index, crossover, mutation, lambda);
						break;
					case 4:
						trial_vec = DEbest2exp(current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, i, best_index, crossover, mutation);
						break;
					case 5:
						trial_vec = DErand2exp(current_gen, pop_index_distribution, dimension_index_distribution,crossover_distribution, rand_gen, i, crossover, mutation);
					case 6:
						trial_vec = DEbest1bin(current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, i, best_index, crossover, mutation);
						break;
					case 7:
						trial_vec = DErand1bin(current_gen, pop_index_distribution, dimension_index_distribution,crossover_distribution, rand_gen, i, crossover, mutation);
						break;
					case 8:
						trial_vec = DErandbest1bin(current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, i, best_index, crossover, mutation, lambda);
						break;
					case 9:
						trial_vec = DEbest2bin(current_gen, pop_index_distribution, dimension_index_distribution, crossover_distribution, rand_gen, i, best_index, crossover, mutation);
						break;
					case 10:
						trial_vec = DErand2bin(current_gen, pop_index_distribution, dimension_index_distribution,crossover_distribution, rand_gen, i, crossover, mutation);
				}

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

			// update best index for next gen
			for (int gen = 0; gen < generations; gen++) {
				// track best fit and its index in current gen
				float best_fit = numeric_limits<float>::max();
				for (int i = 0; i < gen_pop_size; i++) {
					if (current_gen.fitness[i] < best_fit) {
						best_fit = current_gen.fitness[i];
						best_index = i;
					}
				}
			}
		}
		
		// add best vector from last generation to the result population
		result_pop.population[result] = current_gen.population[best_index];
		result_pop.fitness[result] = current_gen.fitness[best_index];
	}


	return result_pop;
}

vector<float> DEbest1exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1 and r2
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);

	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r2][j] - current_gen.population[r1][j]);
		noisy_vec[j] += current_gen.population[best_index][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	int start_index = dimension_index_distribution(rand_gen);
	int components = 0;
	do {
		int index = (start_index + components) % dimensions;
		trial_vec[index] = noisy_vec[index];
		components++;
	} while (crossover_distribution(rand_gen) < crossover && components < dimensions);

	return std::move(trial_vec);
}

vector<float> DErand1exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1, r2, and r3
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);
	int r3 = curr_index;
	while (r3 == curr_index || r3 == r1 || r3 == r2)
		r3 = pop_index_distribution(rand_gen);

	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r2][j] - current_gen.population[r1][j]);
		noisy_vec[j] += current_gen.population[r3][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	int start_index = dimension_index_distribution(rand_gen);
	int components = 0;
	do {
		int index = (start_index + components) % dimensions;
		trial_vec[index] = noisy_vec[index];
		components++;
	} while (crossover_distribution(rand_gen) < crossover && components < dimensions);

	return std::move(trial_vec);
}

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
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1, r2, and r3
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);
	
	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r2][j] - current_gen.population[r1][j]);
		noisy_vec[j] = lambda * (current_gen.population[best_index][j] - current_gen.population[curr_index][j]);
		noisy_vec[j] += current_gen.population[curr_index][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	int start_index = dimension_index_distribution(rand_gen);
	int components = 0;
	do {
		int index = (start_index + components) % dimensions;
		trial_vec[index] = noisy_vec[index];
		components++;
	} while (crossover_distribution(rand_gen) < crossover && components < dimensions);

	return std::move(trial_vec);
}

vector<float> DEbest2exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1 and r2
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);
	int r3 = curr_index;
	while (r3 == curr_index || r3 == r1 || r3 == r2)
		r3 = pop_index_distribution(rand_gen);
	int r4 = curr_index;
	while (r4 == curr_index || r4 == r1 || r4 == r2 || r4 == r3)
		r4 = pop_index_distribution(rand_gen);

	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r1][j] + current_gen.population[r2][j] - current_gen.population[r3][j] - current_gen.population[r4][j]);
		noisy_vec[j] += current_gen.population[best_index][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	int start_index = dimension_index_distribution(rand_gen);
	int components = 0;
	do {
		int index = (start_index + components) % dimensions;
		trial_vec[index] = noisy_vec[index];
		components++;
	} while (crossover_distribution(rand_gen) < crossover && components < dimensions);

	return std::move(trial_vec);
}

vector<float> DErand2exp(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1 and r2
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);
	int r3 = curr_index;
	while (r3 == curr_index || r3 == r1 || r3 == r2)
		r3 = pop_index_distribution(rand_gen);
	int r4 = curr_index;
	while (r4 == curr_index || r4 == r1 || r4 == r2 || r4 == r3)
		r4 = pop_index_distribution(rand_gen);
	int r5 = curr_index;
	while (r5 == curr_index || r5 == r1 || r5 == r2 || r5 == r3 || r5 == r4)
		r5 = pop_index_distribution(rand_gen);

	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r1][j] + current_gen.population[r2][j] - current_gen.population[r3][j] - current_gen.population[r4][j]);
		noisy_vec[j] += current_gen.population[r5][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	int start_index = dimension_index_distribution(rand_gen);
	int components = 0;
	do {
		int index = (start_index + components) % dimensions;
		trial_vec[index] = noisy_vec[index];
		components++;
	} while (crossover_distribution(rand_gen) < crossover && components < dimensions);

	return std::move(trial_vec);
}

vector<float> DEbest1bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1 and r2
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);

	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r2][j] - current_gen.population[r1][j]);
		noisy_vec[j] += current_gen.population[best_index][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	for (int i = 0; i < dimensions; i++) {
		if (crossover_distribution(rand_gen) < crossover)
			trial_vec[i] = noisy_vec[i];
	}

	return std::move(trial_vec);
}

vector<float> DErand1bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1, r2, and r3
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);
	int r3 = curr_index;
	while (r3 == curr_index || r3 == r1 || r3 == r2)
		r3 = pop_index_distribution(rand_gen);

	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r2][j] - current_gen.population[r1][j]);
		noisy_vec[j] += current_gen.population[r3][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	for (int i = 0; i < dimensions; i++) {
		if (crossover_distribution(rand_gen) < crossover)
			trial_vec[i] = noisy_vec[i];
	}

	return std::move(trial_vec);
}

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
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1, r2, and r3
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);
	
	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r2][j] - current_gen.population[r1][j]);
		noisy_vec[j] = lambda * (current_gen.population[best_index][j] - current_gen.population[curr_index][j]);
		noisy_vec[j] += current_gen.population[curr_index][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	for (int i = 0; i < dimensions; i++) {
		if (crossover_distribution(rand_gen) < crossover)
			trial_vec[i] = noisy_vec[i];
	}

	return std::move(trial_vec);
}

vector<float> DEbest2bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 int best_index,
						 float crossover,
						 float mutation
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1 and r2
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);
	int r3 = curr_index;
	while (r3 == curr_index || r3 == r1 || r3 == r2)
		r3 = pop_index_distribution(rand_gen);
	int r4 = curr_index;
	while (r4 == curr_index || r4 == r1 || r4 == r2 || r4 == r3)
		r4 = pop_index_distribution(rand_gen);

	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r1][j] + current_gen.population[r2][j] - current_gen.population[r3][j] - current_gen.population[r4][j]);
		noisy_vec[j] += current_gen.population[best_index][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	for (int i = 0; i < dimensions; i++) {
		if (crossover_distribution(rand_gen) < crossover)
			trial_vec[i] = noisy_vec[i];
	}

	return std::move(trial_vec);
}

vector<float> DErand2bin(Population& current_gen,
						 uniform_int_distribution<int>& pop_index_distribution,
						 uniform_int_distribution<int>& dimension_index_distribution,
						 uniform_real_distribution<float>& crossover_distribution,
						 mt19937& rand_gen,
						 int curr_index,
						 float crossover,
						 float mutation
						 )
{
	int dimensions = current_gen.population[curr_index].size();

	// select r1 and r2
	int r1 = curr_index;
	while (r1 == curr_index)
		r1 = pop_index_distribution(rand_gen);
	int r2 = curr_index;
	while (r2 == curr_index || r2 == r1)
		r2 = pop_index_distribution(rand_gen);
	int r3 = curr_index;
	while (r3 == curr_index || r3 == r1 || r3 == r2)
		r3 = pop_index_distribution(rand_gen);
	int r4 = curr_index;
	while (r4 == curr_index || r4 == r1 || r4 == r2 || r4 == r3)
		r4 = pop_index_distribution(rand_gen);
	int r5 = curr_index;
	while (r5 == curr_index || r5 == r1 || r5 == r2 || r5 == r3 || r5 == r4)
		r5 = pop_index_distribution(rand_gen);

	// generate noisy vec
	vector<float> noisy_vec(dimensions);
	for (int j = 0; j < dimensions; j++) {
		noisy_vec[j] = mutation * (current_gen.population[r1][j] + current_gen.population[r2][j] - current_gen.population[r3][j] - current_gen.population[r4][j]);
		noisy_vec[j] += current_gen.population[r5][j];
	}

	// crossover
	vector<float> trial_vec = current_gen.population[curr_index];
	for (int i = 0; i < dimensions; i++) {
		if (crossover_distribution(rand_gen) < crossover)
			trial_vec[i] = noisy_vec[i];
	}

	return std::move(trial_vec);
}

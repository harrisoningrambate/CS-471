// Name: Harrison Ingram-Bate
#include <vector>
#include <numeric>
#include <limits>
#include <random>
#include <chrono>
#include <cmath>
#include "ACO.h"

#include <iostream>

FShop ACO(FShop& fs,
		  std::size_t num_ants,
		  int iterations,
		  float alpha,
		  float beta,
		  float evaporation,
		  float q) {
	std::size_t job_count = fs.f_shop.size();
	std::size_t machine_count = fs.f_shop[0].size();

	// Initialize pheromones
	float init_pheromone = 1.0f / (evaporation * fs.makespan);
	std::vector<std::vector<float>> attractiveness(job_count, std::vector<float>(job_count, init_pheromone));
	
	// heuristic visibility based off normalized total processing time
	std::vector<float> heuristic(job_count);
	float max_total = 0.0f;
	std::vector<float> total_times(job_count);
	for (std::size_t i = 0; i < job_count; i++) {
		total_times[i] = std::accumulate(fs.f_shop[i].begin(), fs.f_shop[i].end(), 0);
		max_total = std::max(max_total, total_times[i]);
	}
	for (std::size_t i = 0; i < job_count; i++) {
		heuristic[i] = total_times[i] / (max_total);
	}
	
	// initialize global best job order and makespan
	std::vector<std::size_t> gbest_job_order;
	unsigned int gbest_makespan = std::numeric_limits<unsigned int>::max();
	
	std::mt19937 rand_gen(std::chrono::system_clock::now().time_since_epoch().count());

	// run iterations iterations of ACO
	for (int iteration = 0; iteration < iterations; iteration++) {
		std::vector<std::vector<std::size_t>> ant_solutions(num_ants);
		std::vector<unsigned int> ant_makespans(num_ants);

		for (std::size_t ant = 0; ant < num_ants; ant++) {
			std::vector<std::size_t> job_order;
			std::vector<bool> visited(job_count, false);

			// select a job ordering for current ant
			for (std::size_t i = 0; i < job_count; i++) {
				std::vector<float> probabilities;
				float total_weight = 0.0f;

				// calc probabilities for unordered jobs
				for (int j = 0; j < job_count; j++) {
					if (!visited[j]) {
						float weight = std::pow(attractiveness[j][i], alpha) * std::pow(heuristic[j], beta);
						probabilities.push_back(weight);
						total_weight += weight;
					} else probabilities.push_back(0.0f);
				}

				// Roulette Wheel selection
				std::uniform_real_distribution<float> dist(0.0, total_weight);
				double picked = dist(rand_gen);
				double sum = 0.0f;
				int selected_job = -1;

				for (std::size_t j = 0; j < job_count; j++) {
					sum += probabilities[j];
					if (picked <= sum && !visited[j]) {
						selected_job = j;
						break;
					}
				}

				// add job to job ordering
				job_order.push_back(selected_job);
				visited[selected_job] = true;
			}

			// add current ant solution and calculate its makespan
			ant_solutions[ant] = std::move(job_order);
			ant_makespans[ant] = fs.calcMakespan(fs.f_shop, ant_solutions[ant]);

			// update global best
			if (ant_makespans[ant] < gbest_makespan)  {
				gbest_makespan = ant_makespans[ant];
				gbest_job_order = ant_solutions[ant];
			}
		}

		// pheromone evaporation
		for (int i = 0; i < job_count; i++) {
			for (int j = 0; j < job_count; j++) {
				attractiveness[i][j] *= (1.0 - evaporation);
			}
		}

		// pheromone update
		for (std::size_t ant = 0; ant < num_ants; ant++) {
			float deposit = q / ant_makespans[ant];
			for (std::size_t j = 0; j < job_count; j++) {
				std::size_t job = ant_solutions[ant][j];
				attractiveness[job][j] += deposit;
			}
		}

		std::cout << "Best Makespan after " << iteration << " iterations of ant colony: " << gbest_makespan << std::endl;
	}

	// initialize new FShop with ACO gbest job order
	FShop aco_fs(job_count, machine_count, fs.calcMakespan);
	for (std::size_t i = 0; i < job_count; i++) {
		aco_fs.f_shop[i] = std::move(fs.f_shop[gbest_job_order[i]]);
	}
	aco_fs.updateMakespan();

	return aco_fs;
}

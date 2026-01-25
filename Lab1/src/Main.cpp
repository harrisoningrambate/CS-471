#include <iostream>
#include <memory>
#include <random>
#include "Population.h"
#include "Problem.h"
#include "Blind.h"

int main() {
	int prob_num = 1;
	
	float (*fitness_calc)(const vector<float>&);
	switch (prob_num) {
		case 1:
			fitness_calc = Schwefel;	
			break;
		case 2:
			fitness_calc = FirstDeJong;
			break;
		case 3:
			fitness_calc = Rosenbrock;
			break;
		case 4:
			fitness_calc = Rastrigin;
			break;
		case 5:
			fitness_calc = Griewangk;
			break;
		case 6:
			fitness_calc = SineEnvelope;
			break;
		case 7:
			fitness_calc = StretchedV;
			break;
		case 8:
			fitness_calc = AckleyOne;
			break;
		case 9:
			fitness_calc = AckleyTwo;
			break;
		case 10:
			fitness_calc = EggHolder;
			break;
		default:
			std::cout << "invalid problem number" << std::endl;
			return 1;
	}

	std::unique_ptr<vector<uniform_real_distribution<float>>> distributions = std::make_unique<vector<uniform_real_distribution<float>>>();
	distributions->resize(5);
	(*distributions)[0] = uniform_real_distribution<float>(-100, 100);
	(*distributions)[1] = uniform_real_distribution<float>(-100, 100);
	(*distributions)[2] = uniform_real_distribution<float>(-100, 100);
	(*distributions)[3] = uniform_real_distribution<float>(-100, 100);
	(*distributions)[4] = uniform_real_distribution<float>(-100, 100);
	Population results = Blind(std::move(distributions), fitness_calc, 5);

	for (int i = 0; i < results.population.size(); i++) {
		results.fitness[i] = fitness_calc(results.population[i]);
	}
	std::cout << "\nFitness\n"; 
	
	for (int i = 0; i < results.population.size(); i++) {
		std::cout << std::fixed << results.fitness[i] << " ";
	}
	std::cout << std::endl;

	// output data
	return 0;
}

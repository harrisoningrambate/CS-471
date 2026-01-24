#include <iostream>
#include "Population.h"
#include "Problem.h"

int main() {
	// read input data
	// generate population vectors
	Population pop_test(5, 5, -100, 100);
	// calculate fitness
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


	for (int i = 0; i < pop_test.population.size(); i++) {
		pop_test.fitness[i] = fitness_calc(pop_test.population[i]);
	}
	std::cout << "\nFitness\n"; 
	
	for (int i = 0; i < pop_test.population.size(); i++) {
		std::cout << std::fixed << pop_test.fitness[i] << " ";
	}
	std::cout << std::endl;

	// output data
	return 0;
}

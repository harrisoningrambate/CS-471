#include <iostream>
#include "Population.h"
#include "Problem.h"

int main() {
	// read input data
	// generate population vectors
	Population pop_test(5, 5, -100, 100);
	// calculate fitness
	for (int i = 0; i < pop_test.population.size(); i++) {
		for (int j = 0; j < pop_test.population[i].size(); j++)
			std::cout << pop_test.population[i][j] << " ";
		std::cout << std::endl << std::endl;
	}

	for (int i = 0; i < pop_test.population.size(); i++) {
		pop_test.fitness[i] = AckleyTwo(pop_test.population[i]);
	}
	std::cout << "\nFitness\n"; 
	
	for (int i = 0; i < pop_test.population.size(); i++) {
		std::cout << std::fixed << pop_test.fitness[i] << " ";
	}
	std::cout << std::endl;

	// output data
	return 0;
}

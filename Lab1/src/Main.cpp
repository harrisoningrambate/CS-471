#include <iostream>
#include "Population.h"
#include "Problem.h"

int main() {
	// read input data
	// generate population vectors
	Population pop_test(5, 5);
	// calculate fitness
	for (int i = 0; i < pop_test.population.size(); i++) {
		for (int j = 0; j < pop_test.population[i].size(); j++)
			std::cout << pop_test.population[i][j] << " ";
		std::cout << std::endl << std::endl;
	}

	std::cout << "1st De Jong's result: " << FirstDeJong(pop_test.population[0]) << std::endl;
	// output data
	return 0;
}

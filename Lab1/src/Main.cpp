#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <random>
#include "Population.h"
#include "Problem.h"
#include "Blind.h"


std::unique_ptr<std::vector<uniform_real_distribution<float>>> processInputFile(std::string& file_name, size_t& pop_size, int& prob_num);

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "invalid number of arguments\n";
		return 1;
	}

	std::string file_name(argv[1]);
	size_t pop_size;
	int prob_num = 0;
	std::unique_ptr<std::vector<uniform_real_distribution<float>>> distributions = processInputFile(file_name, pop_size, prob_num);

	float (*fitness_calc)(const vector<float>&);
	switch (prob_num) {
		case 1:
			fitness_calc = Schwefel;	
			std::cout << "Schwefel\n";
			break;
		case 2:
			fitness_calc = FirstDeJong;
			std::cout << "First De Jong's\n";
			break;
		case 3:
			fitness_calc = Rosenbrock;
			std::cout << "Rosenbrock\n";
			break;
		case 4:
			fitness_calc = Rastrigin;
			std::cout << "Rastrigin\n";
			break;
		case 5:
			fitness_calc = Griewangk;
			std::cout << "Griewangk\n";
			break;
		case 6:
			fitness_calc = SineEnvelope;
			std::cout << "Sine Envelope\n";
			break;
		case 7:
			fitness_calc = StretchedV;
			std::cout << "Stretched V\n";
			break;
		case 8:
			fitness_calc = AckleyOne;
			std::cout << "Ackley's One\n";
			break;
		case 9:
			fitness_calc = AckleyTwo;
			std::cout << "Ackley's Two\n";
			break;
		case 10:
			fitness_calc = EggHolder;
			std::cout << "Egg Holder\n";
			break;
		default:
			std::cout << "invalid problem number" << std::endl;
			return 1;
	}

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


std::unique_ptr<std::vector<uniform_real_distribution<float>>> processInputFile(std::string& file_name, size_t& pop_size, int& prob_num) {
	std::ifstream input_file(file_name);

	// if file fails to open print error message and exit early.
	if (!input_file.is_open()) {
		std::cout << "Failed to open input file.\n";
		exit(EXIT_FAILURE);
	}

	std::string token;

	// read problem number from input
	std::getline(input_file, token, ',');
	prob_num = std::stoi(token);

	// read population size from input
	std::getline(input_file, token, ',');
	pop_size = std::stoi(token);

	// read dimension count from input
	std::getline(input_file, token);
	size_t dimensions = std::stoi(token);

	std::unique_ptr<vector<uniform_real_distribution<float>>> distribution_vec = std::make_unique<vector<uniform_real_distribution<float>>>();
	distribution_vec->resize(dimensions);
	float low_distribution;
	float high_distribution;
	for (int i = 0; i < dimensions; i++) {
		// get low and high distribution values for dimension[i]
		std::getline(input_file, token, ',');
		low_distribution = std::stof(token);
		std::getline(input_file, token);
		float high_distribution = std::stof(token);

		// create a distribuiton for dimension[i]
		(*distribution_vec)[i] = uniform_real_distribution<float>(low_distribution, high_distribution);
	}


	return std::move(distribution_vec);
}

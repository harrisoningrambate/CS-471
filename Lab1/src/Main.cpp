#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <memory>
#include <random>
#include "Population.h"
#include "Problem.h"
#include "Blind.h"


std::unique_ptr<std::vector<uniform_real_distribution<float>>> processInputFile(std::string& file_name, size_t& pop_size, int& prob_num);

typedef float (*FitnessFunctionPtr)(const vector<float>&);
FitnessFunctionPtr problemFunction(int prob_num);

// TODO: Output function to put results in a output CSV file

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "invalid number of arguments\n";
		return 1;
	}

	std::string file_name(argv[1]);
	size_t pop_size;
	int prob_num = 0;
	std::unique_ptr<std::vector<uniform_real_distribution<float>>> distributions = processInputFile(file_name, pop_size, prob_num);
	FitnessFunctionPtr fitness = problemFunction(prob_num);

	Population results = Blind(std::move(distributions), fitness, pop_size);
	std::cout << pop_size << "\n\n";

	std::cout << "Fitness\n"; 

	std::cout << std::fixed << std::setprecision(2);
	for (int i = 0; i < pop_size; i++) {
		std::cout << "< ";
		for (int j = 0; j < results.population[i].size() - 1; j++) {
			std::cout << results.population[i][j] << ", ";
		}
		std::cout << results.population[i][results.population[i].size() - 1] << " > | "; 
		std::cout << results.fitness[i] << "\n";
	}

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

FitnessFunctionPtr problemFunction(int prob_num) {
	float (*fitness)(const vector<float>&);
	switch (prob_num) {
		case 1:
			fitness = Schwefel;	
			break;
		case 2:
			fitness = FirstDeJong;
			break;
		case 3:
			fitness = Rosenbrock;
			break;
		case 4:
			fitness = Rastrigin;
			break;
		case 5:
			fitness = Griewangk;
			break;
		case 6:
			fitness = SineEnvelope;
			break;
		case 7:
			fitness = StretchedV;
			break;
		case 8:
			fitness = AckleyOne;
			break;
		case 9:
			fitness = AckleyTwo;
			break;
		case 10:
			fitness = EggHolder;
			break;
		default:
			std::cout << "invalid problem number\n";
			exit(EXIT_FAILURE);
	}

	return fitness;
}

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <memory>
#include <random>
#include "Population.h"
#include "Problem.h"
#include "Blind.h"
#include "RepeatedLocalSearch.h"


/**
* Processes an input file assigning population assigning population size and problem number.
* @param[in] file_name, pop_size, prob_num
* @param[out] vector<distributions> (each dimension can have its own distribution)
*/
std::unique_ptr<std::vector<uniform_real_distribution<float>>> processInputFile(std::string& file_name, size_t& pop_size, int& prob_num);

typedef float (*FitnessFunctionPtr)(const vector<float>&);
/**
* Matches a problem number to its correlating Fitness function
* @param[in] prob_num
* @param[out] fitness function
*/
FitnessFunctionPtr problemFunction(int prob_num);

/**
* Outputs result fitness and population to output file in output directory.
* @param[in] file_output
*/
void logResults(Population& pop, std::string file_output);

int main(int argc, char* argv[]) {
	// ensure correct argument count
	if (argc < 2) {
		std::cout << "invalid number of arguments\n";
		return 1;
	}

	// get algorithm to run
	int algo_num;
	if (argc < 3) {
		std::cout << "Input algorithm to use as a number\n1: Blind\n2: Repeated Local Search\n";
		std::cin >> algo_num;
	} else {
		algo_num = stoi(argv[2]);
	}
	
	// create input and output file location strings
	std::string file_input(argv[1]);
	std::string file_output = "output/" + file_input;
	file_input = "input/" + file_input;

	// Problem setup
	size_t pop_size;
	int prob_num;
	std::unique_ptr<std::vector<uniform_real_distribution<float>>> distributions = processInputFile(file_input, pop_size, prob_num);
	FitnessFunctionPtr fitness = problemFunction(prob_num);

	// run selected algorithm
	Population results(0,0);
	switch (algo_num) {
		case 1:
			results = Blind(std::move(distributions), fitness, pop_size);
			break;
		case 2:
			results = RepeatedLocalSearch(std::move(distributions), fitness, pop_size);
			break;
		default:
			std::cout << "Invalid algorithm number\n";
			break;
	}
	// output results each line is fitness[i],vector[i][0],...,vector[i][j-1]
	logResults(results, file_output);

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

void logResults(Population& pop, std::string file_output) {
	std::ofstream out_file(file_output);

	if (out_file.is_open()) {
		out_file << std::fixed << std::setprecision(2);
		for (int i = 0; i < pop.population.size(); i++) {
			out_file << pop.fitness[i] << ',';
			for (int j = 0; j < pop.population[i].size() - 1; j++) {
				out_file << pop.population[i][j] << ',';
			}
			out_file << pop.population[i][pop.population[i].size() - 1] << std::endl;
		}
		out_file.close();
	} else
		std::cout << "Failed to open the output file.";
}

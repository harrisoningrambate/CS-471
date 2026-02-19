// Name: Harrison Ingram-Bate
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <memory>
#include <random>
#include "Population.h"
#include "Problem.h"
#include "DifferentialEvolution.h"


/**
* Processes an input file assigning population size, distributions, problem number, and step size.
* @param[in] file_name, pop_size, prob_num, step_size
* @param[out] vector<distributions> (each dimension can have its own distribution)
*/
std::unique_ptr<std::vector<uniform_real_distribution<float>>> processInputFile(std::string& file_name, size_t& pop_size, size_t& gen_pop_size, int& prob_num, float& mutation, float& crossover, float& lambda, int& generations);

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
		std::cout << "Input algorithm to use as a number\n1: Differential Evolution\n2: Particle Swarm\n";
		std::cin >> algo_num;
	} else {
		algo_num = stoi(argv[2]);
	}
	// get strategy number for DE
	int strategy;
	if (algo_num == 1) {
		if (argc < 4) {
			std::cout << "Input Strategy for Differential Evolution (1-10)\n";
			std::cin >> strategy;
		} else {
			strategy = stoi(argv[3]);
		}
	}
	
	// create input and output file location strings
	std::string file_input(argv[1]);
	std::string file_output = "output/" + file_input;
	file_input = "input/" + file_input;

	// Problem setup
	size_t pop_size = 0;
	size_t gen_pop_size;
	int prob_num = 0;
	float mutation = 0;
	float crossover = 0;
	float lambda = 0;
	int generations = 0;

	std::unique_ptr<std::vector<uniform_real_distribution<float>>> distributions = processInputFile(file_input, pop_size, gen_pop_size, prob_num, mutation, crossover, lambda, generations);
	FitnessFunctionPtr fitness = problemFunction(prob_num);

	// run selected algorithm
	Population results(0,0);
	switch (algo_num) {
		case 1:
			results = DifferentialEvolution(std::move(distributions), fitness, pop_size, gen_pop_size, crossover, mutation, lambda, generations, strategy);
			break;
		case 2:
			// TODO: PS
			break;
		default:
			std::cout << "Invalid algorithm number\n";
			break;
	}
	// output results each line is fitness[i],vector[i][0],...,vector[i][j-1]
	logResults(results, file_output);

	return 0;
}


std::unique_ptr<std::vector<uniform_real_distribution<float>>> processInputFile(std::string& file_name, size_t& pop_size, size_t& gen_pop_size, int& prob_num, float& mutation, float& crossover, float& lambda, int& generations) {
	std::ifstream input_file(file_name);

	// if file fails to open print error message and exit early.
	if (!input_file.is_open()) {
		std::cout << "Failed to open input file.\n";
		exit(EXIT_FAILURE);
	}

	std::string token;

	// read problem number from input file
	std::getline(input_file, token, ',');
	prob_num = std::stoi(token);

	// read population size from input file
	std::getline(input_file, token, ',');
	pop_size = std::stoi(token);

	// read generation population size from input file
	std::getline(input_file, token, ',');
	gen_pop_size = std::stoi(token);

	// read mutation constant from input file
	std::getline(input_file, token, ',');
	mutation = std::stof(token);
	
	// read crossover constant from input file
	std::getline(input_file, token, ',');
	crossover = std::stof(token);

	// read lambda constant from input file
	std::getline(input_file, token, ',');
	lambda = std::stoi(token);

	//read generations constant from input file
	std::getline(input_file, token, ',');
	generations = std::stoi(token);

	// read dimension count from input file
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

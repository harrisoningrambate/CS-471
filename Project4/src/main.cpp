#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

#include "FShop.h"
#include "MakespanFunctions.h"
#include "NEH.h"
#include "ACO.h"

using namespace std;


/**
* Processes an input file into an fshop assigneing the makespan function based off of arguments
*
* @param[in] filename for the input file to read from 
* @param[in] makespan_fp either blocking or non-blocking function pointer
* @param[in] input_file_type either 1 for Taillard_Test file or 2 for output/neh file
* @param[out] A flow shop that holds the read in flow shop from file with its makespan calculated based on the given makespan function
*/
FShop processInputFShop(std::string& filename,
						unsigned int (*makespan_fp)(std::vector<std::vector<unsigned int>>&, std::vector<std::size_t>&),
						int input_file_type);

void writeOutputData(std::string& filename, FShop fs, const std::chrono::duration<float> exec_time);

int main(int argc, char* argv[]) {
	// ensure an input and output dir have been passed as arguments
	if (argc < 3) {
		std::cout << "invalid number of arguments\n";
		return 1;
	}

	// get algorithm to run
	int algo_num;
	if (argc < 4) {
		std::cout << "Input algorithm to use as a number\n1: NEH\n2: ACO\n";
		std::cin >> algo_num;
	} else {
		algo_num = stoi(argv[3]);
	}
	if (algo_num != 1 && algo_num != 2) {
		std::cout << "invalid algorithm selection\n";
		return 2;
	}
	
	// get makespan
	int makespan_func;
	if (argc < 5) {
		std::cout << "Select the method to calculate makespan\n1: Non-Blocking\n2:Blocking\n";
		std::cin >> makespan_func;
	} else {
		makespan_func = stoi(argv[4]);
	}
	unsigned int (*makespan_fp)(std::vector<std::vector<unsigned int>>&, std::vector<std::size_t>&);
	if (makespan_func == 1) makespan_fp = makespan_functions::nonBlocking;
	else if (makespan_func == 2) makespan_fp = makespan_functions::blocking;
	else {
		std::cout << "invalid makespan selection\n";
		return 3;
	}
	
	// processInput
	string input_file = argv[1];
	string output_file = argv[2];

	// run algorithm based on algorithm selected
	if (algo_num == 1) {
		FShop fs = processInputFShop(input_file, makespan_fp, 1);
		auto start = std::chrono::steady_clock::now();
		FShop neh_fs = NEH(fs);
		auto end = std::chrono::steady_clock::now();
		const std::chrono::duration<float> exec_time = end - start;
		std::cout << "Makespan after NEH heuristic: " << neh_fs.makespan << std::endl;
		writeOutputData(output_file, neh_fs, exec_time);
	} else if (algo_num == 2) {
		FShop fs = processInputFShop(input_file, makespan_fp, algo_num);
		auto start = std::chrono::steady_clock::now();
		FShop aco_fs = ACO(fs, 100, 100, 1.0f, 2.0f, 0.5f, 1);
		auto end = std::chrono::steady_clock::now();
		const std::chrono::duration<float> exec_time = end - start;
		writeOutputData(output_file, aco_fs, exec_time);
	}

}

FShop processInputFShop(std::string& filename, unsigned int (*makespan_fn)(std::vector<std::vector<unsigned int>>&, std::vector<std::size_t>&), int input_file_type) {
	std::ifstream input_file(filename);

	// file fails to open error message
	if (!input_file.is_open()) {
		std::cout << "Failed to open " << filename << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string token;
	
	// read machine count
	std::getline(input_file, token, ' ');
	std::size_t machine_count = std::stoi(token);
	
	// read job count
	std::size_t job_count;
	if (input_file_type == 1) {
		std::getline(input_file, token);
		job_count = std::stoi(token);
	} else {
		std::getline(input_file, token, ' ');
		job_count = std::stoi(token);
		std::getline(input_file, token, ' ');
		std::getline(input_file, token);
	}

	// allocate flow shop and fill values
	FShop fs(job_count, machine_count, makespan_fn);
	for (int m = 0; m < machine_count; m++) {
		for (int j = 0; j < job_count - 1; j++) {
			std::getline(input_file, token, ' ');
			fs.f_shop[j][m] = stoi(token);
		}
		std::getline(input_file, token);
		fs.f_shop[job_count - 1][m] = stoi(token);
	}
	fs.updateMakespan();
	
	return std::move(fs);
}

void writeOutputData(std::string& filename,
					 FShop fs,
					 const std::chrono::duration<float> exec_time) {
	std::ofstream out_file(filename);

	if (out_file.is_open()) {
		out_file << fs.f_shop[0].size() << ' ';
		out_file << fs.f_shop.size() << ' ';
		out_file << fs.makespan << ' ';
		out_file << std::fixed << std::setprecision(2) << exec_time.count() << '\n';
		for (int m = 0; m < fs.f_shop[0].size(); m++) {
			for (int j = 0; j < fs.f_shop.size() - 1; j++) {
				out_file << fs.f_shop[j][m] << ' ';
			}
			out_file << fs.f_shop[fs.f_shop[0].size() - 1][m] << '\n';
		}
		out_file.close();
	} else 
		std::cout << "Failed to open the output file\n";
}

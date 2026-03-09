#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "FShop.h"
#include "MakespanFunctions.h"
#include "NEH.h"

using namespace std;


FShop processInputFShop(std::string& filename);

int main() {
	string input_file = "1.txt";
	FShop test_fs2 = processInputFShop(input_file);
	cout << "Makespan before neh heuristic: " << test_fs2.makespan << std::endl;
	FShop neh_fs = NEH(test_fs2);
	std::cout << "Makespan after NEH heuristic: " << neh_fs.makespan << std::endl;
}

FShop processInputFShop(std::string& filename) {
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
	std::getline(input_file, token);
	std::size_t job_count = std::stoi(token);

	// allocate flow shop and fill values
	FShop fs(job_count, machine_count, makespan_functions::blocking);
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

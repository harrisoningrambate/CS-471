// Name: Harrison Ingram-Bate
#include "NEH.h"

#include <queue>
#include <utility>
#include <functional>
#include <limits>

// NOTE: debug libraries
#include <iostream>

FShop NEH(FShop& fs) {	
	std::size_t total_jobs = fs.f_shop.size();
	std::size_t machines = fs.f_shop[0].size();
	
	// seqeunce of indexes
	std::vector<std::size_t> sequence;

	// max heap storing the (total processing time, index) pair of jobs
	// NOTE: when total processing time is equal greater index is put first
	std::priority_queue<
		std::pair<unsigned int, std::size_t>,
		std::vector<std::pair<unsigned int, std::size_t>>,
		std::less<std::pair<unsigned int, std::size_t>>
	> max_heap;
	for (std::size_t j = 0; j < total_jobs; j++) {
		unsigned int tpt = 0;
		for (int m = 0; m < machines; m++)
			tpt += fs.f_shop[j][m];
		max_heap.push({tpt, j});
	}


	// for all elements in the heap determine their best index
	sequence.push_back(max_heap.top().second); // initialized with one value in the sequence
	max_heap.pop();
	int i;
	while (!max_heap.empty()) {
		std::size_t best_index = 0;
		unsigned int best_make = std::numeric_limits<unsigned int>::max();
		std::size_t current_index = max_heap.top().second;
		max_heap.pop();
		for (i = 0; i < sequence.size() + 1; i++) {
			// test sequence
			sequence.insert(sequence.begin() + i, current_index);
			unsigned int current_make = fs.calcMakespan(fs.f_shop, sequence);
			if (current_make < best_index) {
				best_index = current_index;
				best_make = current_make;
			}
			sequence.erase(sequence.begin() + i);
		}
		sequence.insert(sequence.begin() + best_index, current_index);
	}

	// initialize new FShop with neh heuristic job order
	FShop neh_fs(total_jobs, machines, fs.calcMakespan);
	for (int i = 0; i < total_jobs; i++) {
		neh_fs.f_shop[i] = std::move(fs.f_shop[sequence[i]]);
	}
	neh_fs.updateMakespan();
	 
	return neh_fs;
}

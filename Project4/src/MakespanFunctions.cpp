// Name: Harrison Ingram-Bate
#include "MakespanFunctions.h"

namespace makespan_functions {

	unsigned int nonBlocking(std::vector<std::vector<unsigned int>>& fs) {
		std::size_t machines = fs.size();
		std::size_t jobs = fs[0].size();
		std::vector<std::vector<unsigned int>> result_fs(machines, std::vector<unsigned int>(jobs));
	
		for (std::size_t i = 0; i < machines; i++) {
			for (std::size_t j = 0; j < jobs; j++) {
				// top row or left most column's
				if (i == 0 && j == 0) {
					result_fs[i][j] = fs[i][j];
					continue;
				} else if(i == 0) {
					result_fs[i][j] = result_fs[i][j - 1] + fs[i][j];
					continue;
				} else if (j == 0) {
					result_fs[i][j] = result_fs[i - 1][j] + fs[i][j];
					continue;
				}
	
				result_fs[i][j] = std::max(result_fs[i-1][j], result_fs[i][j - 1]) + fs[i][j];
			}
		}
		
		return result_fs[machines - 1][jobs - 1];
	}

	unsigned int blocking(std::vector<std::vector<unsigned int>>& fs) {
		std::size_t machines = fs.size();
		std::size_t jobs = fs[0].size();
		std::vector<std::vector<unsigned int>> result_fs(machines, std::vector<unsigned int>(jobs));

		for (std::size_t j = 0; j < jobs; j++) {
			for (std::size_t i = 0; i < machines; i++) {
				if (i == 0 && j == 0) result_fs[i][j] = fs[i][j];
				else if (j == 0 || i == machines - 1) result_fs[i][j] = result_fs[i - 1][j] + fs[i][j];
				else if (i == 0) result_fs[i][j] = std::max(result_fs[i][j - 1] + fs[i][j], result_fs[i + 1][j - 1]);
				else result_fs[i][j] = std::max(result_fs[i - 1][j] + fs[i][j], result_fs[i + 1][j - 1]);
			}
		}

		return result_fs[machines - 1][jobs - 1];
	}
}

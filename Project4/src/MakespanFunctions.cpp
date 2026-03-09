// Name: Harrison Ingram-Bate
#include "MakespanFunctions.h"

namespace makespan_functions {

	unsigned int nonBlocking(std::vector<std::vector<unsigned int>>& fs) {
		std::size_t jobs = fs.size();
		std::size_t machines = fs[0].size();
		std::vector<std::vector<unsigned int>> result_fs(jobs, std::vector<unsigned int>(machines));

		for (std::size_t j = 0; j < jobs; j++) {
			for (std::size_t m = 0; m < machines; m++) {
				if (j == 0 && m == 0) result_fs[j][m] = fs[j][m];
				else if (j == 0) result_fs[j][m] = result_fs[j][m - 1] + fs[j][m];
				else if (m == 0) result_fs[j][m] = result_fs[j - 1][m] + fs[j][m];
				else result_fs[j][m] = std::max(result_fs[j - 1][m], result_fs[j][m - 1]) + fs[j][m];
			}
		}

		return result_fs[jobs - 1][machines - 1];
	}

	unsigned int blocking(std::vector<std::vector<unsigned int>>& fs) {
		std::size_t jobs = fs.size();
		std::size_t machines = fs[0].size();
		std::vector<std::vector<unsigned int>> result_fs(jobs, std::vector<unsigned int>(machines));

		for (std::size_t j = 0; j < jobs; j++) {
			for (std::size_t m = 0; m < machines; m++) {
				if (m == 0 && j == 0) result_fs[j][m] = fs[j][m];
				else if (j == 0 || m == machines - 1) result_fs[j][m] = result_fs[j][m - 1] + fs[j][m];
				else if (m == 0) result_fs[j][m] = std::max(result_fs[j - 1][m] + fs[j][m], result_fs[j - 1][m + 1]);
				else result_fs[j][m] = std::max(result_fs[j][m - 1] + fs[j][m], result_fs[j - 1][m + 1]);
			}
		}

		return result_fs[jobs - 1][machines - 1];
	}
}

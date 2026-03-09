// Name: Harrison Ingram-Bate
#include "MakespanFunctions.h"

namespace makespan_functions {

	/**
	* computes a makespan for fssp without blocking.
	*
	* @param[in] fs a 2d vector representing a flow shop first index is for jobs, second index is for machines
	* @param[in] fsi a 1d vector representing a permutation of indexes for fssp allowing makespan calculations for 2-n jobs
	* @param[out] the calculated makespan for fssp with blocking
	*/
	unsigned int nonBlocking(std::vector<std::vector<unsigned int>>& fs, std::vector<std::size_t>& ji) {
		std::size_t jobs = ji.size();
		std::size_t machines = fs[0].size();
		std::vector<std::vector<unsigned int>> result_fs(jobs, std::vector<unsigned int>(machines));

		for (std::size_t j = 0; j < jobs; j++) {
			for (std::size_t m = 0; m < machines; m++) {
				if (j == 0 && m == 0) result_fs[j][m] = fs[ji[j]][m];
				else if (j == 0) result_fs[j][m] = result_fs[j][m - 1] + fs[ji[j]][m];
				else if (m == 0) result_fs[j][m] = result_fs[j - 1][m] + fs[ji[j]][m];
				else result_fs[j][m] = std::max(result_fs[j - 1][m], result_fs[j][m - 1]) + fs[ji[j]][m];
			}
		}

		return result_fs[jobs - 1][machines - 1];
	}

	/**
	* computes a makespan for fssp with blocking.
	*
	* @param[in] fs a 2d vector representing a flow shop first index is for jobs, second index is for machines
	* @param[in] fsi a 1d vector representing a permutation of indexes for fssp allowing makespan calculations for 2-n jobs
	* @param[out] the calculated makespan for fssp with blocking
	*/
	unsigned int blocking(std::vector<std::vector<unsigned int>>& fs, std::vector<std::size_t>& ji) {
		std::size_t jobs = ji.size();
		std::size_t machines = fs[0].size();
		std::vector<std::vector<unsigned int>> result_fs(jobs, std::vector<unsigned int>(machines));

		for (std::size_t j = 0; j < jobs; j++) {
			for (std::size_t m = 0; m < machines; m++) {
				if (m == 0 && j == 0) result_fs[j][m] = fs[ji[j]][m];
				else if (j == 0 || m == machines - 1) result_fs[j][m] = result_fs[j][m - 1] + fs[ji[j]][m];
				else if (m == 0) result_fs[j][m] = std::max(result_fs[j - 1][m] + fs[ji[j]][m], result_fs[j - 1][m + 1]);
				else result_fs[j][m] = std::max(result_fs[j][m - 1] + fs[ji[j]][m], result_fs[j - 1][m + 1]);
			}
		}

		return result_fs[jobs - 1][machines - 1];
	}
}

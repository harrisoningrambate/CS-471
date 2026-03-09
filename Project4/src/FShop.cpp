#include "FShop.h"

FShop::FShop(std::size_t jobs,
			 std::size_t machines,
			 unsigned int (*makespanfn)(std::vector<std::vector<unsigned int>>&, std::vector<std::size_t>&))

: f_shop(jobs, std::vector<unsigned int>(machines)), job_index_order(jobs)
{
	this->calcMakespan = makespanfn;
	for (int i = 0; i < jobs; i++) this->job_index_order[i] = i;
	this->makespan = this->calcMakespan(this->f_shop, this->job_index_order);
};

void FShop::updateMakespan() {
	this->makespan = this->calcMakespan(this->f_shop, this->job_index_order);
}

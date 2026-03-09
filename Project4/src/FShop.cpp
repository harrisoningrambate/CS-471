#include "FShop.h"

FShop::FShop(std::size_t jobs,
	   std::size_t machines,
	   unsigned int (*makespanfn)(std::vector<std::vector<unsigned int>>&))
: f_shop(jobs, std::vector<unsigned int>(machines))
{
	this->calcMakespan = makespanfn;
	this->makespan = this->calcMakespan(this->f_shop);
};

void FShop::updateMakespan() {
	this->makespan = this->calcMakespan(this->f_shop);
}

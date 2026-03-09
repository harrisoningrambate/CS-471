#include "FShop.h"

FShop::FShop(std::size_t machines,
	   std::size_t jobs,
	   unsigned int (*makespanfn)(std::vector<std::vector<unsigned int>>&))
: f_shop(machines, std::vector<unsigned int>(jobs))
{
	this->calcMakespan = makespanfn;
	this->makespan = this->calcMakespan(this->f_shop);
};

void FShop::updateMakespan() {
	this->makespan = this->calcMakespan(this->f_shop);
}

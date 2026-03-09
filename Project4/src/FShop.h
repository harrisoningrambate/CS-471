// Nme: Harrison Ingram-Bate
#ifndef F_SHOP
#define F_SHOP

#include <vector>

class FShop {
public:
	/**
	* Constructor of 
	*/
	FShop(std::size_t jobs,
	   std::size_t machines,
	   unsigned int (*makespanfn)(std::vector<std::vector<unsigned int>>&, std::vector<std::size_t>&));
	void updateMakespan();

	std::vector<std::vector<unsigned int>> f_shop;
	std::vector<std::size_t> job_index_order;
	unsigned int makespan;
	unsigned int (*calcMakespan)(std::vector<std::vector<unsigned int>>& fs, std::vector<std::size_t>& ji);
};

#endif

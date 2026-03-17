// Name: Harrison Ingram-Bate
#ifndef F_SHOP
#define F_SHOP

#include <vector>

class FShop {
public:
	/**
	* Constructor of FShop
	*
	* @param[in] jobs the number of jobs in a flow shop
	* @param[in] machines the number of machines in a flow shop
	* @param[in] makespan a function to calculate the makespan of a flow shop
	* @param[out] a flow shop initialized with every value as [job][machine] as 0
	*/
	FShop(std::size_t jobs,
	   std::size_t machines,
	   unsigned int (*makespanfn)(std::vector<std::vector<unsigned int>>&, std::vector<std::size_t>&));
	/**
	* Updates the makespan of a FShop using its makespan function
	*/
	void updateMakespan();

	std::vector<std::vector<unsigned int>> f_shop;
	std::vector<std::size_t> job_index_order;
	unsigned int makespan;
	unsigned int (*calcMakespan)(std::vector<std::vector<unsigned int>>& fs, std::vector<std::size_t>& ji);
};

#endif

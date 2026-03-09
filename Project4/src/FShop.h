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
	   unsigned int (*makespanfn)(std::vector<std::vector<unsigned int>>&));
	void updateMakespan();

	std::vector<std::vector<unsigned int>> f_shop;
	unsigned int makespan;
	unsigned int (*calcMakespan)(std::vector<std::vector<unsigned int>>& fs);
};

#endif

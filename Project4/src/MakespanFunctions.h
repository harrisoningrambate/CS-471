#ifndef MAKESPAN_FUNCTIONS
#define MAKESPAN_FUNCTIONS

#include <vector>

namespace makespan_functions{

	unsigned int nonBlocking(std::vector<std::vector<unsigned int>>& fs, std::vector<std::size_t>& ji);

	unsigned int blocking(std::vector<std::vector<unsigned int>>& fs, std::vector<std::size_t>& ji);
}

#endif

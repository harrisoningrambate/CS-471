#ifndef MAKESPAN_FUNCTIONS
#define MAKESPAN_FUNCTIONS

#include <vector>

namespace makespan_functions{

	unsigned int nonBlocking(std::vector<std::vector<unsigned int>>& fs);

	unsigned int blocking(std::vector<std::vector<unsigned int>>& fs);
}

#endif

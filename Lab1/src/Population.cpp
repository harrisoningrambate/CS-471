#include "Population.h"

Population::Population(size_t pop_size, size_t dimensions): population(pop_size, vector<float>(dimensions)), fitness(pop_size) {};

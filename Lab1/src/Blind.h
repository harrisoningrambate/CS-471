#ifndef BLIND
#define BLIND

#include <random>
#include <memory>
#include <chrono>
#include "Population.h"

Population Blind(std::unique_ptr<vector<uniform_real_distribution<float>>>  distribution_vec,
				 float (*fitness)(const vector<float>&),
				 size_t pop_size);

#endif

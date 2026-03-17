// Name: Harrison Ingram-Bate
#ifndef ACO_H
#define ACO_H

#include "FShop.h"

/**
* Runs ant colony optimization for a FShop
*
* @param[in] fs a FShop holding a 2d vector of jobs and machines and a makespan function
* @param[in] num_ants the number of ants per iteration of ACO
* @param[in] iterations the number of iterations to run before returning the global best
* @param[in] alpha a float constant used to increase/decrease the importance of ant pheromones
* @param[in] beta a float constant used to increase/decrease the importance of heuristic vision
* @param[in] evaporation the rate at which ant pheromones evaporate
* @param[in] q a value used to scale the pheromones each ant deposits when making a decisision
* @param[out] the global best solution found as an FShop
*/
FShop ACO(FShop& fs,
		  std::size_t num_ants,
		  int iterations,
		  float alpha,
		  float beta,
		  float evaporation,
		  float q);

#endif

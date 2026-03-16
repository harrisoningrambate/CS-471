// Name: Harrison Ingram-Bate
#ifndef ACO_H
#define ACO_H

#include "FShop.h"

FShop ACO(FShop& fs,
		  std::size_t num_ants,
		  int iterations,
		  float alpha,
		  float beta,
		  float evaporation,
		  float q);

#endif

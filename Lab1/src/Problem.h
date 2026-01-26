#ifndef PROBLEM
#define PROBLEM
#include <vector>
using namespace std;

/**
* Calculates the fitness of a vector evaluated with Schwefel's function.
* @param[in] vec
* @param[out] fitness
*/
float Schwefel(const vector<float>& vec);

/**
* Calculates the fitness of a vector evaluated with 1st De Jong's function.
* @param[in] vec
* @param[out] fitness
*/
float FirstDeJong(const vector<float>& vec);

/**
* Calculates the fitness of a vector evaluated with Rosenbrock's Sadle.
* @param[in] vec
* @param[out] fitness
*/
float Rosenbrock(const vector<float>& vec);

/**
* Calculates the fitness of a vector evaluated with Rastrigin.
* @param[in] vec
* @param[out] fitness
*/
float Rastrigin(const vector<float>& vec);

/**
* Calculates the fitness of a vector evaluated with Griewangk.
* @param[in] vec
* @param[out] fitness
*/
float Griewangk(const vector<float>& vec);

/**
* Calculates the fitness of a vector evaluated with Sine Envelope Sine Wave.
* @param[in] vec
* @param[out] fitness
*/
float SineEnvelope(const vector<float>& vec);

/**
* Calculates the fitness of a vector evaluated with Stretched V Sine Wave.
* @param[in] vec
* @param[out] fitness
*/
float StretchedV(const vector<float>& vec);

/**
* Calculates the fitness of a vector evaluated with Ackley's One.
* @param[in] vec
* @param[out] fitness
*/
float AckleyOne(const vector<float>& vec);

/**
* Calculates the fitness of a vector evaluated with Ackley's Two
* @param[in] vec
* @param[out] fitness
*/
float AckleyTwo(const vector<float>& vec);

/**
* Calculates the fitness of a vector evaluated with Egg Holder.
* @param[in] vec
* @param[out] fitness
*/
float EggHolder(const vector<float>& vec);
#endif

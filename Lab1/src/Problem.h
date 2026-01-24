#ifndef PROBLEM
#define PROBLEM
#include <vector>
using namespace std;

float Schwefel(const vector<float>& vec);

float FirstDeJong(const vector<float>& vec);

float Rosenbrock(const vector<float>& vec);

float Rastrigin(const vector<float>& vec);

float Griewangk(const vector<float>& vec);

float SineEnvelope(const vector<float>& vec);

float StretchedV(const vector<float>& vec);

float AckleyOne(const vector<float>& vec);

float AckleyTwo(const vector<float>& vec);

float EggHolder(const vector<float>& vec);
#endif

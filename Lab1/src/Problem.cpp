#include <math.h>
#include "Problem.h"

float Schwefel(vector<float> vec) {
	int n = vec.size();
	float result = 418.9829f * n;
	float summation = 0;
	for (int i = 0; i < n; i++) {
		summation = -1 * vec[i] * sin(sqrt(abs(vec[i])));
	}
	result -= summation;
	return result;
}

float FirstDeJong(vector<float> vec) {
	int n = vec.size();
	float result = 0.0f;

	for (int i = 0; i < n; i++) {
		result += vec[i] * vec[i];
	}
	return result;
}

// TODO: implement Rosenbrock

// TODO: implement Rastrigin

// TODO: implement Griegwangk

// TODO: implement Sine Envelope Sine Wave

// TODO: implement Stretched V Sine Wave

// TODO: implement Ackley's One

// TODO: implement Ackley's Two

// TODO: implement Egg Holder

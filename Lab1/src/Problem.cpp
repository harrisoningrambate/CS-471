#include <math.h>
#include "Problem.h"

float Schwefel(const vector<float>& vec) {
	int n = vec.size();
	float result = 418.9829f * n;
	float summation = 0;
	for (int i = 0; i < n; i++) {
		summation += -1 * vec[i] * sin(sqrt(abs(vec[i])));
	}
	result -= summation;
	return result;
}

float FirstDeJong(const vector<float>& vec) {
	int n = vec.size();
	float result = 0.0f;

	for (int i = 0; i < n; i++) {
		result += vec[i] * vec[i];
	}
	return result;
}

float Rosenbrock(const vector<float>& vec) {
	int n = vec.size();
	float result = 0.0f;

	float temp; // used to hold summation calculation
	for (int i = 0; i < n - 1; i++) {
		temp = 0.0f; // reset temp;

		// calculation current instance of the summation
		temp = vec[i] * vec[i] - vec[i+1];
		temp *= temp;
		temp += (1 - vec[i]) * (1 - vec[i]);
		temp *= 100;
		
		result += temp;
	}

	return result;
}

// TODO: implement Rastrigin

// TODO: implement Griegwangk

// TODO: implement Sine Envelope Sine Wave

// TODO: implement Stretched V Sine Wave

// TODO: implement Ackley's One

// TODO: implement Ackley's Two

// TODO: implement Egg Holder

#include <math.h>
#include "Problem.h"

// cast math.h implementation of pi from double to float to use in functions
#define PI ((float)M_PI)

float Schwefel(const vector<float>& vec) {
	int n = vec.size();
	float result = 418.9829f * n;
	float summation = 0.0f;
	for (int i = 0; i < n; i++) {
		summation += -1.0f * vec[i] * sin(sqrt(abs(vec[i])));
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
		// calculation current instance of the summation
		temp = vec[i] * vec[i] - vec[i+1];
		temp *= temp;
		temp += (1.0f - vec[i]) * (1.0f - vec[i]);
		temp *= 100.0f;
		
		result += temp;
	}

	return result;
}

float Rastrigin(const vector<float>& vec) {
	int n = vec.size();
	float result = 10.0f * n;
	float summation = 0.0f;
	
	float temp;
	for (int i = 0; i < n; i++) {
		// calculation current instance of the summation
		temp = vec[i] * vec[i];
		temp -= (10.0f * cos(2 * PI *vec[i]));

		summation += temp;
	}
	// NOTE: this might change to a +=
	result *= summation;

	return result;
}

// TODO: implement Griegwangk
float Griewangk(const vector<float>& vec){
	int n = vec.size();
	float result = 1.0f;
	float summation = 0.0f;
	float product = 1.0f;

	for (int i = 0; i < n; i++) {
		// calculation current instance of the summation and product
		summation += (vec[i] * vec[i]) / 4000.0f;
		product *= cos(vec[i] / sqrt(i + 1));
	}

	// finalize result
	result += summation;
	result -= product;

	return result;
}

// TODO: implement Sine Envelope Sine Wave

// TODO: implement Stretched V Sine Wave

// TODO: implement Ackley's One

// TODO: implement Ackley's Two

// TODO: implement Egg Holder

#define _USE_MATH_DEFINES
#include <math.h>
#include "Problem.h"

// cast math.h implementation of pi and e from double to float to use in functions
#define PI ((float)M_PI)
#define E ((float)M_E)

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

	float temp;
	for (int i = 0; i < n - 1; i++) {
		temp = vec[i] * vec[i] - vec[i+1];
		temp *= temp;
		temp *= 100.0f;
		temp += (1.0f - vec[i]) * (1.0f - vec[i]);
		
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
		temp = vec[i] * vec[i];
		temp -= (10.0f * cos(2 * PI *vec[i]));

		summation += temp;
	}
	result *= summation;

	return result;
}

float Griewangk(const vector<float>& vec){
	int n = vec.size();
	float result = 1.0f;
	float summation = 0.0f;
	float product = 1.0f;

	for (int i = 0; i < n; i++) {
		summation += (vec[i] * vec[i]) / 4000.0f;
		product *= cos(vec[i] / sqrt(i + 1));
	}

	result += summation;
	result -= product;

	return result;
}

float SineEnvelope(const vector<float>& vec){
	int n = vec.size();
	float result = 0.0f;
	float summation = 0.0f;

	float numerator;
	float denominator;
	float sum_of_squares; // reused calculation
	for (int i = 0; i < n -1; i++) {
		sum_of_squares = vec[i] * vec[i] + vec[i + 1] * vec[i + 1];

		numerator = sum_of_squares - 0.5f;
		numerator *= numerator;
		numerator = sin(numerator);

		denominator = 1.0f + 0.001f * (sum_of_squares);
		denominator *= denominator;

		summation += 0.5f * (numerator / denominator);
	}
	result -= summation;

	return result;
}

float StretchedV(const vector<float>& vec) {
	int n = vec.size();
	float result = 0.0f;
	
	float temp;
	float sum_of_squares; // reused calculation
	for (int i = 0; i < n - 1; i++) {
		sum_of_squares = vec[i] * vec[i] + vec[i + 1] * vec[i + 1];

		temp = sin(50 * pow(sum_of_squares, 0.1f));
		temp *= temp;
		temp *= pow(sum_of_squares, 0.25f);

		result += temp + 1.0f;
	}

	return result;
}

float AckleyOne(const vector<float>& vec) {
	int n = vec.size();
	float result = 0.0f;
	float constant = 1 / pow(E, 0.2f); // reused calculation
	
	float temp;
	for (int i = 0; i < n - 1; i++) {
		temp = vec[i] * vec[i] + vec[i + 1] * vec[i + 1];
		temp = constant * sqrt(temp);
		temp += 3 * (cos(2 * vec[i]) + sin(2 * vec[i + 1]));

		result += temp;
	}

	return result;
}

float AckleyTwo(const vector<float>& vec) {
	int n = vec.size();
	float result  = 0.0f;
	
	float temp1, temp2;
	for (int i = 0; i < n -1; i++) {
		temp1 = vec[i] * vec[i] + vec[i + 1] * vec[i + 1];
		temp1 /= 2.0f;
		temp1 = 20.0f / pow(E, 0.2f * sqrt(temp1));

		temp2 = cos(2 * PI * vec[i]) + cos(2 * PI * vec[i + 1]);
		temp2 = pow(E, 0.5f * temp2);

		result += 20.0f + E - temp1 - temp2;
	}

	return result;
}

float EggHolder(const vector<float>& vec) {
	int n = vec.size();
	float result = 0.0f;

	float temp;
	for (int i = 0; i < n - 1; i++) {
		temp = sqrt(abs(vec[i] - vec[i + 1] - 47.0f));
		result -= vec[i] * sin(temp);

		temp = sqrt(abs(vec[i + 1] + 47.0f + vec[i] / 2.0f));
		result -= (vec[i + 1] + 47.0f) * sin(temp);
	}

	return result;
}

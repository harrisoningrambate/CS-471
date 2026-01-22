#include <math.h>
#include "Problem.h"

float Schwefel(vector<float> vec) {
	int n = vec.size();
	float result = 418.9829f * n;
	for (int i = 0; i < n; i++) {
		// TODO: implement summation portion of Schwefel's funciton
		result -= vec[i];
	}
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

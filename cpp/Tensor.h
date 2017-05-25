#ifndef __TENSOR_H__
#define __TENSOR_H__

#include "Matrix.h"
#include <vector>
#include <iostream>

using namespace std;

class Tensor {
public:
	Tensor(vector<Matrix>);
	Tensor(vector<vector<vector<int>>>);
	Tensor(unsigned int x, unsigned int y, unsigned int z);
	void set(int, Matrix);
	Matrix operator[](unsigned int);
private:
	vector<Matrix> tensor_;
	unsigned int x_;
	unsigned int y_;
	unsigned int z_;
};

#endif
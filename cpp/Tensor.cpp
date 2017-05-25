#include "Tensor.h"

Tensor::Tensor(vector<Matrix>) {

}
Tensor::Tensor(vector<vector<vector<int>>>) {

}
Tensor::Tensor(unsigned int x, unsigned int y, unsigned int z) {
	assert(x > 0 && y > 0 && z > 0);

	x_ = x;
	y_ = y;
	z_ = z;

	Matrix m(x,y);
	for (unsigned int w = 0; w < z_; w++) {
		tensor_.push_back(m);
	}
}

Matrix Tensor::operator[](unsigned int n) {
	assert(n > 0 && n < z_);
	return tensor_[n];
}

void Tensor::set(int n, Matrix m) {
	assert(n > 0 && n < z_);
	tensor_[n] = m;
}

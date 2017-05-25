#include "Matrix.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

//template<typename T>
Matrix::Matrix(unsigned int rows, unsigned int cols) {
	assert(cols > 0 && rows > 0);
	rows_ = rows;
	cols_ = cols;
	vector<int> col(cols);
	for (unsigned int r = 0; r < rows; r++) {
		matrix_.push_back(col);
	}
}

//template<typename T>
Matrix::Matrix(vector<vector<int>> v) {
	rows_ = v.size();
	unsigned int largest = 0;
	for (unsigned int i = 0; i < v.size(); i++) {
		if (v[i].size() > largest)largest = v[i].size();
	}
	cols_ = largest;

	vector<int> col(cols_);
	for (unsigned int r = 0; r < rows_; r++) {
		matrix_.push_back(col);
	}

	for (unsigned int r = 0; r < v.size(); r++) {
		for (unsigned int c = 0; c < v[r].size(); c++) {
			if (v[r][c]) matrix_[r][c] = v[r][c]; 
			else matrix_[r][c] = 0;
		}
	}
}

//template<typename T>
vector<int> Matrix::operator[](unsigned int r)const {
	assert(r >= 0 && r < rows_);
	return matrix_[r];
}
//template<typename T>
void Matrix::set(unsigned int r, unsigned int c, int value) {
	assert(r >= 0 && r < rows_ && c >= 0 && c < cols_);
	matrix_[r][c] = value;
}
//template<typename T>
Matrix Matrix::Tp() {
	return Matrix(1, 1);
}

//template<typename T>
unsigned int Matrix::r()const {
	return rows_;
}

//template<typename T>
unsigned int Matrix::c()const {
	return cols_;
}
//template<typename T>
int Matrix::det()const{
	assert(rows_ == cols_);//must be square matrix :3
	int determinate = 0;
	if (rows_ != 1 && cols_ != 1) {
		for (unsigned int i = 0; i < rows_; i++) {
			
			vector<vector<int>> m;
			for (unsigned int row = 0; row < rows_; row++) {
				vector<int> r;
				for (unsigned int col = 0; col < cols_; col++) {
					if (row != i && col != 0) {
						r.push_back(matrix_[row][col]);
					}
				}
				if(r.size() != 0) m.push_back(r);
			}

			Matrix newMatrix(m);

			determinate += pow(-1, (i + 1) + 1) * matrix_[i][0] * newMatrix.det();
		}
		return determinate;
	}
	else {
		return matrix_[0][0];
	}
}

//template<typename T>
Matrix operator+(Matrix a, Matrix b) {
	assert(a.r() == b.r() && a.c() == b.c());
	Matrix ret(a.r(), a.c());
	for (unsigned int i = 0; i < a.r(); i++) {
		for (unsigned int j = 0; j < a.c(); j++) {
			ret.set(i, j, a[i][j] + b[i][j]);
		}
	}
	return ret;
}

//template<typename T>
Matrix operator-(Matrix a, Matrix b) {
	assert(a.r() == b.r() && a.c() == b.c());
	Matrix ret(a.r(), a.c());
	for (unsigned int i = 0; i < a.r(); i++) {
		for (unsigned int j = 0; j < a.c(); j++) {
			ret.set(i, j, a[i][j] - b[i][j]);
		}
	}
	return ret;
}

//template<typename T>
Matrix operator*(Matrix a, Matrix b) {
	assert(a.c() == b.r());
	Matrix newMatrix(a.r(), b.c());
	
	for (unsigned int i = 0; i < newMatrix.r(); i++) {
		for (unsigned int j = 0; j < newMatrix.c(); j++) {
			newMatrix.set(i, j, dot(a.getRow(i), b.getCol(j)));
		}
	}

	return newMatrix;
}

int dot(vector<int> a, vector<int> b) {
	int dP = 0;
	while (a.size() < b.size()) {
		a.push_back(0);
	}
	while (a.size() > b.size()) {
		b.push_back(0);
	}

	for (unsigned int i = 0; i < a.size(); i++) {
		dP += a[i] * b[i];
	}
	return dP;
}

vector<int> Matrix::getRow(unsigned int n)const {
	assert(n >= 0 && n < rows_);
	vector<int> v;
	for (unsigned int i = 0; i < cols_; i++) {
		v.push_back(matrix_[n][i]);
	}
	return v;
}

vector<int> Matrix::getCol(unsigned int n)const {
	assert(n >= 0 && n < cols_);
	vector<int> v;
	for (unsigned int i = 0; i < rows_; i++) {
		v.push_back(matrix_[i][n]);
	}
	return v;
}

Matrix operator*(double n, Matrix m) {
	for (unsigned int i = 0; i < m.r(); i++) {
		for (unsigned int j = 0; j < m.c(); j++) {
			m.set(i, j, m[i][j] * n);
		}
	}
	return m;
}

Matrix operator*(Matrix m, double n) {
	for (unsigned int i = 0; i < m.r(); i++) {
		for (unsigned int j = 0; j < m.c(); j++) {
			m.set(i, j, m[i][j] * n);
		}
	}
	return m;
}

//template<typename T>
ostream& operator<<(ostream & os, const Matrix &a) {
	for (unsigned int r = 0; r < a.r(); r++) {
		for (unsigned int c = 0; c < a.c(); c++) {
			os << a[r][c]<<"   ";
		}
		os << endl;
	}
	return os;
}
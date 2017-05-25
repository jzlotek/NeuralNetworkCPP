#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class Matrix {
public:
	Matrix(unsigned int, unsigned int);
	Matrix(vector<vector<int>>);
	vector<int> operator[](unsigned int)const;
	Matrix Tp();
	unsigned int r()const;
	unsigned int c()const;
	void set(unsigned int r, unsigned int c, int value);
	int det()const;
	vector<int> getRow(unsigned int)const;
	vector<int> getCol(unsigned int)const;
private:
	unsigned int rows_;
	unsigned int cols_;
	vector<vector<int>> matrix_;
};

int dot(vector<int>, vector<int>);
double dot(vector<double>, vector<double>);
double dot(vector<int>, vector<double>);
double dot(vector<double>, vector<int>);

Matrix operator+(Matrix, Matrix);

Matrix operator-(Matrix, Matrix);

Matrix operator*(Matrix, Matrix);

Matrix operator*(double, Matrix);
Matrix operator*(Matrix, double);

//template<typename T>
ostream & operator<<(ostream & os, const Matrix &a);

#endif

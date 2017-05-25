#include "Matrix.h"
#include "Tensor.h"
#include <iostream>

using namespace std;

int main() {
	
	Matrix m(1,1);
	m.set(0, 0, 1);
	vector<vector<int>> x = { {10,0,1},
							  {0,1,0},
							  {1,0,5} };

	vector<vector<int>> y = { { 10,0,1 },
							  { 0,1,0 },
							  { 1,0,5 } };
	Matrix test(x);
	Matrix test1(y);
	cout << m << endl;
	cout << test << endl;
	cout << test.det() << endl;
	cout << test - test1 << endl;
	cout << test*test1 << endl;
	cout << test * 2 << endl;
	cout << 2 * test << endl;
	return 0;
}
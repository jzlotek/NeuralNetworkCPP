#ifndef __NEURON_H__
#define __NEURON_H__

#include <vector>
#include "InputNode.h"

using namespace std;

class Neuron {
private:
	vector<InputNode*> inputs_;
	bool out_;
	double thresh_;
	double rand_;
	double value_;
public:
	Neuron();
	Neuron(double);
	void setInputs(vector<InputNode*>);
	void setThreshhold(double);
	bool getValue()const;
	double sigmoid(double);
	void normalize();
	void sum(vector<double>);
};
Neuron& operator*(Neuron&, double);
Neuron& operator*(double, Neuron&);

#endif
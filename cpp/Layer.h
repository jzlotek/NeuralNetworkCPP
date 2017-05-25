#ifndef __LAYER_H__
#define __LAYER_H__

#include <vector>
#include "Neuron.h"

using namespace std;
class Layer {
private:
	vector<Neuron*> neurons_;
	vector<double> weights;
public:
	Layer(vector<Neuron*>);
	void calcAllValues();
};
#endif
#ifndef __NEURON_H__
#define __NEURON_H__

#include "Node.h"
#include <vector>
#include "InputLayer.h"
using namespace std;

class Neuron : public Node{
public:
	Neuron();
	void setSynapses(InputLayer*);
	vector<double> getWeights()const;
private:
	InputLayer* synapses_;
	vector<double> weights_;
};

#endif
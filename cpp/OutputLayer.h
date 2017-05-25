#ifndef __OUTLAYER__
#define __OUTLAYER__

#include "InputLayer.h"
#include <string>
#include "Neuron.h"

using namespace std;

class OutputLayer : public InputLayer {
public:
	OutputLayer(string name = "");
	OutputLayer(vector<Neuron*>, string name = "", InputLayer* = NULL);
	void setSynapses(InputLayer*);
private:
	vector<Neuron*> neurons_;
};

#endif
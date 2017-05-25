#include "OutputLayer.h"
#include <string>

OutputLayer::OutputLayer(string name):InputLayer(name) {
	neurons_ = {};
}
OutputLayer::OutputLayer(vector<Neuron*> n, string name, InputLayer* l): InputLayer(name) {
	for (int i = 0; i < getNumNodes(); i++) {
		neurons_[i]->setSynapses(l);
	}
}
void OutputLayer::setSynapses(InputLayer* l) {
	for (int i = 0; i < getNumNodes(); i++) {
		neurons_[i]->setSynapses(l);
	}
}
#include "Neuron.h"

Neuron::Neuron():Node() {
	synapses_ = NULL;
}
void Neuron::setSynapses(InputLayer* l) {
	synapses_ = l;
	for (int i = 0; i < synapses_->getNumNodes(); i++) {
		weights_.push_back(1.0);
	}
}
vector<double> Neuron::getWeights()const {
	return weights_;
}

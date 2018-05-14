#include <vector>
#include <fstream>
#include "Layer.h"

Layer::Layer(unsigned int neurons, unsigned int lastLayerSize) {
  for (unsigned int i = 0; i < neurons; i++) {
    _neurons.push_back(Neuron(lastLayerSize));
    _bias.push_back((rand() * 5) % 10);
  }
}

std::vector<Neuron> &Layer::getNeurons() { return _neurons; }

void Layer::forwardPropigate(Layer &lastLayer) {
  for (unsigned int i = 0; i < _neurons.size(); i++) {
    // getNeurons()[i].sum(layer, _bias[i]);
    _neurons[i].sum(lastLayer, lastLayer.getBias()[i]);
  }
}
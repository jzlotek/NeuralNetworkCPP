#include <vector>
#include <fstream>
#include "Neuron.h"
#include "Layer.h"

class Layer;

Neuron::Neuron(unsigned int synapses) {
  for (unsigned int i = 0; i < synapses; i++) {
    _weights.push_back(1.5);
  }
}

double Neuron::getValue()const { return _value; }

std::vector<double> Neuron::getWeights()const { return _weights; }

void Neuron::setWeights(const std::vector<double> weights) {
    if(weights.size() == _weights.size()){
        _weights=weights;
    }
}

double Neuron::activate(bool deriv) {
  if (!deriv)
    return ((getValue() > 0) ? getValue() : 0); // ReLU function
  return 1;
  //   return tanh(_value);
  // return 1 - pow(tanh(_value), 2);
}

void Neuron::sum(Layer &layer, double bias) {
  std::vector<Neuron> &neurons = layer.getNeurons();
  double sumValue = 0;
  for (unsigned int i = 0; i < neurons.size(); i++) {
    sumValue += neurons[i].activate(false) * _weights[i];
  }
  _value = sumValue + bias;
}

void Neuron::setValue(double v) { _value = v; }
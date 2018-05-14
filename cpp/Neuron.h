#include <vector>

#ifndef _NEURON_H
#define _NEURON_H

class Neuron;
class Layer;

class Neuron {
private:
    std::vector<double> _weights;
    double _value = 0;
    double _delta;

public:
    Neuron(unsigned int synapses = 0);
    double activate(bool deriv = false);
    void sum(Layer &layer, double bias);
    double getValue() const;
    std::vector<double> getWeights()const;
    void setWeights(std::vector<double> weights);
    void setValue(double);
    void setDelta(double d) { _delta = d; };
    double getDelta() const { return _delta; };
};

#endif

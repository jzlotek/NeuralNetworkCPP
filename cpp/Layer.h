#include <vector>
 
#ifndef _LAYER_H_
#define _LAYER_H_

class Neuron;

class Layer {
public:
    Layer(unsigned int neurons = 1, unsigned int lastLayerSize = 0);
    std::vector<Neuron> &getNeurons();
    void forwardPropigate(Layer &lastLayer);
    std::vector<double> &getBias() { return _bias; };
    void activate(bool deriv = false);

private:
    std::vector<Neuron> _neurons;
    std::vector<double> _bias;
};

#endif //UNTITLED_LAYER_H

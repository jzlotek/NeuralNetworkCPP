#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "Neuron.cpp"
#include "Layer.cpp"

using namespace std;

template<typename T>
ostream &operator<<(ostream &out, vector<T> v) {
    out << "[";
    if (v.size() == 0)
        out << " ";
    for (unsigned int i = 0; i < v.size(); i++) {
        out << v[i];
        if (i != v.size() - 1)
            out << ", ";
    }
    out << "]";
    return out;
}

class Network;

class Network {
private:
    vector<Layer> _layers;
    int _epoch = 0;
    double _averageError = 0;

public:
    Network(vector<unsigned int> topology);

    void forwardPropigate();

    vector<Layer> &getLayers();

    void setInitialValues(vector<double>);

    double trainNetwork(vector<vector<double>> inputs,
                        vector<vector<double>> outputs, double gamma);

    void setNetworkDeltas(vector<double> expected);

    void updateWeights();
};

Network::Network(vector<unsigned int> topology) {
    assert(topology.size() >= 3);
    for (unsigned int i = 0; i < topology.size(); i++) {
        if (i == 0)
            _layers.push_back(Layer(topology[i]));
        else
            _layers.push_back(Layer(topology[i], topology[i - 1]));
    }
}

vector<Layer> &Network::getLayers() { return _layers; }

ostream &operator<<(ostream &out, Neuron n) {
    out << "Value: " << n.activate(false) << " Weights: ";
    vector<double> weights;

    for (unsigned int i = 0; i < n.getWeights().size(); i++) {
        weights.push_back(n.getWeights()[i]);
    }
    cout << weights;
    return out;
}

ostream &operator<<(ostream &os, Network n) {
    for (unsigned int i = 0; i < n.getLayers().size(); i++) {
        os << n.getLayers()[i].getNeurons() << endl;

        os << "Bias: " << n.getLayers()[i].getBias() << endl;
    }

    return os;
}

void Network::forwardPropigate() {
    for (unsigned int i = 1; i < _layers.size(); i++) {
        _layers[i].forwardPropigate(_layers[i - 1]);
    }
}

void Network::setInitialValues(vector<double> v) {
    assert(v.size() == _layers[0].getNeurons().size());
    for (unsigned int i = 0; i < v.size(); i++) {
        _layers[0].getNeurons()[i].setValue(v[i]);
    }
}

double calcError(vector<Neuron> &outputLayer, vector<double> output) {
    assert(outputLayer.size() == output.size());
    double error = 0;

    for (unsigned int i = 0; i < output.size(); i++) {
        error += pow(outputLayer[i].activate(false) - output[i], 2);
    }
    error /= (output.size() * 2.0);

    return error;
}

void Network::setNetworkDeltas(vector<double> expected) {
    vector<double> gradient;
    for (int i = _layers.size() - 1; i >= 0; i--) {
        if (i == _layers.size() - 1) {
            for (unsigned int n = 0; n < _layers[i].getNeurons().size(); n++) {
                gradient.push_back(expected[n] -
                                   _layers[i].getNeurons()[n].activate(false));
            }
        } else {
            for (unsigned int n = 0; n < _layers[i].getNeurons().size(); n++) {
                double error = 0;

                for (unsigned int j = 0; j < _layers[i + 1].getNeurons().size(); j++) {
                    error += (_layers[i + 1].getNeurons()[j].getWeights()[n] *
                              _layers[i + 1].getNeurons()[j].getDelta());
                }
                gradient.push_back(error);
            }
        }
        for (unsigned int n = 0; n < _layers[i].getNeurons().size(); n++) {
            Neuron &ref = _layers[i].getNeurons()[n];
            ref.setDelta(gradient[i] * ref.activate(true));
        }
    }
}

vector<double> getLayerValueVector(Layer l) {
    vector<double> values;
    for (unsigned int i = 0; i < l.getNeurons().size(); i++) {
        values.push_back(l.getNeurons()[i].activate(false));
    }
    return values;
}

void Network::updateWeights() {
    double gamma = -.5;
    vector<double> inputs;
    for (unsigned int i = 0; i < _layers.size() - 1; i++) {
        if (i != 0)
            inputs = getLayerValueVector(_layers[i - 1]);

        vector<Neuron> &neurons = _layers[i].getNeurons();
        vector<Neuron> &nextLayer = _layers[i + 1].getNeurons();
        vector<double> &bias = _layers[i + 1].getBias();
        for (unsigned int n = 0; n < nextLayer.size(); n++) {
            vector<double> weightsTemp = _layers[i + 1].getNeurons()[n].getWeights();
            for (unsigned int j = 0; j < neurons.size(); j++) {

                weightsTemp[j] = (weightsTemp[j] + (nextLayer[n].getDelta() * gamma * neurons[j].activate(false)));
                // weightsTemp[j] = (weightsTemp[j] + (neurons[j].getDelta() * gamma * nextLayer[n].activate(false)));

                // cout<<(nextLayer[n].getDelta() * gamma *
                // neurons[j].activate(false))<<endl;

            }
            cout << weightsTemp;
            nextLayer[n].setWeights(weightsTemp);
            weightsTemp.clear();
            bias[n] -= gamma * nextLayer[n].getDelta();
        }
    }
}

double Network::trainNetwork(vector<vector<double>> inputs,
                             vector<vector<double>> outputs, double gamma) {
    assert(inputs.size() == outputs.size());
    double error;
    double totalE = _averageError * _epoch;
    for (unsigned int i = 0; i < inputs.size(); i++) {
        // SET VALUES
        // cout << "Setting Values" << endl;
        setInitialValues(inputs[i]);
        // FORWARD PROP
        forwardPropigate();
        // cout<<"Forward propigation done. Last layer:"<<endl;
        // cout << _layers[_layers.size() - 1].getNeurons() << endl;
        // FIND ERROR LAST LAYER
        error = calcError(_layers[_layers.size() - 1].getNeurons(), outputs[i]);
        // cout<<"Error: "<<error<<endl;
        // BACK PROPIGATE
        setNetworkDeltas(outputs[i]);
        // cout<<"Deltas generated"<<endl;
        // Update weightsweights
        updateWeights();
        // cout<<"Weights Updated"<<endl;


        _epoch++;
        totalE += error;
        cout << "Error: " << _averageError << "\tEpoch: " << _epoch << endl;
    }
    _averageError = totalE / _epoch;
    return _averageError;
}

vector<unsigned int> getTopology(string fileLocation) {
    ifstream file;
    file.open(fileLocation);
    vector<unsigned int> top;
    unsigned int read;
    if (file.is_open()) {
        while (file >> read) {
            top.push_back(read);
        }
    }
    return top;
}

vector<vector<double>> createRandomInput(int i) {
    vector<vector<double>> parent;
    for (unsigned int n = 0; n < i; n++) {
        double rand1 = rand() % 2;
        double rand2 = rand() % 2;
        parent.push_back({(round(rand1)), (round(rand2))});
    }
    return parent;
}

vector<vector<double>> createOutput(vector<vector<double>> in) {
    vector<vector<double>> parent;
    for (unsigned int i = 0; i < in.size(); i++) {
        vector<double> v = in[i];
        parent.push_back({v[0] == v[1] ? 0.0 : 1.0});
    }
    return parent;
}

int main() {
    srand(time(NULL));
    Network network({2, 3, 1});
    vector<vector<double>> in = createRandomInput(500);
    vector<vector<double>> out = createOutput(in);
    cout << in << endl << out << endl;
    double error = 100;
    while (error > 1) {
        error = network.trainNetwork(in, out, 0);
    }

    // cout << endl << endl << network << endl;
    // network.trainNetwork(in, out, 0);
    // cout << endl << endl << network << endl;
    // network.trainNetwork(in, out, 0);
    // cout << endl << endl << network << endl;
    // network.trainNetwork(in, out, 0);
    // cout << endl << endl << network << endl;
    // network.trainNetwork(in, out, 0);
    // cout << endl << endl << network << endl;
    // network.trainNetwork(in, out, 0);

    cout << endl << endl << network << endl;
    return 0;
}

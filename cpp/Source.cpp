#include "Matrix.h"
#include "Tensor.h"
#include "InputNode.h"
#include "Neuron.h"
#include "InputLayer.h"
#include "OutputLayer.h"
#include "Node.h"
#include <iostream>

using namespace std;

InputLayer* createInputs(int n) {
	InputLayer* layer = new InputLayer("Input");
	for (int i = 0; i < n; i++) {
		layer->addNode(new InputNode());
	}
	return layer;
}

//Creates a hidden layer with a number attatched to it i
//Creates it with n nodes and linking it to the Layer l
//Returns a new OutputLayer
OutputLayer* createHidden(int i, int n, InputLayer* l) {
	OutputLayer* layer = new OutputLayer("HiddenLayer"+i);
	for (int j = 0; j < n; j++) {
		layer->addNode(new Neuron());
	}
	layer->setSynapses(l);
	return layer;
}
OutputLayer* createOutput(int n, InputLayer* l) {
	OutputLayer* layer = new OutputLayer("Output");
	for (int j = 0; j < n; j++) {
		layer->addNode(new Neuron());
	}
	layer->setSynapses(l);
	return layer;
}
int main() {
	/*
	Program flow:
	1) Instantiate Layersas pointers.
	2) Create Nodes as pointers and add them to the respective layer
	3) Link layers together by passing the layer n-1 into layer n	
	*/

	vector<InputLayer*> network;

	network.push_back(createInputs(1));
	network.push_back(createHidden(1, 4, network[network.size() - 1]));
	network.push_back(createOutput(1, network[network.size() - 1]));


	Node* n1 = new InputNode();
	InputLayer* l = new InputLayer("Test");
	l->addNode(n1);
	cout<<n1->getValue()<<endl;
	cout << l->getName() << endl;
	delete l;

	cout<<n1->getValue();
	
	return 0;
}
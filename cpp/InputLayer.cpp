#include "InputLayer.h"
#include <ctime>

using namespace std;

InputLayer::InputLayer(string name) {
	name_ = name;
	neurons_ = {};
}

InputLayer::InputLayer(vector<Node*> n, string name) {
	name_ = name;
	neurons_ = n;
}

int InputLayer::getNumNodes()const {
	return neurons_.size();
}

void InputLayer::addNode(Node* n) {
	neurons_.push_back(n);
}
InputLayer::~InputLayer() {
	for (int i = 0; i < getNumNodes(); i++) {
		delete neurons_[i];
	}
	neurons_.clear();
}
string InputLayer::getName()const {
	return name_;
}

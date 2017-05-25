#include "Layer.h"
#include <ctime>

using namespace std;

vector<Neuron*> neurons_;
vector<double> weights;

Layer::Layer(vector<Neuron*> n) {
	neurons_ = n;
	for (int i = 0; i < n.size(); i++) {
		time_t timer;
		srand(time(&timer));
		double value = cos(rand());
		weights.push_back(value);
	}
}
void Layer::calcAllValues() {

}
#include "Neuron.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

Neuron::Neuron() {
	thresh_ = 0;
	inputs_ = {};
	time_t timer;
	srand(time(&timer));
	rand_ = (rand() % 2) - 1;
}
Neuron::Neuron(double t) {
	thresh_ = t;
	inputs_ = {};
	time_t timer;
	srand(time(&timer));
	rand_ = (rand() % 2) - 1;
}
void Neuron::setInputs(vector<InputNode*> i) {
	inputs_ = i;
}
void Neuron::setThreshhold(double t) {
	thresh_ = t;
}
bool Neuron::getValue()const {
	return out_ >= value_;
}
double Neuron::sigmoid(double v) {
	return atan(v - rand_) / atan(1) + 0.5;
}
void Neuron::normalize() {

}
void Neuron::sum(vector<double> w) {
	assert(w.size() == inputs_.size());
	double sum = 0;
	for (int i = 0; i < w.size(); i++) {
		sum += w[i] * inputs_[i]->getValue();
	}
	value_ = sigmoid(sum);
}

Neuron& operator*(Neuron& n, double v) {
	return n;
}
Neuron& operator*(double v, Neuron& n) {
	return n;
}
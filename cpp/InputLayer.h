#ifndef __LAYER_H__
#define __LAYER_H__

#include <vector>
#include "Node.h"
#include <string>

using namespace std;
class InputLayer {
protected:
	string name_;
	vector<Node*> neurons_;
public:
	InputLayer(string name = "");
	InputLayer(vector<Node*>, string name = "");
	int getNumNodes()const;
	void addNode(Node*);
	~InputLayer();
	string getName()const;
};
#endif
#ifndef __INPUTNODE_H__
#define __INPUTNODE_H__

#include "Node.h"

using namespace std;

class InputNode : public Node {
public:
	void setValue(double);
	InputNode();
};

#endif
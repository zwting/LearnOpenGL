#include "Node.h"

Node::~Node()
{
	if (model)
	{
		delete model;
		model = nullptr;
	}
}

void Node::calcModelMatrix()
{
	forward = rotation * (-vec3_forward);
	up = rotation * vec3_up;
	right = rotation * vec3_right;

	modelMatrix[0] = glm::vec4(right, 0);
	modelMatrix[1] = glm::vec4(up, 0);
	modelMatrix[2] = glm::vec4(forward, 0);
	modelMatrix[3] = glm::vec4(position, 1);
}

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
	forward = rotation * vec3_forward;
	up = rotation * vec3_up;
	right = rotation * vec3_right;

	modelMatrix = glm::translate(modelMatrix, position);

	mat4x4 matRot(1);
	matRot[0] = glm::vec4(-right, 0);
	matRot[1] = glm::vec4(up, 0);
	matRot[2] = glm::vec4(forward, 0);
	matRot[3] = glm::vec4(position, 1);
	modelMatrix *= matRot;
	modelMatrix = glm::scale(modelMatrix, scale);

	isTransformDirty = false;
}

void Node::Rotate(const quaternion& q)
{
	rotation *= glm::normalize(q);
	calcModelMatrix();
}

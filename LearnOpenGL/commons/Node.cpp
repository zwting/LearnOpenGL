#include "Node.h"
#include "glm/gtx/quaternion.hpp"

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
	mat4x4 matRot = glm::toMat4(rotation);
	modelMatrix *= matRot;
	modelMatrix = glm::scale(modelMatrix, scale);

	isTransformDirty = false;
}

void Node::Rotate(const quaternion& q)
{
	rotation *= glm::normalize(q);
	calcModelMatrix();
}

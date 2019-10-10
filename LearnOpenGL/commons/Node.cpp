#include "Node.h"
#include "glm/gtx/quaternion.hpp"
#include "CommonUtils.h"

Node::~Node()
{
	if (mpModel)
	{
		delete mpModel;
		mpModel = nullptr;
	}
}

void Node::CalcModelMatrix()
{
	mForward = mRotation * -vec3_forward;
	mUp = mRotation * vec3_up;
	mRight = mRotation * vec3_right;

	CommonUtils::IdentityMat(mModelMatrix);

	mModelMatrix = glm::translate(mModelMatrix, mPosition);
	mat4x4 matRot = glm::toMat4(mRotation);
	mModelMatrix *= matRot;
	mModelMatrix = glm::scale(mModelMatrix, mScale);

	mIsTransformDirty = false;
}

void Node::Rotate(const quaternion& q)
{
	// rotation = glm::normalize(q) * rotation;
	// calcModelMatrix();
}

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

void Node::CheckIsDirty() const
{
	if(!mIsTransformDirty)
	{
		return;
	}

	if(mDirtyCallback != nullptr)
	{
		mDirtyCallback();
	}
}

void Node::CalcModelMatrix()
{
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

void Node::LookAt(const vec3& target, const vec3& worldUp)
{
	const vec3 forward = glm::normalize(mPosition- target);
	const vec3 right = glm::cross(worldUp, forward);
	const vec3 up = glm::cross(forward, right);

	mRotation = glm::quat_cast(glm::mat3(right, up, forward));

	mIsTransformDirty = true;
	CheckIsDirty();
}

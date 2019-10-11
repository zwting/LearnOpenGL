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
	if (!mIsTransformDirty)
	{
		return;
	}

	if (mDirtyCallback != nullptr)
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
	const vec3 forward = glm::normalize(mPosition - target);
	//这里不调用normalize就会出现奇怪现象，原因就是 axb = |a|x|b|x sin(alpha)，即使
	// a,b都是单位向量，结果向量的长度取值范围是 [0, 1]。小于1不是单位向量，所以必须规格化。
	const vec3 right = glm::normalize(glm::cross(worldUp, forward));
	// 这里可以不规格化是因为 forward 和 right的夹角为90。sin(90) = 1, 所以结果向量的长度 为|forward|x|right| = 1。直接就是单位向量
	const vec3 up = glm::cross(forward, right);

	mRotation = glm::quat_cast(glm::mat3(right, up, forward));

	mIsTransformDirty = true;
	CheckIsDirty();
}

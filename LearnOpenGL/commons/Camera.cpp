#include "Camera.h"

Camera::Camera(vec3& pos, vec3& forward, float fov, float near, float far, vec3 up)
{
	mPosition = pos;
	mForward = forward;
	mFov = fov;
	mNear = near;
	mFar = far;
	mWorldUp = up;
}

const mat4x4& Camera::GetViewMatrix()
{
	mViewMatrix[0][0] = mRight.x;
	mViewMatrix[0][1] = mRight.y;
	mViewMatrix[0][2] = mRight.z;

	mViewMatrix[1][0] = mUp.x;
	mViewMatrix[1][1] = mUp.y;
	mViewMatrix[1][2] = mUp.z;

	mViewMatrix[2][0] = mForward.x;
	mViewMatrix[2][1] = mForward.y;
	mViewMatrix[2][2] = mForward.z;

	// mViewMatrix[3][0] = 

	return mViewMatrix;
}

const mat4x4& Camera::GetProjMatrix()
{
}

void Camera::LookAt(const vec3& target, const vec3& worldUp)
{
	mForward = glm::normalize(target - mPosition);
	mRight = glm::cross(mForward, worldUp);
	mUp = glm::cross(mRight, mForward);
}

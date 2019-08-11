#pragma once
#include <glm/glm.hpp>
class Camera
{
private:
	int _fov;
	float _aspect;
	float _near;
	float _far;
	bool _isActive;
public:
	static Camera* s_pCurCamera;

	Camera(int fov, float aspect, float near, float far, glm::vec3 pos = glm::vec3(0.0f));

	void Active();
};

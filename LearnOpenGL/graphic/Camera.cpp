#include "Camera.h"

Camera* Camera::s_pCurCamera = nullptr;

Camera::Camera(int fov, float aspect, float near, float far, glm::vec3 pos)
{
	
}

void Camera::Active()
{
	if(s_pCurCamera != nullptr)
	{
		s_pCurCamera->_isActive = false;
	}
	s_pCurCamera = this;
	_isActive = true;
}

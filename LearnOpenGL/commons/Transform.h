#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

class Transform
{
	
private:
	glm::vec3 _localPosition;
public:
	glm::vec3 localPosition() const
	{
		return _localPosition;
	}

	void localPosition(const glm::vec3& vec3)
	{
		_localPosition = vec3;
	}

	void setPosition(const glm::vec3& vec3)
	{
		_position = vec3;
	}

	void localRotation(const glm::quat& quat)
	{
		_localRotation = quat;
	}

	void setRotation(const glm::quat& quat)
	{
		_rotation = quat;
	}

	void setScale(const glm::vec3& vec3)
	{
		_scale = vec3;
	}

	glm::vec3 position() const
	{
		return _position;
	}

	glm::quat localRotation() const
	{
		return _localRotation;
	}

	glm::quat rotation() const
	{
		return _rotation;
	}

	glm::vec3 scale() const
	{
		return _scale;
	}

private:
	glm::vec3 _position;
	glm::quat _localRotation;
	glm::quat _rotation;
	glm::vec3 _scale;

public:
	void Rotate(float angle, glm::vec3 axis);
	void Translate(glm::vec3 pos);
};

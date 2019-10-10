#pragma once

#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef glm::vec3 vec3;
typedef glm::vec2 vec2;
typedef glm::quat quaternion;
typedef glm::mat4x4 mat4x4;

#define VALUE_PTR glm::value_ptr
#define MAT_IDENTITY mat4x4(1.0f)

#define VEC3_ZERO vec3(0, 0, 0)
#define VEC3_ONE vec3(1, 1, 1)
#define VEC3_UP vec3(0, 1, 0)
#define VEC3_DOWN vec3(0, -1, 0)
#define VEC3_LEFT vec3(-1, 0, 0)
#define VEC3_RIGHT vec3(1, 0, 0)
#define VEC3_FORWARD vec3(0, 0, 1)
#define VEC3_BACK vec3(0, 0, -1)

#define QUA_IDENTITY quaternion(1,0,0,0)

#pragma once

#include <glm/glm.hpp>

typedef glm::vec3 vec3;
typedef glm::quat qua;
typedef glm::mat4x4 mat4x4;

#define mat_identity mat4x4(1.0f)

#define vec3_zero vec3(0,0,0)
#define vec3_one vec3(1,1,1)
#define vec3_up vec3(0,1,0)
#define vec3_down vec3(0, -1, 0)
#define vec3_left vec3(1,0,0)
#define vec3_right vec3(-1,0,0)
#define vec3_forward vec3(0,0,1)
#define vec3_back vec3(0,0,-1)

#define qua_identity qua();

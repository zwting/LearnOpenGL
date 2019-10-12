#pragma once
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include "Time.h"
#include "MathType.h"
#include "glm/gtx/norm.hpp"

class CommonUtils
{
public:
	static Time* s_time;
public:
	static std::string ReadTextFromFile(const char* path)
	{
		assert(path != nullptr);
		std::fstream f(path, std::ios_base::in);
		std::stringstream buffer;
		buffer << f.rdbuf();
		return buffer.str();
	}

	static std::string CombinePath(const std::string& path, const std::string& fileName)
	{
		if (!path.empty() && !fileName.empty())
		{
			char lastOfPath = path[path.size() - 1];
			if (lastOfPath == '\\' || lastOfPath == '/')
			{
				return path + fileName;
			}
			return path + '/' + fileName;
		}

		if (path.empty())
		{
			return fileName;
		}

		if(fileName.empty())
		{
			return path;
		}

		return nullptr;
	}

	static float Clamp01(float val)
	{
		return Clamp(val, 0, 1);
	}

	static float Clamp(float val, float min, float max)
	{
		if (val < min) return min;
		if (val > max) return max;
		return val;
	}

	static void IdentityMat(mat4x4& mat)
	{
		mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1;
		mat[0][1] = mat[0][2] = mat[0][3] = 0;
		mat[1][0] = mat[1][2] = mat[1][3] = 0;
		mat[2][0] = mat[2][1] = mat[2][3] = 0;
		mat[3][0] = mat[3][1] = mat[3][2] = 0;
	}

	static quaternion FromDirectionTo(const vec3& u, const vec3& v)
	{
		float norm_u_v = glm::sqrt(glm::length2(u) * glm::length2(v));
		vec3 w = glm::cross(u, v);
		return glm::normalize(quaternion(norm_u_v + glm::dot(u, v), w.x, w.y, w.z));
	}
};

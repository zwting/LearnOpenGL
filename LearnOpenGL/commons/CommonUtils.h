#pragma once
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include "Time.h"
#include "MathType.h"

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
};

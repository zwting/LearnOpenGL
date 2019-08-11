#pragma once
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include "Time.h"
#include "glad/glad.h"

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
};

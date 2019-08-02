#pragma once
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>

class CommonUtils
{
public:
	static std::string ReadTextFromFile(const char* path)
	{
		assert(path != nullptr);

		std::fstream f(path, std::ios_base::in);
		std::stringstream buffer;
		buffer << f.rdbuf();
		return buffer.str();
	}
};

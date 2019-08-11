#pragma once
#include <string>
#include <fstream>
#include <sstream>

class CommonUtils
{
public:
	static std::string LoadStrFromFile(const char* path)
	{
		std::fstream f(path, std::ios_base::in);
		std::stringstream buffer;
		buffer << f.rdbuf();
		std::string ret = std::string(buffer.str());
		f.close();
		return ret;
	}
};

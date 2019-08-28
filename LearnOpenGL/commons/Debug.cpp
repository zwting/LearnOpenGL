#include "Debug.h"
#include <cstdarg>

char* Debug::_buffer = new char[1024];

void Debug::Log(const char* msg, ...)
{
	va_list  vl;
	va_start(vl, msg);
}



void Debug::LogError(const char* msg, ...)
{
}

void Debug::LogWarning(const char* msg, ...)
{
}

void Debug::PackLogMsg(const char* msg, ...)
{
}

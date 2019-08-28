#pragma once

class Debug
{
private:
	static char* _buffer;
public:
	static void Log(const char* msg, ...);
	static void LogError(const char* msg, ...);
	static void LogWarning(const char* msg, ...);
private:
	static void PackLogMsg(const char* msg, ...);
};

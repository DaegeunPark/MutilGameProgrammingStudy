#pragma once
namespace StringUilities
{
	string GetCommandLineArg(int index);
	
	string Sprintf(const char* format, ...);

	void Log(const char* format);
	void Log(const char* format, ...);
}

#define LOG(...) StringUilities::Log(__VA_ARGS__);
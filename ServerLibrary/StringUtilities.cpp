#include "stdafx.h"

#if !_WIN32
extern const char** __argv;
extern int __argc;
void OutputDebugString(const char* text)
{
	printf("%s", text);
}
#endif

string StringUilities::GetCommandLineArg(int index)
{
	if (index < __argc)
		return string(__argv[index]);
	else
		return string();
}

string StringUilities::Sprintf(const char* format, ...)
{
	char temp[4096];

	va_list args;
	va_start(args, format);
	
#if _WIN32
	_vsnprintf_s(temp, 4096, 4096, format, args);
#else
	vsnprintf(temp, 4096, format, args);
#endif

	return string(temp);
}

void StringUilities::Log(const char* format)
{
	OutputDebugString(format);
	OutputDebugString("\n");
}

void StringUilities::Log(const char* format, ...)
{
	char temp[4096];

	va_list args;
	va_start(args, format);

#if _WIN32
	_vsnprintf_s(temp, 4096, 4096, format, args);
#else
	vsnprintf(temp, 4096, format, args);
#endif

	OutputDebugString(temp);
	OutputDebugString("\n");
}

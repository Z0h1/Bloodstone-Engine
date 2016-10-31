#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#define OS WIN
#elif defined(unix) || defined(__unix) || defined(__unix__)
	#define OS UNIX
#elif defined(__APPLE__) || defined(__MACH__)
	#define OS APPLE
#endif
#pragma once

#ifdef _WIN32
	#define SPRINTF		sprintf_s
	#define STRERROR	strerror_s
	#define SSCANF		sscanf_s
	#define STRERROR	strerror_s
#else
	#define SPRINTF		sprintf
	#define STRERROR	strerror
	#define SSCANF		sscanf
	#define STRERROR strerror
#endif
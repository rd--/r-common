#ifndef R_COMMON_C_FAILURE_H
#define R_COMMON_C_FAILURE_H

#include <unistd.h>

#ifndef FAILURE
#define FAILURE _exit(1)
#endif

#define die(...) \
	{ \
		(void)fprintf(stderr, __VA_ARGS__); \
		_exit(1); \
	}

#define die_when(x, ...) \
	if (x) { \
		(void)fprintf(stderr, __VA_ARGS__); \
		_exit(1); \
	}

#endif

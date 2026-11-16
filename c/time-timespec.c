#include <math.h>
#include <stdlib.h>

#include "time-timespec.h"

/* Integer microseconds (us) to timespec (t). */
struct timespec usec_to_timespec(unsigned long us)
{
	struct timespec t;
	long ns = (long)us * 1000L;
	ldiv_t d = ldiv(ns, 1000000000L);
	t.tv_sec = d.quot;
	t.tv_nsec = d.rem;
	return t;
}

/* Fractional seconds (s) to timespec (t). */
struct timespec double_to_timespec(double s)
{
	struct timespec t;
	double integer_part_s = floor(s);
	double fractional_part_ns = (s - integer_part_s) * 1.0e9;
	t.tv_sec = (time_t)integer_part_s;
	t.tv_nsec = (long)fractional_part_ns;
	return t;
}

/* Timespec (t) to fractional seconds (s). */
double timespec_to_double(struct timespec t)
{
	return t.tv_sec + (t.tv_nsec / 1.0e9);
}

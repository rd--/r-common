#include "float.h"
#include "hermite.h"

/* 4-point, 3rd-order Hermite (x-form) */
f32 hermitef(f32 x, f32 y0, f32 y1, f32 y2, f32 y3)
{
	f32 c0 = y1;
	f32 c1 = 0.5F * (y2 - y0);
	f32 c2 = y0 - 2.5F * y1 + 2.0F * y2 - 0.5F * y3;
	f32 c3 = 1.5F * (y1 - y2) + 0.5F * (y3 - y0);
	return ((c3 * x + c2) * x + c1) * x + c0;
}

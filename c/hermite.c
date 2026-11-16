#include "hermite.h"

/* 4-point, 3rd-order Hermite (x-form) */
R hermitef(R x, R y0, R y1, R y2, R y3)
{
	R c0 = y1;
	R c1 = 0.5F * (y2 - y0);
	R c2 = y0 - 2.5F * y1 + 2.0F * y2 - 0.5F * y3;
	R c3 = 1.5F * (y1 - y2) + 0.5F * (y3 - y0);
	return ((c3 * x + c2) * x + c1) * x + c0;
}

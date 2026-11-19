#include <math.h>

#include "biquad.h"
#include "float.h"

f64 biquad_normalised_direct_form_1(f64 x0, f64 b0, f64 b1, f64 b2, f64 a1, f64 a2, f64 *x1, f64 *x2, f64 *y1, f64 *y2)
{
	f64 y0 = (b0 * x0) + (b1 * *x1) + (b2 * *x2) - (a1 * *y1) - (a2 * *y2);
	*x2 = *x1;
	*x1 = x0;
	*y2 = *y1;
	*y1 = y0;
	return y0;
}

f64 biquad_normalised_direct_form_2(f64 x0, f64 b0, f64 b1, f64 b2, f64 a1, f64 a2, f64 *w1, f64 *w2)
{
	f64 w0 = x0 - (a1 * *w1) - (a2 * *w2);
	f64 y0 = (b0 * w0) + (b1 * *w1) + (b2 * *w2);
	*w2 = *w1;
	*w1 = w0;
	return y0;
}

f64 biquad_transposed_normalised_direct_form_2(f64 x0, f64 b0, f64 b1, f64 b2, f64 a1, f64 a2, f64 *w1, f64 *w2)
{
	f64 y0 = (b0 * x0) + *w1;
	*w1 = (b1 * x0) - (a1 * y0) + *w2;
	*w2 = (b2 * x0) - (a2 * y0);
	return y0;
}

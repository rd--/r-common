#ifndef R_COMMON_C_BIQUAD_H
#define R_COMMON_C_BIQUAD_H

#include "float.h"

f64 biquad_normalised_direct_form_1(f64 x0, f64 b0, f64 b1, f64 b2, f64 a1, f64 a2, f64 *x1, f64 *x2, f64 *y1, f64 *y2);
f64 biquad_normalised_direct_form_2(f64 x0, f64 b0, f64 b1, f64 b2, f64 a1, f64 a2, f64 *w1, f64 *w2);
f64 biquad_transposed_normalised_direct_form_2(f64 x0, f64 b0, f64 b1, f64 b2, f64 a1, f64 a2, f64 *w1, f64 *w2);

#endif

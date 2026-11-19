#ifndef _R_COMMON_C_FILTER_H
#define _R_COMMON_C_FILTER_H

#include <stdbool.h>

#include "float.h"

f64 fosCoefStep(f64 in, f64 a0, f64 a1, f64 b1, f64 *in1, f64 *out1);
f64 sosCoefStep(f64 in, f64 a0, f64 a1, f64 a2, f64 b1, f64 b2, f64 *in1, f64 *in2, f64 *out1, f64 *out2);
f64 iir2CoefStep(f64 in, f64 a0, f64 b1, f64 b2, f64 *out1, f64 *out2);

void bwLpfOrHpfCoef(bool isHpf, f64 sr, f64 freq, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2);
void rlpfCoef(f64 radiansPerSample, f64 freq, f64 rq, f64 *a0, f64 *b1, f64 *b2);
void resonzCoef(f64 radiansPerSample, f64 freq, f64 rq, f64 *a0, f64 *b1, f64 *b2);

typedef struct {
	f64 a0, a1, b1;
} fos;

typedef struct {
	f64 a0, a1, a2, b1, b2;
} sos;

typedef struct {
	f64 a0, b1, b2;
} iir2;

sos bwLpfOrHpf(bool isHpf, f64 sr, f64 freq);
iir2 rlpf(f64 radiansPerSample, f64 freq, f64 rq);
iir2 resonz(f64 radiansPerSample, f64 freq, f64 rq);

typedef struct {
	f64 in1, out1;
} fosState;

typedef struct {
	f64 in1, in2, out1, out2;
} sosState;

typedef struct {
	f64 out1, out2;
} iir2State;

f64 fosStep(f64 in, fos c, fosState *s);
f64 sosStep(f64 in, sos c, sosState *s);
f64 iir2Step(f64 in, iir2 c, iir2State *s);

#endif

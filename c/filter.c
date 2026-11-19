#include <math.h>
#include <stdbool.h>

#include "biquad.h"
#include "filter.h"
#include "float.h"

#define PI (3.14159265358979323846)

f64 fosCoefStep(f64 x0, f64 b0, f64 b1, f64 a1, f64 *x1, f64 *y1)
{
	f64 y0 = (b0 * x0) + (b1 * *x1) + (a1 * *y1);
	*x1 = x0;
	*y1 = y0;
	return y0;
}

f64 sosCoefStep(f64 x0, f64 b0, f64 b1, f64 b2, f64 a1, f64 a2, f64 *x1, f64 *x2, f64 *y1, f64 *y2)
{
	return biquad_normalised_direct_form_1(x0, b0, b1, b2, -a1, -a2, x1, x2, y1, y2);
}

f64 iir2CoefStep(f64 x0, f64 b0, f64 a1, f64 a2, f64 *y1, f64 *y2)
{
	f64 y0 = (b0 * x0) + (a1 * *y1) + (a2 * *y2);
	*y2 = *y1;
	*y1 = y0;
	return y0;
}

// Butterworth low pass or high pass Sos filter coefficients.
void bwLpfOrHpfCoef(bool isHpf, f64 sr, f64 freq, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2)
{
	f64 f = freq * PI / sr;
	f64 c = isHpf ? tan(f) : 1 / tan(f);
	f64 c2 = c * c;
	f64 s2c = sqrt(2) * c;
	*a0 = 1 / (1 + s2c + c2);
	*a1 = isHpf ? -2 * *a0 : 2 * *a0;
	*a2 = *a0;
	*b1 = isHpf ? 2 * (c2 - 1) * *a0 : 2 * (1 - c2) * *a0;
	*b2 = (1 - s2c + c2) * *a0;
}

// f64lpf Iir2 coefficients, (a0, b1, b2).
void rlpfCoef(f64 radiansPerSample, f64 freq, f64 rq, f64 *a0, f64 *b1, f64 *b2)
{
	f64 qr = 0.001 > rq ? 0.001 : rq;
	f64 pf = freq * radiansPerSample;
	f64 d = tan(pf * qr * 0.5);
	f64 c = (1 - d) / (1 + d);
	*b1 = (1 + c) * cos(pf);
	*a0 = (1 + c - *b1) * 0.25;
	*b2 = -c;
}

// f64esonz Iir2 coefficients, (a0, b1, b2).
void resonzCoef(f64 radiansPerSample, f64 freq, f64 rq, f64 *a0, f64 *b1, f64 *b2)
{
	f64 ff = freq * radiansPerSample;
	f64 b = ff * rq;
	f64 r = 1 - b * 0.5;
	f64 twof64 = 2 * r;
	f64 r2 = r * r;
	f64 ct = (twof64 * cos(ff)) / (1 + r2);
	*a0 = (1 - r2) * 0.5;
	*b1 = twof64 * ct;
	*b2 = -r2;
}

f64 fosStep(f64 in, fos c, fosState *s)
{
	return fosCoefStep(in, c.a0, c.a1, c.b1, &(s->in1), &(s->out1));
}

f64 sosStep(f64 in, sos c, sosState *s) {
	return sosCoefStep(in, c.a0, c.a1, c.a2, c.b1, c.b2, &(s->in1), &(s->in2), &(s->out1), &(s->out2));
}

f64 iir2Step(f64 in, iir2 c, iir2State *s) {
	return iir2CoefStep(in, c.a0, c.b1, c.b2, &(s->out1), &(s->out2));
}

sos bwLpfOrHpf(bool isHpf, f64 sr, f64 freq)
{
	sos c;
	bwLpfOrHpfCoef(isHpf, sr, freq, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2);
	return c;
}
iir2 rlpf(f64 radiansPerSample, f64 freq, f64 rq)
{
	iir2 c;
	rlpfCoef(radiansPerSample, freq, rq, &c.a0, &c.b1, &c.b2);
	return c;
}
iir2 resonz(f64 radiansPerSample, f64 freq, f64 rq)
{
	iir2 c;
	resonzCoef(radiansPerSample, freq, rq, &c.a0, &c.b1, &c.b2);
	return c;
}

/* Beq filter coefficient calculations, results are (a0, a1, a2, b1, b2). */

#include <math.h>

#include "beq.h"
#include "float.h"

#define PI (3.14159265358979323846)

// Calculate coefficients for bi-quad low pass filter.
void beqLowPassCoef(f64 sr, f64 freq, f64 rq, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2)
{
	f64 w0 = PI * 2 * freq * (1 / sr);
	f64 cos_w0 = cos(w0);
	f64 i = 1 - cos_w0;
	f64 alpha = sin(w0) * 0.5 * rq;
	f64 b0rz = 1 / (1 + alpha);
	*a0 = i * 0.5 * b0rz;
	*a1 = i * b0rz;
	*a2 = *a0;
	*b1 = cos_w0 * 2 * b0rz;
	*b2 = (1 - alpha) * -b0rz;
}

// Calculate coefficients for bi-quad high pass filter.
void beqHiPassCoef(f64 sr, f64 freq, f64 rq, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2)
{
	f64 w0 = PI * 2 * freq * (1 / sr);
	f64 cos_w0 = cos(w0);
	f64 i = 1 + cos_w0;
	f64 alpha = sin(w0) * 0.5 * rq;
	f64 b0rz = 1 / (1 + alpha);
	*a0 = i * 0.5 * b0rz;
	*a1 = -i * b0rz;
	*a2 = *a0;
	*b1 = cos_w0 * 2 * b0rz;
	*b2 = (1 - alpha) * -b0rz;
}

// Calculate coefficients for bi-quad all pass filter.
void beqAllPassCoef(f64 sr, f64 freq, f64 rq, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2)
{
	f64 w0 = PI * 2 * freq * (1 / sr);
	f64 alpha = sin(w0) * 0.5 * rq;
	f64 b0rz = 1 / (1 + alpha);
	*a0 = (1 - alpha) * b0rz;
	*a2 = 1;
	*b1 = 2 * cos(w0) * b0rz;
	*a1 = -*b1;
	*b2 = -*a0;
}

// Calculate coefficients for bi-quad band pass filter.
void beqBandPassCoef(f64 sr, f64 freq, f64 bw, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2)
{
	f64 w0 = PI * 2 * freq * (1 / sr);
	f64 sin_w0 = sin(w0);
	f64 alpha = sin_w0 * sinh(0.34657359027997 * bw * w0 / sin_w0);
	f64 b0rz = 1 / (1 + alpha);
	*a0 = alpha * b0rz;
	*a1 = 0;
	*a2 = -*a0;
	*b1 = cos(w0) * 2 * b0rz;
	*b2 = (1 - alpha) * -b0rz;
}

// Calculate coefficients for bi-quad stop band filter.
void beqBandStopCoef(f64 sr, f64 freq, f64 bw, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2)
{
	f64 w0 = PI * 2 * freq * (1 / sr);
	f64 sin_w0 = sin(w0);
	f64 alpha = sin_w0 * sinh(0.34657359027997 * bw * w0 / sin_w0);
	f64 b0rz = 1 / (1 + alpha);
	*a0 = b0rz;
	*a2 = b0rz;
	*b1 = 2 * cos(w0) * b0rz;
	*a1 = -*b1;
	*b2 = (1 - alpha) * -b0rz;
}

// Calculate coefficients for bi-quad peaking EQ filter.
void beqPeakEqCoef(f64 sr, f64 freq, f64 rq, f64 db, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2)
{
	f64 a = pow(10, db / 40);
	f64 w0 = PI * 2 * freq * (1 / sr);
	f64 alpha = sin(w0) * 0.5 * rq;
	f64 b0rz = 1 / (1 + (alpha / a));
	*a0 = (1 + (alpha * a)) * b0rz;
	*a2 = (1 - (alpha * a)) * b0rz;
	*b1 = 2 * cos(w0) * b0rz;
	*a1 = -*b1;
	*b2 = (1 - (alpha / a)) * -b0rz;
}

// Calculate coefficients for bi-quad low shelf filter.
void beqLowShelfCoef(f64 sr, f64 freq, f64 rs, f64 db, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2)
{
	f64 a = pow(10, db / 40);
	f64 w0 = PI * 2 * freq * (1 / sr);
	f64 cos_w0 = cos(w0);
	f64 sin_w0 = sin(w0);
	f64 alpha = sin_w0 * 0.5 * sqrt((a + (1 / a)) * (rs - 1) + 2);
	f64 i = (a + 1) * cos_w0;
	f64 j = (a - 1) * cos_w0;
	f64 k = 2 * sqrt(a) * alpha;
	f64 b0rz = 1 / ((a + 1) + j + k);
	*a0 = a * ((a + 1) - j + k) * b0rz;
	*a1 = 2 * a * ((a - 1) - i) * b0rz;
	*a2 = a * ((a + 1) - j - k) * b0rz;
	*b1 = 2 * ((a - 1) + i) * b0rz;
	*b2 = ((a + 1) + j - k) * -b0rz;
}

// Calculate coefficients for bi-quad high shelf filter.
void beqHiShelfCoef(f64 sr, f64 freq, f64 rs, f64 db, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2)
{
	f64 a = pow(10, db / 40);
	f64 w0 = PI * 2 * freq * (1 / sr);
	f64 cos_w0 = cos(w0);
	f64 sin_w0 = sin(w0);
	f64 alpha = sin_w0 * 0.5 * sqrt((a + (1 / a)) * (rs - 1) + 2);
	f64 i = (a + 1) * cos_w0;
	f64 j = (a - 1) * cos_w0;
	f64 k = 2 * sqrt(a) * alpha;
	f64 b0rz = 1 / ((a + 1) - j + k);
	*a0 = a * ((a + 1) + j + k) * b0rz;
	*a1 = -2 * a * ((a - 1) + i) * b0rz;
	*a2 = a * ((a + 1) + j - k) * b0rz;
	*b1 = -2 * ((a - 1) - i) * b0rz;
	*b2 = ((a + 1) - j - k) * -b0rz;
}

sos beqLowPass(f64 sr, f64 freq, f64 rq)
{
	sos c;
	beqLowPassCoef(sr, freq, rq, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2);
	return c;
}
sos beqHiPass(f64 sr, f64 freq, f64 rq)
{
	sos c;
	beqHiPassCoef(sr, freq, rq, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2);
	return c;
}
sos beqAllPass(f64 sr, f64 freq, f64 rq)
{
	sos c;
	beqAllPassCoef(sr, freq, rq, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2);
	return c;
}
sos beqBandPass(f64 sr, f64 freq, f64 bw)
{
	sos c;
	beqBandPassCoef(sr, freq, bw, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2);
	return c;
}
sos beqBandStop(f64 sr, f64 freq, f64 bw)
{
	sos c;
	beqBandStopCoef(sr, freq, bw, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2);
	return c;
}
sos beqPeakEq(f64 sr, f64 freq, f64 rq, f64 db)
{
	sos c;
	beqPeakEqCoef(sr, freq, rq, db, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2);
	return c;
}
sos beqLowShelf(f64 sr, f64 freq, f64 rs, f64 db)
{
	sos c;
	beqLowShelfCoef(sr, freq, rs, db, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2);
	return c;
}
sos beqHiShelf(f64 sr, f64 freq, f64 rs, f64 db)
{
	sos c;
	beqHiShelfCoef(sr, freq, rs, db, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2);
	return c;
}

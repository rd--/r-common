#ifndef R_COMMON_C_BEQ_H
#define R_COMMON_C_BEQ_H

#include "filter.h"
#include "float.h"

void beqLowPassCoef(f64 sr, f64 freq, f64 rq, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2);
void beqHiPassCoef(f64 sr, f64 freq, f64 rq, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2);
void beqAllPassCoef(f64 sr, f64 freq, f64 rq, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2);
void beqBandPassCoef(f64 sr, f64 freq, f64 bw, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2);
void beqBandStopCoef(f64 sr, f64 freq, f64 bw, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2);
void beqPeakEqCoef(f64 sr, f64 freq, f64 rq, f64 db, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2);
void beqLowShelfCoef(f64 sr, f64 freq, f64 rs, f64 db, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2);
void beqHiShelfCoef(f64 sr, f64 freq, f64 rs, f64 db, f64 *a0, f64 *a1, f64 *a2, f64 *b1, f64 *b2);

sos beqLowPass(f64 sr, f64 freq, f64 rq);
sos beqHiPass(f64 sr, f64 freq, f64 rq);
sos beqAllPass(f64 sr, f64 freq, f64 rq);
sos beqBandPass(f64 sr, f64 freq, f64 bw);
sos beqBandStop(f64 sr, f64 freq, f64 bw);
sos beqPeakEq(f64 sr, f64 freq, f64 rq, f64 db);
sos beqLowShelf(f64 sr, f64 freq, f64 rs, f64 db);
sos beqHiShelf(f64 sr, f64 freq, f64 rs, f64 db);

#endif

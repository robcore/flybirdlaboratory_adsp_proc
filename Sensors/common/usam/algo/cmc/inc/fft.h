#ifndef FFT_H
#define FFT_H

typedef __complex__ float  cfloat;

#ifndef __linux__

void sfpFFT( cfloat *Input, int points, cfloat *twiddles, cfloat *Output);
void gentwiddle( cfloat *twiddle, int NP, int log2NP );

#else

#include "fft_autogen.h"

#define  sfpFFT( Input, points, twiddles, Output) fft_autogen(Input, points, Output)
#define gentwiddle(twiddle, NP, log2NP)

#endif

#endif //FFT_H

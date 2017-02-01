#ifndef __FFT_H__
#define __FFT_H__

void fft(int inverse, floatSingleArray *R, floatSingleArray *I);
void adcFFTInit(int deltaT);
void FFTInit(int deltaF);
void getTabsFFT(floatSingleArray *real,floatSingleArray *imag);

#endif

#ifndef __FFT_H__
#define __FFT_H__

void fft(int inverse, struct floatSingleArray *real, struct floatSingleArray *imag);
void adcFFTInit(int deltaT);
void FFTInit(int deltaF);
void getTabsFFT(struct floatSingleArray *real,struct floatSingleArray *imag);

#endif

#ifndef __FFT_H__
#define __FFT_H__

void fft(int inverse, float *R, float *I);
void adcFFTInit(int deltaT);
void FFTInit(int deltaF);
void getTabsFFT(float *real,float *imag);

#endif
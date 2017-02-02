#ifndef __FFT_H__
#define __FFT_H__

#define DIRECT_FFT 1
#define INVERSE_FFT (-1)

//void fft(short int dir,struct floatSingleArray *real,struct floatSingleArray *imag);
void fft(uint8_t dir, userComplexArray *vect);
void __adcFFTInit(uint32_t deltaT);
void __FFTInit(uint32_t deltaF);
void fftGeneralInit(uint32_t deltaT, uint32_t deltaF);
//void getTabsFFT(struct floatSingleArray *real,struct floatSingleArray *imag);
void getTabsFFT(userComplexArray *vect);

#endif

#ifndef __FFTDESCRIBE_H__
#define __FFTDESCRIBE_H__

#include <vector.h>

void complexLinearToComplexExponential(const vector<float> real, const vector<float> imag, vector<float> *mod, vector<float> *arg);

void complexExponentialToComplexLinear(const vector<float> mod, const vector<float> arg, vector<float> *real, vector<float> *imag);

void extractEnveloppes(const vector<float> mod, const vector<float> arg, vector<vector<float>> *envs)



#endif

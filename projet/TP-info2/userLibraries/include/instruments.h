#ifndef __INSTRUMENTS_H__
#define __INSTRUMENTS_H__

struct Instrument
{
	char name[50];
	char codeMIDI;
	float H0;
	float H1;
	float H2;
	float H3;
	float H4;
	float H5;
	float H6;
	float H7;
	float H8;
	float H9;
	float H10;
	float H11;
	float H12;
	float H13;
	float H14;
	float H16;
}

Instrument getInstru(float *env, Instrument *listInstru);

float getFreqPlay(float *env, Instrument instru);


#endif

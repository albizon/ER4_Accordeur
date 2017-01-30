#include "define.h"
#include "fft.h"
#include "note.h"

/*
En entrée : 
  N : nombre de points en puissance de 2,
  R, I : tableaux de N points contenant les parties réelles (R) et imaginaires (I) du signal d'entrée. Pour un signal réel, I doit être initialisé à 0.
  inverse : booléen qui indique si le calcul est une transformée directe (False) ou inverse (True).
En sortie : 
  R,I : tableaux qui contiennent les parties réelles et imaginaires de la transformée de FOURIER directe ou inverse calculée.
  Type RESULD : Array [0..1023] Of Real ;
*/

void fft(const int N, int inverse, float *R, float *I)
{
  const float PI = 3.141592 ;
  const float UFL = 1.0E-38 ;
  const float OVF = 1.0E38 ;
  float N1,N2,J,K,M,L1,L2,L,I5,IJ;
  float T1,T2,W1,W2,U1,U2,Z1,Z2;
  
  if (inverse==TRUE)
  {
      for (IJ=0; IJ<(N-1);IJ++)
      {
        R[IJ] := R[IJ]/N;
			  I[IJ] := I[IJ]/N;
      }
  }
  
  M = arrondi(log(N)/log(2)) ;
	N2 = N / 2 ;
	N1 = N-1 ;
	J = 1 ;
  
  for (IJ=0; IJ<N1);IJ++)
  {
  			 if (IJ<J)
         {
				     T1 = R[J-1] ;
				     T2 = I[J-1] ;
				     R[J-1] = R[IJ-1] ;
				     I[J-1] = I[IJ-1] ;
				     R[IJ-1] = T1 ;
				     I[IJ-1] = T2 ;
         }
         K = N2 ;
         do {
				     J := J - K ;
				     K:=K div 2 ;
         } While (K<J);
         J := J+K ;
  }
  
  for  (L=1, L<M; L++ )
  {
		       L1 := trunc(exp(L*ln(2))) ;
		       L2 := L1 div 2 ;
		       U1 := 1 ;
		       U2 := 0 ;
		       W1 := COS(PI/L2) ;
		       W2 := -SIN(PI/L2) ;
		       If inverse Then W2 := -W2 ;
		       for (J=1; J<L2; J++ )
           {
			         IJ = J ;
			          do{
                   I5 := IJ+L2 ;
                   T1 := R[I5-1]*U1-I[I5-1]*U2 ;
                   T2 := R[I5-1]*U2+I[I5-1]*U1 ;
                   R[I5-1] := R[IJ-1] - T1 ;
                   I[I5-1] := I[IJ-1] - T2 ;
                   R[IJ-1] := R[IJ-1] + T1 ;
                   I[IJ-1] := I[IJ-1] + T2 ;
                   IJ := IJ + L1 ;
                } while( IJ>=N) ;
             
                Z1:=U1*W1-U2*W2 ;
             
                if (abs(Z1)>OVF)
                {
                  if (Z1>0) Z1 = OVF;
                  else Z1 := -OVF ;
                }
             
                if (abs(Z1)<UFL)
                {
                  Z1 := 0 ;
                 	Z2 := U1*W2+U2*W1 ;
                }
             
			          if (abs(Z2)>OVF) 
                {
                  if (Z2>0) Z2 := OVF;
                  else Z2 = 0-OVF ;
                }
             
		          	if (abs(Z2)<UFL) 
                {
                  Z1 := 0 ;
                	U1 := Z1 ;
                }
             
			          U2 := Z2 ;
           }
  }  
}


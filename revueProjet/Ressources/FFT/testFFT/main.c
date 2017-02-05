#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define Nb 512
#define NbPointsParPeriodes 10

int main()
{
    int i=0;
    printf("Hello world!\n");
    float x[Nb];
    float y[Nb];
    for ( i=0; i<Nb; i++) x[i]=0;
    for ( i=0; i<Nb; i++) y[i]=0;

    x[5]=1;
    //for ( i=0; i<Nb; i++) x[i]=sin((2.0 * 3.14 * i)/NbPointsParPeriodes);

            for ( i=0; i<Nb; i++) printf("%.1f ",x[i]);
            printf("\n\n");
            for ( i=0; i<Nb; i++) printf("%.2f ",y[i]);
            printf("\n\n\n");

    FFT(-1,x,y);

            for ( i=0; i<Nb; i++) printf("%.2f ",x[i]);
            printf("\n\n");
            for ( i=0; i<Nb; i++) printf("%f ",y[i]);
            printf("\n\n\n");

    return 0;
}

/*
   This computes an in-place complex-to-complex FFT
   real and imag are the real and imaginary arrays
   dir =  1 gives forward transform
   dir = -1 gives reverse transform
*/
void FFT(short int dir,float *real,float *imag)
{
   long size,binsize,i,i1,j,k,i2,l,l1,l2;
   float c1,c2,temp_real,temp_imag,t1,t2,u1,u2,z;

   /* Calculate the number of points */
    size= Nb ; //length(real); // On résupère la taille du tableau de réels

    i=0;
    do // Récupération de la taille du tableau en 2^binsize
    {
        size /= 2;
        i++;
    }
    while(size>=2);

    binsize = i;
    size= Nb ;

   /* Do the bit reversal */
   i2 = size >> 1;

   j = 0;
   for (i=0;i<(size-1);i++) {
      if (i < j) {
         temp_real = real[i];
         temp_imag = imag[i];
         real[i] = real[j];
         imag[i] = imag[j];
         real[j] = temp_real;
         imag[j] = temp_imag;
      }

      k = i2;
      while (k <= j) {
         j -= k;
         k >>= 1;
      }
      j += k;
   }

   /* Compute the FFT */
   c1 = -1.0;
   c2 = 0.0;
   l2 = 1;
   for (l=0;l< binsize ;l++) {
      l1 = l2;
      l2 <<= 1;
      u1 = 1.0;
      u2 = 0.0;
      for (j=0;j<l1;j++) {
         for (i=j;i<size;i+=l2)
		 {
            i1 = i + l1;
            t1 = u1 * real[i1] - u2 * imag[i1];
            t2 = u1 * imag[i1] + u2 * real[i1];
            real[i1] = real[i] - t1;
            imag[i1] = imag[i] - t2;
            real[i] += t1;
            imag[i] += t2;
         }
         z =  u1 * c1 - u2 * c2;
         u2 = u1 * c2 + u2 * c1;
         u1 = z;
      }
      c2 = sqrt((1.0 - c1) / 2.0);
      if (dir == 1)
         c2 = -c2;
      c1 = sqrt((1.0 + c1) / 2.0);
   }



   /* Scaling for forward transform */
   if (dir == 1) {
      for (i=0;i<size;i++)
	  {
         real[i] /= size;
         imag[i] /= size;
      }
   }
}



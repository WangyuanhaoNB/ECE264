#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L

double simpson_numerical_integration(Integrand intg_arg) {
   double integral = 0.0;

   double upp = intg_arg.upper_limit;
   double low = intg_arg.lower_limit;
   double n = (upp-low)/(intg_arg.n_intervals);
   double up;
   double lw;
   int i;

   for (i = 0; i < intg_arg.n_intervals; i++)
   {
		up =  ( 1 + i ) * n + intg_arg.lower_limit;
		lw = (i * n) + intg_arg.lower_limit;
		integral += (n / 6) * (intg_arg.integration_func(lw) + (4 * intg_arg.integration_func((lw + up) / 2)) + intg_arg.integration_func(up));
   }
   if (intg_arg.upper_limit == intg_arg.lower_limit)
   {
		integral = 0;
   }
   return integral;
}

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, 
                                                 double (*cos_sin)(double)) {
   double integral = 0.0;
   double upp = intg_arg.upper_limit;
   double low = intg_arg.lower_limit;
   double nt = (upp - low) / (intg_arg.n_intervals);  // Width of the intervals
   double up = 0.0;  // upper limit in intervals
   double lw = 0.0;  // lower limit in intervals
   double L = (upp - low) / 2;
   double m = (n * M_PI) / L; 
   int i;

   for (i = 0; i < intg_arg.n_intervals; i++)
   {
        up = (i + 1) * nt + low;
   		lw = (i * nt) + low;
		integral += (nt / 6) * (intg_arg.integration_func(lw) * cos_sin(m * lw) + 4 * intg_arg.integration_func((lw + up) / 2) * cos_sin(m * (lw + up) / 2) + intg_arg.integration_func(up) * cos_sin(m * up));
   }
   return integral;
}

void fourier_coefficients(Fourier fourier_arg) {
   double upp = fourier_arg.intg.upper_limit;
   double low = fourier_arg.intg.lower_limit;
   double L = (upp - low) / 2;
   for (int i = 0; i < fourier_arg.n_terms; i++) {
      fourier_arg.a_i[i] = 0.0;
      fourier_arg.b_i[i] = 0.0;
	  if ( i == 0 )
	  {
	  	fourier_arg.a_i[i] = simpson_numerical_integration(fourier_arg.intg) / L;
	  	fourier_arg.b_i[i] = 0;
	  }
	  else 
	  {
	  	fourier_arg.a_i[i] = simpson_numerical_integration_for_fourier(fourier_arg.intg,i,cos) *(1/ L);
		fourier_arg.b_i[i] = simpson_numerical_integration_for_fourier(fourier_arg.intg,i,sin) * (1 / L);
	    
		 

   }
}
}

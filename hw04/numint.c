// do not change this part, if you do, your code may not compile
//
/* test for structure defined by student */
#ifndef NTEST_STRUCT 
#include "numint.h"
#else 
#include "numint_key.h"
#endif /* NTEST_STRUCT */
//
// do not change above this line, if you do, your code may not compile
// This is the only file you have to include 

double simpson_numerical_integration(Integrand intg_arg)
{
   double integral = 0.0;
   double upp = intg_arg.upper_limit;
   double low = intg_arg.lower_limit;
   double n = (upp-low)/(intg_arg.n_intervals);
   double i;
   double low2;


   for (i = 0; i < intg_arg.n_intervals; i++)
   {
   low2 =  ( 1 + i ) * n + intg_arg.lower_limit;
   low = (i * n) + intg_arg.lower_limit;
   integral += (n / 6) * (intg_arg.func_to_be_integrated(low) + (4 * intg_arg.func_to_be_integrated((low2 + low) / 2)) + intg_arg.func_to_be_integrated(low2));
   
   }

   return integral;
}

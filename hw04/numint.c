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
  double integral = 0.0, width, a_point = intg_arg.lower_limit;
  width = (intg_arg.upper_limit - intg_arg.lower_limit) / intg_arg.n_intervals;
   //calculate the integral
  for (int i = 0;i < intg_arg.n_intervals - 1;i++) {
    //I'm sorry but I have to use these long equations to keep the percision for my result
    integral += (width / 6) * (intg_arg.function_to_be_integrated(a_point) + 4.0 * intg_arg.function_to_be_integrated(a_point + width / 2) + intg_arg.function_to_be_integrated(a_point + width));
    a_point = intg_arg.lower_limit + (i + 1) * width;
  }
  integral += (width / 6) * (intg_arg.function_to_be_integrated(intg_arg.upper_limit - width) + 4.0 * intg_arg.function_to_be_integrated(intg_arg.upper_limit - width / 2) + intg_arg.function_to_be_integrated(intg_arg.upper_limit));
  return integral;
}

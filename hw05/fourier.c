#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L

double simpson_numerical_integration(Integrand intg_arg) {
   double integral = 0.0;
   int i = 0;//loop control
   double a = intg_arg.lower_limit;
   double l = (intg_arg.upper_limit - intg_arg.lower_limit) / intg_arg.n_intervals;//width of intervals
   //calculate integral by simpson
   while (i < intg_arg.n_intervals) {
      integral += (l / 6) * (intg_arg.function_to_be_integrated(a) + 4 * intg_arg.function_to_be_integrated(a + l / 2) +intg_arg.function_to_be_integrated(a + l));
	  a = intg_arg.lower_limit + (i + 1) * l;
	  i++;
   }
   integral += (l / 6) * (intg_arg.function_to_be_integrated(intg_arg.upper_limit - l) + 4 * intg_arg.function_to_be_integrated(intg_arg.upper_limit - l / 2) + intg_arg.function_to_be_integrated(intg_arg.upper_limit));
   return integral;
}

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, double (*cos_sin)(double)) {
   double integral = 0.0;
   int i = 0;
   double a = intg_arg.lower_limit;
   double l = (intg_arg.upper_limit - intg_arg.lower_limit) / intg_arg.n_intervals;
   double L = (intg_arg.upper_limit - intg_arg.lower_limit) / 2;//period
   //calculate the integral by fourier
   while (i < intg_arg.n_intervals) {
      integral += (l / 6) * (intg_arg.function_to_be_integrated(a) * cos_sin((n * M_PI * a) / L) + 4 * intg_arg.function_to_be_integrated(a + l / 2) * cos_sin(((a + l / 2) * n * M_PI) / L) + intg_arg.function_to_be_integrated(a + l) * cos_sin(((a + l) * n * M_PI) / L));
	  a = intg_arg.lower_limit + (i + 1) * l;
	  i++;
   }
   integral += (l / 6) * (intg_arg.function_to_be_integrated(intg_arg.upper_limit - l) * cos_sin(((intg_arg.upper_limit - l) * n * M_PI ) / L) + 4 * intg_arg.function_to_be_integrated(intg_arg.upper_limit - l / 2) * cos_sin(((intg_arg.upper_limit - l / 2) * n * M_PI) / L)+ intg_arg.function_to_be_integrated(intg_arg.upper_limit) * cos_sin((intg_arg.upper_limit * n * M_PI) / L));
   return integral;
}

void fourier_coefficients(Fourier fourier_arg) {
   double l = (fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit) / 2;//period
   fourier_arg.a_i[0] = (1 / l) * (simpson_numerical_integration(fourier_arg.intg));//a0
   //find ai and bi
   for (int i = 1; i < fourier_arg.n_terms; i++) {
     fourier_arg.a_i[i] = (1 / l) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, cos);
     fourier_arg.b_i[i] = (1 / l) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, sin);
   }

}

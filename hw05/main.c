#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
#include "util.h"
#include "fourier.h"
#include <string.h>

int main(int argc, char ** argv) {
    //check parameters
    if (argc != 6) {
      	return EXIT_FAILURE;
    }
    else {
      //initialize
    Integrand integrand = {
	   .upper_limit = atof(argv[3]),  
	   .lower_limit = atof(argv[2]), 
	   .n_intervals = atoi(argv[4]),    	   
      };
    //check n_terms
    int n_terms = atoi(argv[5]);         
    if (n_terms < 1){
	   n_terms = 1;
    }
    //check boundarys   
    if (integrand.upper_limit == integrand.lower_limit){
	   return EXIT_FAILURE;
    }  
    //check n_intervals
    if (integrand.n_intervals < 1){
	   integrand.n_intervals = 1;
    }
    //decide which function to calculate
    if (strcmp(argv[1],"1") == 0) {
	   integrand.function_to_be_integrated = unknown_function_1;
    }
    else if (strcmp(argv[1],"2") == 0) {
	   integrand.function_to_be_integrated = unknown_function_2;
    }
    else if (strcmp(argv[1],"3") == 0) {
	   integrand.function_to_be_integrated = unknown_function_3;
    }
    else{
	   return EXIT_FAILURE;
    }	  
    Fourier fourier = {
	   .intg      = integrand,
	   .n_terms   = n_terms,
	   .a_i       = malloc(sizeof(*fourier.a_i) * n_terms),
	   .b_i       = malloc(sizeof(*fourier.b_i) * n_terms)
    };
    // If allocation of fourier.a_i and/or fourier.b_i failed, then free the
    // one that didn't fail and then exit with EXIT_FAILURE.
    if (fourier.a_i == NULL || fourier.b_i == NULL) {
       free(fourier.a_i);  // free(..) has not effect if its argument is NULL
       free(fourier.b_i);
       return EXIT_FAILURE;
    }

    fourier_coefficients(fourier);
 
    print_fourier_coefficients(fourier.a_i, fourier.b_i, 
                               fourier.n_terms);
    
    free(fourier.a_i);
    free(fourier.b_i);

    return EXIT_SUCCESS;
   }
} 


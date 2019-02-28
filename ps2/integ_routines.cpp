//  file: integ_routines.cpp
//
//  These are routines for trapezoid, Simpson and Gauss rules               
//                                                                     
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      04-Jan-2004  original version, for 780.20 Computational Physics
//      08-Jan-2005  function to be integrated now passed, changed names
//      09-Jan-2011  new names and rearranged; fixed old bug
//	27-Feb-2019  changed floats to doubles; added milne integration routine (Programmer: Alex Carls)
//
//  Notes:
//   * define with doubles to emphasize round-off error  
//   * compile with:  "g++ -Wall -c integ_routines.cpp" or makefile
//   * adapted from: "Projects in Computational Physics" by Landau and Paez
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau  
//   * equation for interval h = (b-a)/(N-1) with x_min=a and x_max=b
/*

     Analysis of plot in integ_test.ps:
	There seems to be some issue with the Simpson's routine. The slope seems to be the same as the 
	slope for Milne's rule. This isn't consistent with the slope of -4 we got in session 3. The 
	slope I got for the Milne method was ~-6. I did some research on the Newton-Cotes formulas for 
	numerical integration (https://en.wikipedia.org/wiki/Newton%E2%80%93Cotes_formulas and also see 
	Hjorth-Jensen notes, CH. 5) and found the expected errors for this routine (called Boole's rule
	on the Wiki page). The expected error is:
				ϵ_approx = h^7*(8/945)*f^(6)(0)
	Since h = (b-a)/N and global error is approximately local error time the number of iterations, N,
	the global error should scale like h^(-6), which is what our graph tells us.

	The optimum value for N would be when ϵ_approx = ϵ_machine which is approximately 10^(-16). By
	calculating the sixth derivative using wolfram alpha and plugging everything in, I found an
	optimum value of N = 315 = 10^(2.498). This should correspond to a minimum on the relative error
	plot. The plot gives a minimum at log10(N) = 2.626 = log10(423). So my theoretical estimation
	isn't quite the same but it seems reasonable.

*/
// 
//************************************************************************

// include files
#include <cmath>
#include "integ_routines.h"   // integration routine prototypes 

#include <gsl/gsl_integration.h>

//************************************************************************

// Integration using Simpson's rule
double simpsons_rule ( int num_pts, double x_min, double x_max, 
                      double (*integrand) (double x) )
{  
   double interval = ((x_max - x_min)/double(num_pts - 1));  // called h in notes
   double sum=  0.;  // initialize integration sum to zero		 
   
   for (int n=2; n<num_pts; n+=2)                // loop for odd points  
   {
     double x = x_min + interval * double(n-1);
     sum += (4./3.)*interval * integrand(x);
   }
   for (int n=3; n<num_pts; n+=2)                // loop for even points  
   {
     double x = x_min + interval * double(n-1);
     sum += (2./3.)*interval * integrand(x);
   }   
   // add in the endpoint contributions   
   sum +=  (interval/3.) * (integrand(x_min) + integrand(x_max));	
   
   return (sum);
}    

//************************************************************************

// Integration using Milne's rule
double milnes_rule ( int num_pts, double x_min, double x_max, 
                      double (*integrand) (double x) )
{  
   double interval = ((x_max - x_min)/double(num_pts - 1));  // called h in notes
   double sum=  0.;  // initialize integration sum to zero		 
   
   for (int n=2; n<num_pts; n+=2)                // loop for odd points  
   {
     double x = x_min + interval * double(n-1);
     sum += (64./45.)*interval * integrand(x);
   }
   for (int n=3; n<num_pts; n+=4)                // loop for even points  
   {
     double x = x_min + interval * double(n-1);
     sum += (24./45.)*interval * integrand(x);
   }
   for (int n=5; n<num_pts; n+=4)                // loop for even points  
   {
     double x = x_min + interval * double(n-1);
     sum += (28./45.)*interval * integrand(x);
   }   
   // add in the endpoint contributions   
   sum +=  (14.*interval/45.) * (integrand(x_min) + integrand(x_max));	
   
   return (sum);
}

//************************************************************************

// Integration using GSL routine
double gsl_integ ( double x_min, double x_max, double alpha,
                      double (*integrand) (double x, void *params) )
{
   gsl_integration_workspace *work_ptr
      = gsl_integration_workspace_alloc (1000);

   double lower_limit = x_min;  /* lower limit a */
   double upper_limit = x_max;  /* upper limit b */
   double abs_error = 1.0e-8;	/* to avoid round-off problems */
   double rel_error = 1.0e-8;	/* the result will usually be much better */
   double result;		/* the result from the integration */
   double error;		/* the estimated error from the integration */

   gsl_function My_function;
   void *params_ptr = &alpha;

   My_function.function = integrand;
   My_function.params = params_ptr;

   gsl_integration_qags (&My_function, lower_limit, upper_limit,
			 abs_error, rel_error, 1000, work_ptr, &result,
			 &error);

   return result;
}









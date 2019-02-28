//  file: integ_test.cpp
//
//  This is a test program for basic integration methods.               
//                                                                     
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      04-Jan-2004  original version, for 780.20 Computational Physics
//      08-Jan-2005  changed functions to pass integrand
//      09-Jan-2011  updated functions
//
//  Notes:
//   * define with floats to emphasize round-off error  
//   * compile with:  "g++ -Wall -c integ_test.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez  
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau                           
// 
//************************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

#include "integ_routines.h"	// prototypes for integration routines

double my_integrand (double x);
double my_gsl_integrand (double x, void *params);

const double PI = 3.1415926535897932384626;	// Pi to high precision 

//************************************************************************

int
main ()
{
  // set up the integration specifiction
  const int max_intervals = 2001;	// maximum number of intervals
  const double lower = 0.0;	// lower limit of integration
  const double upper = 1.0;	// upper limit of integration
  double alpha = 1.0;

  const double answer = (22./7.) - PI;	// the "exact" answer for the test 
  double result = 0.;  // approximate answer

  result = gsl_integ (lower, upper, alpha, &my_gsl_integrand);

  // open the output file stream
  ofstream integ_out ("integ.dat");	// save data in integ.dat

  int width = 20;  // setw width for output
  integ_out << "# Integrating ((x-x^2)^4)/(1+x^2) dx from 0 to 1" << endl;
  integ_out << "# exact result              = " << setw(width) << setprecision(16) << answer << endl;
  integ_out << "#" << endl;
  integ_out << "# result from gsl routine   = " << setw(width) << setprecision(16) << result << endl;
  integ_out << "# error of gsl routine      = " << setw(width) << setprecision(16) << result - answer << endl;
  integ_out << "#" << endl;
  integ_out << "# Errors in integration routines for each number of intervals (in log10)" << endl;
  integ_out << "#         N                    Simpsons                  Milnes  " << endl;
  integ_out << "#-----------------------------------------------------------------------" << endl;

  // Simpson's rule requires an odd number of intervals so start at 3 and increase by even intervals
  // Milne's rule requires number of form 4i+1 so start at 3 and increase by intervals of 4
  for (int i = 3; i <= max_intervals; i += 4)
  {
    integ_out << setw(4) << log10 (i);

    result = simpsons_rule (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << setprecision(16) << log10 (fabs (result - answer) / answer);

    result = milnes_rule (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << setprecision(16) << log10 (fabs (result - answer) / answer);

    integ_out << endl;
  }

  cout << "data stored in integ.dat\n";
  integ_out.close ();

  return (0);
}

//************************************************************************

/*
   The function I am integrating is the following:
	((x-x^2)^4)/(1+x^2)
   When integrated from 0 to 1, it gives an interesting result
   of exactl (22/7)-pi (approx. = 0.00126448926734962)
*/

// the function we want to integrate 
double
my_integrand (double x)
{
  return (pow(x-x*x,4)/(1+x*x));
}

// function for use with gsl integration routine
double
my_gsl_integrand (double x, void *params)
{
  // Mathematica form:  Log[alpha*x]/Sqrt[x]

  // The next line recovers alpha from the passed params pointer
  double alpha = *(double *) params;

  return ( alpha * pow (x - x*x, 4) / (1 + x*x) );
}


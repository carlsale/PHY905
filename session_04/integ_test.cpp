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

float my_integrand (float x);

const double ME = 2.7182818284590452354E0;	// Euler's number 

//************************************************************************

int
main ()
{
  // set up the integration specifiction
  const int max_intervals = 100001;	// maximum number of intervals
  const float lower = 0.0;	// lower limit of integration
  const float upper = 2.0;	// upper limit of integration

  const double answer = 2.*atan(sqrt(2.));	// the "exact" answer for the test 
  float result_brute = 0.;  // approximate answer by brute force
  float result_sub_sing = 0.;  // approximate answer by brute force

  // open the output file stream
  ofstream integ_out ("integ.dat");	// save data in integ.dat
  integ_out << "#  N   Brute     No Sing." << endl;
  integ_out << "#-----------------------------------------" << endl;

  // Simpson's rule requires an odd number of intervals  
  for (int i = 3; i <= max_intervals; i += 2)
  {
    integ_out << setw(4) << log10(i);

    result_brute = simpsons_rule (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs (result_brute - answer)/answer);

    float skip = ((upper - lower)/float(i - 1));
    result_sub_sing = simpsons_rule (i - 2, lower + skip, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs (result_sub_sing - answer)/answer);

    integ_out << endl;
  }

  cout << "data stored in integ.dat\n";
  integ_out.close ();

  return (0);
}

//************************************************************************

// the function we want to integrate 
float
my_integrand (float x)
{
  return (1./((x+1.)*sqrt(x)));
}

//  file: gsl_spline_test_class.cpp
// 
//  Test program for the gsl spline routines using the Spline class
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/10/09 -- created from gsl_cubic_spline_test.cpp
//
//  Notes:
//   * uses the GSL interpolation functions (see online documentation) 
//
//*****************************************************************
// include files
#include <iostream>    // cout and cin
#include <iomanip>     // manipulators like setprecision
#include <cmath>
#include <string>     // C++ strings      
#include <fstream>                           
using namespace std;    
#include "GslSpline.h"  // Header file for the GSL Spline class

inline double sqr (double z) {return z*z;}  // inline function for z^2

int
main (void)
{
  const int npts = 9;   // maximum number of array points 

  // Test: interpolate scattering cross-section data for a range of energies
  double energy[npts] = {0., 25., 50., 75., 100., 125., 150., 175., 200.};
  double sigmaExp[npts] = {10.3, 16.0, 45.0, 85.5, 52.8, 19.9, 10.8, 8.25, 4.7};

  // Make the cubic spline object
  string type = "cubic";
  Spline my_cubic_spline (energy, sigmaExp, npts, type);
  // Make the linear spline object
  type = "linear";
  Spline my_line_spline (energy, sigmaExp, npts, type);
  // Make the polynomial spline object
  type = "poly";
  Spline my_poly_spline (energy, sigmaExp, npts, type);

  ofstream my_file;
  my_file.open("gsl_spline_test_class.dat");
  my_file << "    E  sigma:   exact   cubic_spline   line_spline   poly_spline" << endl;

  for(double x = 0.; x <= 201.; x += 5.){
  // Evaluate the spline
    double y_cubic = my_cubic_spline.y (x);
    double y_line = my_line_spline.y (x);
    double y_poly = my_poly_spline.y (x);

    double sigmaExact = 63900./(sqr(x-78.0)+sqr(55.0)/4.);

    my_file << fixed << setprecision(12) 
            << x << "  " << sigmaExact << "  " << y_cubic << "  " << y_line << "  " << y_poly << endl;
  }

  return (0);      // successful completion 
}

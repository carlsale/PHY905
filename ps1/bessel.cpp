
//  file: bessel_final.cpp 
//
//  Spherical Bessel functions via up and down recursion      
//                                                                     
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2011  new version, for 780.20 Computational Physics
//
//  Notes:  
//   * compile with:  "g++ -o bessel bessel.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez  
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau  
//   * added relative error calculation and output to bessel.cpp
//   * data saved as: x y1 y2 rel_error log10(x) log10(rel_error) 
//  
/*
      Interpretation of bessel.ps (Problem 3, part b):
	
	In order to help me understand the features of bessel.ps, I plotted the actual results of the recursion methods for j_l(x) versus x in bessel_function.ps. There are 4 main regions in bessel.ps with different features. 

	In the first region corresponding to 0 < x < ~3, we see a consistent relative error of essentially 1 (corresponding to log10(error) = 0 on the graph). This seems reasonable because the bessel function is pretty much zero for these x values. This means we are calculating numbers near the machine precision so error is quite large.

	In the second region corresponding to ~3 < x < ~10, we see a quick drop in the error (slope = -17.5). This is because the values for the bessel function for these x values become non-zero and the two methods have similar precision in this region.

	In the third region corresponding to ~10 < x < ~30, we see fairly consistent error with a 10^-16 relative error. This is where the actual relative error becomes smaller than the machine precision. So no matter how close the two methods get for these x values, the machine cannot distinguish them with more precision than this error. We can assume that the two methods have very similar precision here.

	In the fourth region corresponding to x > ~30, the error sharply rises (slope = 74.1!) until it reaches the max at rel. error = ~1. This is consistent with what we see in the bessel_function.ps plot. For large values of x, the downward recursion method becomes much more erratic and leaves the trend that we see set by the gsl function. Therefore the relative error becomes quite large.
*/
//************************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>

using namespace std;		// we need this when .h is omitted

#include <gsl/gsl_sf_bessel.h>	// gsl Bessel special function header file

// function prototypes 
double down_recursion (double x, int n, int m);	// downward algorithm 
double up_recursion (double x, int n);	// upward algorithm 

// global constants  
const double xmax = 100.0;	// max of x  
const double xmin = 0.1;	// min of x >0  
const double step = 0.1;	// delta x  
const int order = 10;		// order of Bessel function 
const int start = 50;		// used for downward algorithm 

//********************************************************************
int
main (void)
{
  double ans_down, ans_up;
  double rel_error, log_rel_error;
  double y, y_err;

  // open an output file stream
  ofstream my_out ("bessel.dat");

  my_out << "# Spherical Bessel functions via up and down recursion,"
    << " l = " << order << endl;

  my_out << "#   x       jdown(x)      jup(x)       rel. error     ";
  my_out << "log10(x)  log10(rel.err.)     gsl       gsl_error" << endl;


  // step through different x values
  for (double x = xmin; x <= xmax; x += step)
    {
      ans_down = down_recursion (x, order, start);
      ans_up = up_recursion (x, order);
      y = gsl_sf_bessel_jl (order, x); // This is to satisfy Problem 3, part c

      // we calculate the absolute value of the relative error
      rel_error =
	fabs (ans_down - ans_up) / (fabs (ans_down) + fabs (ans_up));
      if (rel_error > 1.e-20)
	{
	  log_rel_error = log10 (rel_error);
	}
      else
	{
	  log_rel_error = -20.;
	}

      y_err = log10 (fabs (ans_down - y) / (fabs (ans_down) + fabs (y)));
      if (isinf (y_err))
	{
	  y_err = -20.;
	}

      my_out << fixed << setprecision (6) << setw (8) << x << " "
	<< scientific << setprecision (6)
	<< setw (13) << ans_down << " "
	<< setw (13) << ans_up << " "
	<< setw (13) << rel_error << " "
	<< setw (13) << log10 (x) << " "
	<< setw (13) << log_rel_error << " "
	<< setw (13) << y << " " 
        << setw (13) << y_err << endl;
    }
  cout << "data stored in bessel.dat." << endl;

  // close the output file
  my_out.close ();
  return (0);
}


//------------------------end of main program----------------------- 

// function using downward recursion  
double
down_recursion (double x, int n, int m)
{
  double j[start + 2];		// array to store Bessel functions 
  j[m + 1] = j[m] = 1.;		// start with "something" (choose 1 here) 
  for (int k = m; k > 0; k--)
    {
      j[k - 1] = ((2. * (double) k + 1.) / x) * j[k] - j[k + 1];	// recur. rel.
    }
  double scale = ((sin (x)) / x) / j[0];	// scale the result 
  return (j[n] * scale);
}


//------------------------------------------------------------------ 

// function using upward recursion  
double
up_recursion (double x, int n)
{
  double term_three = 0.;
  double term_one = (sin (x)) / x;	// start with lowest order 
  double term_two = (sin (x) - x * cos (x)) / (x * x);	// next order
  for (int k = 1; k < n; k += 1)	// loop for order of function     
    {				// recurrence relation
      term_three = ((2. * double (k) + 1.) /x) * term_two - term_one;
      term_one = term_two;
      term_two = term_three;
    }
  return (term_three);
}

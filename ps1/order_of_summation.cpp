//************************************************************************ 
//  file: order_of_summation1.cpp
// 
//  Program to demonstrate that the order of summation of even positive
//   numbers matters
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      01/02/11  new version from demo1.cpp
//
//  Notes:
//   * An example to try to understand summing upward vs. summing
//      downward.  Add a small number eps (slightly below single-precision
//      machine precision) many times to 1.  It makes a big difference
//      (in single precision) whether you do 1 + eps + eps + ... or
//      eps + eps + ... + 1.
//
//
//   * First pass: no subroutine
//   * Use single precision AND double precision at the same time
//   * Here is the output with eps=5e-8 added 10^7 time:
//
//                           1+eps+eps+...   eps+eps+...+1
//        single precision:  1.0000000000    1.5323836803
//        double precision:  1.4999999992    1.4999999999
//
/*
      Interpretation of order_of_summation.ps (Problem 2, part c):

	If we look back at the order of summation test from Activity 2, we added a small number eps N times to 1.  Taking 1 and then adding eps caused a problem when eps was on the order of the machine precision because the machine would just consider 1 + eps = 1 within error. Adding the N eps first did not give this problem as long as N*eps < 1.

	In pretty much the same way, the upward sum in this program will be much less accurate because we are adding increasingly small numbers to 1. Eventually the machine will not be able to distinguish the next 1/n from the current sum. The downward sum fixes this problem as it did before. Therefore, it is generally more precise.

	For very low N, I believe that the upward sum will be close in precision to the downward sum since we aren't adding numbers that are on the order of the machine precision. As N gets quite large though, the relative error will increase you begin to add very small numbers and the upward sum becomes less precise. We begin to see this in the N > ~10^4 region. For these large N, we see the error scale as N^2. This was determined by fitting the error and finding a slope of 1.9 which gives the power since we plotted in log-log.

*/
//*************************************************************************


// include files
#include <iostream>		// this is needed for cout
#include <iomanip>		// this allows manipulation of output (precision, notation, etc...)
#include <fstream>		// this allows input/output to files
#include <cmath>		// this allows log10() and abs()
using namespace std;		// we need this when .h is omitted

//********************** begin main ******************************

int
main ()
{
  int nMax = 100000;

  ofstream myFile;
  myFile.open ("order_of_summation.dat");

  myFile << "#log10(N)      log10(error)   sum_up         sum_down" << endl;

  for (int n = 1; n <= nMax; n++)
    {
      float sum_up = 0.;	// starts at n = 1 and sums progressively larger numbers 
      float sum_down = 0.;	// starts at n = N and sums progressively smaller numbers 
      float error;

      // add small numbers (in single or double precision) num_eps times
      for (int i = 1; i <= n; i++)
	{
	  sum_up += 1. / i;
	  sum_down += 1. / (n - i + 1);
	}

      error =
	abs (sum_up - sum_down) / ((abs (sum_up) + abs (sum_down)) / 2.);
      if (!isinf (log10 (error)))
	{
	  myFile << scientific << setprecision (8) << log10 (n) << "  "
	    << log10 (error) << " " << sum_up << "  " << sum_down << endl;
	}
    }

  myFile.close ();

  return (0);
}

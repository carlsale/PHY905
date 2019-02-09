//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2010  updates to "To do" wishlist
//      12-Jan-2016  comment out "using namespace std;"
//      06-Feb-2019  completed To do (1-7)
//
//  Notes:  
//   * compile with:  "g++ -o area.x area.cpp"
//
//  To do:
//   1. output the answer with higher precision (more digits)   - done
//   2. use a "predefined" value of pi or generate it with atan - done
//   3. define an inline square function                        - done
//   4. split the calculation off into a function (subroutine)  - done
//   5. output to a file (and/or input from a file)             - done
//   6. add checks of the input (e.g., for non-positive radii)  - done
//   7. rewrite using a Circle class                            - done
//
//  *Edited*
//    Programmer: Alex Carls
//    Date: 02/06/2019
//    New File Name: area_new.cpp
//
//*********************************************************************// 

// include files
#include <iostream>		// this has the cout, cin definitions
#include <cmath>		// this has predefined pi value
#include <iomanip>		// this allows manipulation of outputs (precision, scientific, etc...)
#include <fstream>		// this allows output/input to files
using namespace std;		// if omitted, then need std::cout, std::cin 

//*********************************************************************//

const double pi = M_PI;		// define pi as a constant 

inline double
square (double x)
{
  return x * x;			// here we have an inline function to calculate the square of the variable x
}

class Circle
{
public:

  double r;

  double area ();
};

int
main ()
{
  Circle myCircle;
  bool invalid = false;
  int input;
  string output;

  cout << endl << "How do you want to input the radius?" << endl << endl
    << "1) Read from file" << endl
    << "2) Enter manually" << endl << endl << "Enter 1 or 2: ";
  cin >> input;
  if (input == 1)
    {
      string filename;
      ifstream inputfile;
      cout << endl << "Please input the name of the file: ";
      cin >> filename;
      inputfile.open (filename);
      if (inputfile.fail ())
	{
	  cout << endl <<
	    "Error opening file. Please enter radius manually..." << endl;
	  input = 2;
	}
      else
	{
	  cout << endl << "Opening " << filename <<
	    " and reading first entry as radius." << endl;
	}
      inputfile >> myCircle.r;
      inputfile.close ();
    }
  if (input == 2 || input != 1)	// just make them input a radius if they input an invalid choice
    {
      if (input != 2)
	{
	  cout << endl << "You only had two options..." << endl;
	}
      cout << endl << "Enter the radius of your circle: ";	// ask for radius
      cin >> myCircle.r;
    }

  if (myCircle.r < 0)
    {
      invalid = true;		// check the input for non-positive 
    }
  while (invalid)
    {
      cout << "Please input a valid (positive) value for the radius: ";
      cin >> myCircle.r;
      if (myCircle.r > 0)
	{
	  invalid = false;	// only let the program continue if they give a positive value
	}
    }

  cout << endl <<
    "Do you want to output the results to a file? Enter (y/n): ";
  cin >> output;

  if (output == "y" || output == "Y" || output == "yes" || output == "Yes")
    {
      ofstream outputfile;
      outputfile.open ("area_results.dat");
      outputfile << "#Radius          Area" << endl;
      outputfile << fixed << setw (16) << left << myCircle.r << " " <<
	setprecision (16) << myCircle.area () << endl;
      cout << endl << "Outputing to file area_results.dat" << endl;
      outputfile.close ();
    }

  cout << endl << setprecision (16) << "Radius = " << myCircle.r << ", Area = " << myCircle.area () << endl;	// setprecision(16) causes output of 16 significant figures for higher precision

  return 0;			// "0" for successful completion
}

double
Circle::area ()
{
  return pi * square (r);	// area subroutine returns area using radius r and inline square function
}

//*********************************************************************//

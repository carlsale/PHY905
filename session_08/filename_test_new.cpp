//  file: filename_test.cpp 
//
//  Test program to use C++ strings to make filenames in various ways      
//                                                                     
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      20-Feb-2004  original version, for 780.20 Computational Physics
//      06-Feb-2009  minor upgrades 
//
//  Notes:  
//   * compile with:  "g++ -Wall -o filename_test filename_test.cpp"
//   * note that we include <string> for strings and <sstream> for
//      building string streams
//   * building string stream objects is just like doing output using
//      iostram and iomanip, with <<'s and manipulators
//  
//************************************************************************

// include files
#include <iostream>   // cout and cin                                
#include <iomanip>    // manipulators like setprecision              
#include <fstream>    // file input and output                       
#include <string>     // C++ strings                                 
#include <sstream>    // C++ stringstream class (could omit iostream)  

using namespace std;    

//********************************************************************
int
main (void)
{
  ostringstream my_filename_stream;  // declare a stringstream object
  ofstream my_file;    // now for a filename

  for(int j = 0; j <= 3; j++)
  {
    my_filename_stream.str("");

    // you can load the string from a stream just like output streams
    my_filename_stream << "test_file_num" << j << ".out";

    cout << "Creating output file " << j << " with file name "
         << my_filename_stream.str() << "." << endl;

    my_file.open (my_filename_stream.str().c_str());  // use .c_str() to convert to a char*

    my_file << "This is file " << j << "." << endl;

    my_file.close();    // close the output file
  }

  double alpha;

  cout << "Now please input a double precision number and I will create a file using it: ";
  cin >> alpha;

  my_filename_stream.str("");
  my_filename_stream << "test_file_alpha" << setprecision(3) << alpha << ".out";

  my_file.open (my_filename_stream.str().c_str());

  my_file << "This file was created with double precision parameter alpha = " << alpha << "." << endl;

  my_file.close();

  return (0);
}

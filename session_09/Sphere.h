//  file: Sphere.h
// 
//  Header file for the Sphere C++ class. 
//
//  Programmer:  Alex Carls  carls@nscl.msu.edu
//
//  Revision history:
//      03/15/19  Original version.
//
//*****************************************************************

// The ifndef/define macro ensures that the header is only included once
#ifndef SPHERE_H
#define SPHERE_H

// include files

class Sphere
{ 
  public:
    Sphere (const double rad);  // constructor
    ~Sphere ();  // destructor

    // accessor functions
    double get_radius ();
    void set_radius (const double rad);
    double volume ();

  private:
    double radius;  // the sphere radius
    inline double cube (const double x) {return x*x*x;};  // inline function
};

#endif

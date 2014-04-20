// Designer: Bradley Bare 
//
// Description: This is a class that creates a dynamic grid to your size. All
// dimensions can be changed if the constructor is changed.
//
// Use: Used as a base class from which the LEDs will be controlled.
//

#include "Arduino.h"

#ifndef MatrixD_H
#define MatrixD_H

class DMatrix
{
 protected:
  int width;
  int height;
  int inPins;

 public:
  int*** Matrix;
  //Matrix member variable 
  
  DMatrix(const int x, const int y, const int z) :
          width(x),    height(y),   inPins(z)
  {
    Matrix= new int**[width];
    for(int i=0; i<width; i++)
    {
      Matrix[i]= new int*[height];
      for(int j=0; j<height; j++)
      {
        Matrix[i][j]= new int[inPins];
      };
    };
  };
  //Constructor sets up bool Matrix
};
#endif
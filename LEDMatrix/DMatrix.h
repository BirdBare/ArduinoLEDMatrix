// Designer: Bradley Bare 
//
// Description: This is a class that creates a dynamic grid to your size. All
// dimensions can be changed if the constructor is changed.
//
// Use: Used as a base class from which the LEDs will be controlled.
//

#ifndef MatrixD_H
#define MatrixD_H

#include <Arduino.h>

class DMatrix
{
 protected:
  int width;
  int height;
  int inPins;
  int*** Matrix;
  //Matrix member variable.

 public:
  
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
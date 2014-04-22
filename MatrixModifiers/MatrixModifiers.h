// Designer: Bradley Bare
//
// Description: These functions will be used to modify the Matrix. Each function
// does exactly what the description says and nothing more to increase 
// possibilities of designs.
//
// Use: Call function with parameters and the matrix will be changed accordingly.

#ifndef MatrixModifiers_H
#define MatrixModifiers_H
#include <Arduino.h>

// What: Native math functions to exclude C++ libraries, save space.

// Description: Finds the square root of a float with recursion
//
// Post: returns square root as float
float squareRoot(const float x,const float y=1.0)
{
  if(y*y>=x)
    return y;
  return squareRoot(x,y+0.01);
}

// Description: Finds the slope between two points
//
// Post: returns slope as float
float slope(const Point s, const Point e)
{
  if(s.w==e.w || s.h==e.h)
    return 0.0;
  return (float(e.h)-float(s.h))/(float(e.w)-float(s.w));
}

// Description: Draws a line from Starting point sP to ending Point eP. If line 
// is not horizontal or vertical. It attempts to draw the line by slope 
// comparison.
//
// Pre: sP and eP must be within Matrix boundries.
//
// Post: Line is made from sP to eP. Set to color c and value on.
void Line(LEDs& Matrix, const Point sP, const Point eP, const bool on=1, 
          const Color c=SOLID)
{
  int hInc, wInc;
  float lineSlope=slope(sP,eP);
  
  sP.h<eP.h ? hInc=1:hInc=-1; sP.w<eP.w ? wInc=1:wInc=-1;
  //Sets hInc and wInc to height and width increments on Matrix
  
  for(int h=sP.h; (hInc*h)<=(hInc*eP.h); h+=hInc)
    for(int w=sP.w; (wInc*w)<=(wInc*eP.w); w+=wInc)
      if( (lineSlope==0 && (w==eP.w || h==eP.h)) || (sP.h==h && sP.w==w) ||
           slope(sP,Point(w,h)) == lineSlope ) 
        Matrix.setColor(Point(w,h),on,c);
  //for loop stack with if statement that decides when to turn on based on slope
  
  return;
}

// Description: Makes a solid or hollow rectangle of color c
//
// Pre: Rectangle must be within Matrix boundries.
//
// Post: Rectangle is made. Set to color c and value on, solid or hollow
void Rectangle(LEDs& Matrix, const Point sP, const int width, const int height,
               const bool solid=true, const bool on=1, const Color c=SOLID)
{
  if(width>0 && height>0)
  {
    if(solid)
      for(int h=sP.h; h<(sP.h+height); h++)
        Line(Matrix,Point(sP.w,h),Point((sP.w+width-1),h),on,c);
      //Makes rectangle by using lines
      
    else
    {
      Line(Matrix,Point(sP.w,sP.h),Point(sP.w+width-1,sP.h),on,c);
      Line(Matrix,Point(sP.w,sP.h+height-1),Point(sP.w+width-1,sP.h+height-1),on,c);
      Line(Matrix,Point(sP.w,sP.h),Point(sP.w,sP.h+height-1),on,c);
      Line(Matrix,Point(sP.w+width-1,sP.h),Point(sP.w+width-1,sP.h+height-1),on,c);
    }
    //Makes outline of rectangle
    
  }
  return;
}

// Description: Makes a triangle. Solid or hollow of color c
//
// Pre:

#endif
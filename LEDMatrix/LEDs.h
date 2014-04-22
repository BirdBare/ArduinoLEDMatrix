// Designer: Bradley Bare
//
// Description: This class represents all of the LEDs on the matrix. Each LED is
// controlled by the matrix made by the DMatrix class. Comes with function
// shiftMatrix() that shifts Matrix to all Registers and leaves Matrix unchanged
//
// Use: Origin=(0,0) To use, start at Origin and move Right and Up. Each point
// is an LED that has an On(!0) and Off(0) state.

#ifndef LEDsMatrix_H
#define LEDsMatrix_H

#include "Arduino.h"
#include "DMatrix.h"

// Description: Used in the form Point(x,y), where x>=0 and y>=0, to easily
// define a region on the matrix.
struct Point
{
  int w;
  int h;
  Point(){}
  Point(const int x, const int y) : w(x),h(y) {}
};

// Description: The enum Color is used to differ between colors for now.
enum Color{ SOLID, RED, GREEN, BLUE, YELLOW, PURPLE, CYAN, WHITE };


class LEDs: public DMatrix
{
  #if defined MatrixModifiers_H
    friend class MatrixModifiers;
  #endif

 protected:
  int dataPin;
  int clockPin;
  int latchPin;
  int LEDperReg;
  int* outPins; 
  //which outpins to use on each register, 1=in-use 0=not
  //Reads Least-to-Greatest pins on. 
  //MUST use a multiple of LEDperReg. MUST be same for all registers
  
 public:  
  LEDs(const int x, const int y, const int z,
       const int d, const int c, const int l, const int r, int *p) : 
       DMatrix(x,y,z),
       dataPin(d),  clockPin(c), latchPin(l), LEDperReg(r), outPins(p) {};
  //Constructor
  
  // Description: This functions is used to change color on a RGB common cathode 
  // LED diode. 
  //
  // Pre: If inPins=1 then Color should be SOLID!
  //
  // Post: Color set to on value
  void setColor(const Point p, const bool on=1, const Color c=SOLID)
  {
    int iPlusPlus=1;
    if(c==SOLID)
      iPlusPlus=3;
    //if c==SOLID inpins==1 and only one color should be turned off
    
    for(int i=0; i<3; i+=iPlusPlus)
      Matrix[p.w][p.h][i]=LOW;
    //Pre-turns off LEDs
    
    if(on)
    {
      if(c==SOLID || c==RED || c==YELLOW || c==PURPLE || c==WHITE)
        Matrix[p.w][p.h][0]=on;
      if(c==GREEN || c==YELLOW || c==CYAN || c==WHITE)
        Matrix[p.w][p.h][1]=on;
      if(c==BLUE || c==PURPLE || c==CYAN || c==WHITE)
        Matrix[p.w][p.h][2]=on;
    }
    return;
  }
  
  
  // Description: Shifts the whole Matrix at once. Shifts the matrix to the 
  // Shift Registers controlling LEDs.
  // 
  // Post: Matrix is set and ready to be latched to pins.
  void shiftMatrix()
  {
    byte data=0;
    
    for(int LED=0, outPin=0; LED<width*height; LED++)
    {
      for(int i=0; i<inPins; i++)
      {
        while(outPins[outPin]==0)
          outPin++;
        bitWrite(data,outPin,outPins[outPin] &
                 !!Matrix[width-(LED/height)-1][height-(LED%height)-1][i]);
        outPin++;
        //While loop skips pins that are not in use so they are not printed
        
      };
      //for loop to set colors on pins if they are enabled inPins=3
      
      if((LED+1)%LEDperReg==0)
      {
        shiftOut(dataPin,clockPin,MSBFIRST,data);
        outPin=0;
        data=0;
      }
      //if statement to shiftOut when all pins per register are set
      
    };
    return;
  }
};

#endif
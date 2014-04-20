// Designer: Bradley Bare
//
// Description: This class represents all of the LEDs on the matrix. Each LED is
// controlled by the matrix made by the DMatrix class. Comes with function
// shiftMatrix() that shifts Matrix to all Registers and leaves Matrix unchanged
//
// Use: Origin=(0,0) To use, start at Origin and move Right and Up. Each point
// is an LED that has an On(!0) and Off(0) state.

#include "Arduino.h"
#include "DMatrix.h"

#ifndef LEDsMatrix_H
#define LEDsMatrix_H

class LEDs: public DMatrix
{
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
  
  // Description: Main function of whole Matrix. Shifts the matrix to the 
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
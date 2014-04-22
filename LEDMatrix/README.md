LEDMatrix
Designed by: Bradley Bare
ANYONE CAN USE THIS FOR ANYTHING
=========

Designed for shift register s74hc595n

******************Rough dataPin wiring diagram*****************
| r=Shift Register | d=dataPin | Ds=dataPin Start(1) | De=dataPin End | 
**************************
        5x5 grid
    
    rd4  rd9  rd14 rDe  r
    rd3  rd8  rd13 rd18 r
    rd2  rd7  rd12 rd17 r
    rd1  rd6  rd11 rd16 r
    rDs  rd5  rd10 rd15 r
    
--------------------------
Explanation: The dataPin wiring comes from the Arduino to Origin(Ds) and follows from 
the serial out pin to the next dataPin(d). 

In short the wiring goes from origin(Ds) to max-height(d4) to origin+1(d5) to 
max-height(d9) and so on.

NOTE: The Matrix controls each LED connected to the Register, NOT the Register
**************************END ROUGH DIAGRAM*********************

================================TEMPLATE===================================
#include <LEDs.h>

const int width=0, height=0, inPins=0;
const int dataPin=0, clockPin=0, latchPin=0;
int LEDperReg=0, outPins[]={0,0,0,0,0,0,0,0};

LEDs LED(width,height,inPins,dataPin,clockPin,latchPin,LEDperReg,outPins);

void setup()
{
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  return;
}

void loop()
{
  return;
}

---------------------------------------------------------------------------
Explanation: Anything in the Template initialized as 0 SHOULD be changed
before running code.

width: Width of Matrix
height: Height of Matrix
inPins: The number of Anode connections per LED (1 for Solid LED OR 3 for RGB LED)
dataPin: Desired dataPin
clockPin: Desired clockPin
latchPin: Desired latchPin
LEDperReg: Number of LEDs each register will run
outPins[]: The pins the will have the LED connected (1=Connected OR 0=NotConnected)
==============================END TEMPLATE=================================

//////////////////////Usable Object and Functions///////////////////////////

Object Matrix[width][height][inPin(color)]
  Explanation: Each point in the matrix represents an LED in your real Matrix  Origin(0,0)

Function: setMatrix() USE: object_name.setMatrix();
          setColor(Point,on/off,Color); //Use this to change points(LEDs) in the Matrix
**********Remember to flash latchPin from LOW to HIGH for this function call************

///////////////////////////////////END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

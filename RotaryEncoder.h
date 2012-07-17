/***********************************
Written by Joshua Oster-Morris/craftycoder.  
BSD license, check license.txt for more information
All text above must be included in any redistribution

I strongly urge hardware debouncing with rotary encoders. 
A 10000pF cap between both the A and B pins to GND (the C pin)
is suffcient to offer very consistent reads.

*ENC_A* is the arduino pin the A pin of the encoder is plugged in to.
*ENC_B* is the arduino pin the B pin of the encoder is plugged in to.
*multiplier* is what is sounds like
*stepSize* is used to find the *multiplicand*
*pauseLength* is the maximum amount of time in microseconds a user can pause before the number of steps resets
Equations of interest.
*multiplicand* = (consecutive steps in one direction with less than a *pauseLength* between them)/*stepSize*
*direction* = 1 for clockwise or -1 for counterclockwise
readEncoder() returns *multiplicand*x*multiplier*x*direction*
****************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class RotaryEncoder {
 public:
  RotaryEncoder(int ENC_A, int ENC_B, int multiplier, int stepSize, int pauseLength);
  int readEncoder();
 private:
  int _ENC_A, _ENC_B, _oldENC_A, _oldENC_B, _lastENCread, _ENCcounter, _pauseLength, _multiplier, _stepSize;
  long _lastENCreadTime;
};


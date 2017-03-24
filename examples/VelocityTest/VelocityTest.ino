/***********************************
Written by Joshua Oster-Morris/craftycoder.  
BSD license, check license.txt for more information
All text above must be included in any redistribution

I strongly urge hardware debouncing with rotary encoders. 
A 10000pF cap between both the A and B pins to GND (the C or middle pin)
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

#include <RotaryEncoder.h>;
int val = 0;
RotaryEncoder encoder(A0,A2,5,6,3000);
void setup()
{  
  Serial.begin(57600);
}
void loop()
{
  int enc = encoder.readEncoder();
  if(enc != 0) {
    val = val + (enc);
    val = min(val,4095);
    val = max(val,0);
    Serial.println(val);
  } 
  delayMicroseconds(5);
}


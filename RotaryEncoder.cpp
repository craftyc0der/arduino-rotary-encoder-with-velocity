#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int ENC_A, int ENC_B, int multiplier, int stepSize, int pauseLength) {
  _ENC_A = ENC_A;
  _ENC_B = ENC_B;
  _multiplier = multiplier;
  _stepSize = stepSize;
  _pauseLength = pauseLength;
  _oldENC_A = 0;
  _oldENC_B = 0;
  _lastENCread = 0;
  _ENCcounter = 0;
  _lastENCreadTime = micros();  
  //define pin modes
  pinMode(_ENC_A, INPUT);
  pinMode(_ENC_B, INPUT);
  digitalWrite(_ENC_A,HIGH); //these pins do not have pull up resistors on an attiny...
  digitalWrite(_ENC_B,HIGH); //you must pull them up on the board.
}
int RotaryEncoder::readEncoder() {
  int a0Pin = digitalRead(_ENC_A);
  int a1Pin = digitalRead(_ENC_B);
  int changevalue = 1;
  int returnVal = 0;
  if(a0Pin != _oldENC_A || a1Pin != _oldENC_B) {
    if(_oldENC_A == a1Pin && _oldENC_B != a0Pin) {
      returnVal = -1;
    } else if (_oldENC_B == a0Pin && _oldENC_A != a1Pin) {
      returnVal = 1;
    }
    _oldENC_A = a0Pin;
    _oldENC_B = a1Pin;
    
    if(returnVal != 0) {
      if(returnVal == _lastENCread) {
          _ENCcounter++;
          if((micros() - _lastENCreadTime) < _pauseLength) {
            changevalue = max((_ENCcounter/_stepSize)*_multiplier,1);
          }
          _lastENCreadTime = micros();
        } else {
          _ENCcounter=0;
      }
      _lastENCread = returnVal;
    }
    
    return returnVal*changevalue;
  } else {
    return 0;
  }
}

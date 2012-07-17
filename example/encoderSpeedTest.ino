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
  int changevalue = 1;
  if(enc != 0) {
    val = val + (enc);
    val = min(val,4095);
    val = max(val,0);
    Serial.println(val);
  } 
  delayMicroseconds(5);
}


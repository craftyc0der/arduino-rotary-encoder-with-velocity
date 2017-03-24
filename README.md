Arduino library for use with rotary encoders. Allows you to sense turn velocity by outputting increasingly larger numbers based on number of turns in one direction. You set the numbers in the output equations. It's easy, fear not.

Here is a trivial implementation of the library.

```c
#include <RotaryEncoder.h>;

RotaryEncoder encoder(A0,A1,5,6,1000); 
void setup() { 
  Serial.begin(57600); 
} 
void loop() { 
  int enc = encoder.readEncoder(); 
  if(enc != 0) { 
    Serial.println(enc); 
  } 
  delayMicroseconds(5); 
}
```

Inside the library, the code counts the number of the sequential clicks in one direction within less than the time constant you pass in when you instantiate the object. In the above example, the selected time constant is 1000µs (the 5th variable). If the user waits longer than that amount of time the counter resets. If the user changes direction the counter resets. To determine the return value I divide the counter by the 4th variable you pass in, 6 in this case, and then multiply that by 5 (the 3rd variable) and return that value. Turning anti-clockwise is the same except that I make it negative (multiply value by -1). So, if you turn the knob 30 times in a clockwise direction I will return (30/6)x*5 or 25. Bear in mind that 30 times doesn't mean 30 detents of the encoder. Each encoder is different. The ones I have in my drawer return 4 times per detent, YMMV.

In order for this to work, you need to have clean reads of the encoder (or it will reset the counter). To do this effectively, you really need to "debouce" the switch. I've never been able to effectively do this in software. I use 10000pF capacitors between the A pin and GND and B pin GND. This makes the circuit very well protected from bad reads. Furthermore, you need to check the value more frequently than it can change otherwise the quadrature signal will become out of sync and you will not know what direction you are turning.

[![Youtube Video](http://img.youtube.com/vi/f-rprOXX8qo/0.jpg)](http://www.youtube.com/watch?v=f-rprOXX8qo)
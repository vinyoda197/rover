
#include <Servo.h>

#define servoPin 6
Servo Servo1;

void setup() {
  // put your setup code here, to run once:
  Servo1.attach(servoPin);
  Servo1.write(0); // initial
}

void loop() {
  servoTap();
  delay(5000);
}


void servoTap ()
{
  Servo1.write(180); 
   delay(1000); 
   Servo1.write(0);
}

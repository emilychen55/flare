#include <RFduinoBLE.h>

#define neoPixel 6

void setup() {
  // put your setup code here, to run once:
  pinMode(neoPixel, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(neoPixel, HIGH);
  delay(10);
  digitalWrite(neoPixel, HIGH);
  delay(10);
}

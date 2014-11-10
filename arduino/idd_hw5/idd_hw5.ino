#include <Servo.h>

// pins and objects
Servo servo1;
int photoDiode = A3;

// global values
int pos = 0;
int thresh = 20;
int photoValue = 0;
int degree = 100;
int flag = 0;

// actual main loop function
void flareOn(int s) {
  if (s == 1) {
    for (pos = 0; pos < degree; pos += 1) {
      servo1.write(pos);
      delay(15);
    }
    flag = 1;
  }
  else if (s == 0) {
    // turn light on
    for (pos = degree; pos >= 1; pos -= 1) {
      servo1.write(pos);
      delay(15);
    }
    flag = 0;
  }
}

void pc_listen() {
  if (Serial.available()) {
    char incomingByte = Serial.read();
    if (incomingByte == 'a') {
      Serial.print(photoValue);
    } else if (incomingByte =='1') {
      flareOn(1);
    } else if (incomingByte =='0') {
      flareOn(0);
    } 
  }
}

void setup() {
  servo1.attach(9);
  Serial.begin(9600);
  // initialize analog input to photodiode
  pinMode(photoDiode, INPUT);
}

void loop() {
  photoValue = analogRead(photoDiode);
  pc_listen();
}

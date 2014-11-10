#include <Servo.h>

// pins and objects
Servo servo1;
int photoDiode = A3;

// global values
int pos = 0;
int thresh = 20;
int photoValue = 0;
int degree = 120;
int flag = 0;

// actual main loop function
void flareOn(int photoValue) {
  if (photoValue > thresh && flag == 0) {
    // turn light off
    for (pos = 0; pos < degree; pos += 1) {
      servo1.write(pos);
      delay(15);
    }
    flag = 1;
  }
  else if (photoValue <= thresh && flag == 1) {
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
      Serial.println(photoValue);
    } else {
      Serial.println("Servo control here");
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
  
//  flareOn(photoValue);
  
  pc_listen();
  
}

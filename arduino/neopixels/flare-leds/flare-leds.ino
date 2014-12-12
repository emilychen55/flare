#include <RFduinoBLE.h>

#define redPin 4
#define greenPin 3
#define bluePin 2
static const char* NAME = "Stark"; 
//Tony: F3:FA...
//Stark: F3:DA:73:20:77:03
//Iron Man: ED:01..
static const int ADVERTISEMENT_INTERVAL = 675;
static bool connectionStatus = false;
int pixelLength = 16; // LED for GPIO 5

void advertise(uint32_t ms) {
  //start advertising
  RFduinoBLE.begin();
  //advertise for ms milliseconds
  RFduino_ULPDelay(ms);
  //  //stop advertising
  RFduinoBLE.end();
}

//This function will automatically run everytime the device is connected
void RFduinoBLE_onConnect() {
  //Code here
  Serial.println("connected");
  connectionStatus = true;
}

//This function will automatically run everytime the device is disconnected
void RFduinoBLE_onDisconnect() {
  //Code here
  Serial.println("disconnected");
  connectionStatus = false;
}

void RFduinoBLE_onReceive(char *data, int len) {
  Serial.println(len);  
  Serial.print("r: ");
  Serial.println((int)data[0]);
  Serial.print("g: ");
  Serial.println((int)data[1]);
  Serial.print("b: ");
  Serial.println((int)data[2]);
  if (len >= 3) {
    int r = (int)data[0];
    int g = (int)data[1];
    int b = (int)data[2];
    // set color and brightness to LED
    lightingMode(r, g, b); 
  }
}

void setup() {
  delay(2000);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Set Device Parameters
  RFduinoBLE.deviceName = NAME;
  RFduinoBLE.advertisementInterval = ADVERTISEMENT_INTERVAL;
  RFduinoBLE.txPowerLevel = +4;
  RFduinoBLE.begin();
  Serial.begin(9600);
}

void loop() {
  //Serial.println("TONY");
//  lightingMode(220, 0, 0);
//  delay(2000);
//  lightingMode(0, 220, 0);
//  delay(2000);
//  lightingMode(0, 0, 220);
//  delay(2000);
//  testFade(); 
  RFduino_ULPDelay(2000); // Ultra Low Power Delay
}

/** LED code **/
void lightingMode(int r, int g, int b) {
    //set PWM for each LED
    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);
    
    //lightingMode(255, 220, 80); // warm light
    //lightingMode(255, 147, 41); // candle
}

void decreaseColorTone(char color[]) {
  int incr = 0;
  for(int i = 0; i<50; i++) {
    incr = 5*i;
    if (color[0] = 'r') {
      lightingMode(255-incr, 225, 255);
      delay(150);
    }
    else if (color[0] = 'b') {
      lightingMode(255, 225-incr, 255);
      delay(150);
    }
    else if (color[0] = 'g') {
      lightingMode(255, 225, 255-incr);
      delay(150);
    }
  }
}

void paired() {
 if (connectionStatus == true) {
    lightingMode(0, 100, 0);
    delay(100);
  } else {
    lightingMode(0, 0, 100);
    delay(100);
  }
}

void turnOff(int val) {
  if (val == 0) { // red
    analogWrite(redPin, 0);
  }
  else if (val == 1) { //green
    analogWrite(greenPin, 0);
  }
  else if (val == 2) { // blue
    analogWrite(bluePin, 0);
  }
  else if (val == 10) { // white
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
}

void fade(char* color) {
  if (color == "white") {
    for(int i = 0; i<360; i++){
      //convert 0-360 angle to radian (needed for sin function)
      float rad = DEG_TO_RAD * i;
      //calculate sin of angle as number between 0 and 255
      int sinOut = constrain((sin(rad) * 128) + 128, 0, 255); 
      analogWrite(redPin, sinOut);
      analogWrite(greenPin, sinOut);
      analogWrite(bluePin, sinOut);
      delay(10);
    }
  }
  else if (color == "red") {
    for(int i = 0; i<360; i++){
      //convert 0-360 angle to radian (needed for sin function)
      float rad = DEG_TO_RAD * i;
      //calculate sin of angle as number between 0 and 255
      int sinOut = constrain((sin(rad) * 128) + 128, 0, 255); 
      analogWrite(redPin, sinOut);
      analogWrite(greenPin, 220);
      analogWrite(bluePin, 220);
      delay(10);
    }
  }
  else if (color == "green") {
    for(int i = 0; i<360; i++){
      //convert 0-360 angle to radian (needed for sin function)
      float rad = DEG_TO_RAD * i;
      //calculate sin of angle as number between 0 and 255
      int sinOut = constrain((sin(rad) * 128) + 128, 0, 255); 
      analogWrite(redPin, 220);
      analogWrite(greenPin, 220);
      analogWrite(bluePin, sinOut);
      delay(10);
    }
  }
  else if (color == "blue") {
    for(int i = 0; i<360; i++){
      //convert 0-360 angle to radian (needed for sin function)
      float rad = DEG_TO_RAD * i;
      //calculate sin of angle as number between 0 and 255
      int sinOut = constrain((sin(rad) * 128) + 128, 0, 255); 
      analogWrite(redPin, 220);
      analogWrite(greenPin, 220);
      analogWrite(bluePin, sinOut);
      delay(10);
    }
  }
}

void testFade(){
  for(int i = 0; i<360; i++){
    //convert 0-360 angle to radian (needed for sin function)
    float rad = DEG_TO_RAD * i;
    //calculate sin of angle as number between 0 and 255
    int sinOut = constrain((sin(rad) * 128) + 128, 0, 255); 
    analogWrite(redPin, sinOut);
    analogWrite(greenPin, sinOut);
    analogWrite(bluePin, sinOut);
    delay(10);
  }
}

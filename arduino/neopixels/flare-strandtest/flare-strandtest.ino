#include <RFduinoBLE.h>
#include "Neopixel.h"
#include "Pins.h"

static const char* NAME = "Tony";
static const int ADVERTISEMENT_INTERVAL = 675;
static bool connectionStatus = false;
int pixelLength = 16; // LED for GPIO 2

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

void setup() {
  // Set Device Parameters
  RFduinoBLE.deviceName = NAME;
  RFduinoBLE.advertisementInterval = ADVERTISEMENT_INTERVAL;
  RFduinoBLE.txPowerLevel = +4;
  
  begin(); //NeoPixels to begin
  RFduinoBLE.begin();
  Serial.begin(9600);
}

void loop() {
  if (connectionStatus == true) {
    colorOn(1);
    turnOffLights();
  } else {
    colorOn(2);
    turnOffLights();
  }
  //RFduino_ULPDelay(350); // Ultra Low Power Delay for 350 milliseconds
}

void colorOn(int val) {
    for (uint16_t i=0; i<pixelLength; i++) {
      if (val == 0) { //red
        set_pixel_color(i, Color(255, 0, 0));
      }
      else if (val == 1) { //green
        set_pixel_color(i, Color(0, 255, 0));
      }
      else if (val == 2) { //blue
        set_pixel_color(i, Color(0, 0, 255));
      } else { //white
        set_pixel_color(i, Color(56, 56, 56));
      }
    delay(50);
    show();
  }
}

void turnOffLights() {
  for (int i = pixelLength-1; i > 0; i--) {
    set_pixel_color(i, Color(0, 0, 0));
  }
  show();
}

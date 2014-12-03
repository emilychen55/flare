// pins
int micPin = A3;

// global variables
int micValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  micValue = analogRead(micPin);
  Serial.println(micValue);
  delay(100);
}

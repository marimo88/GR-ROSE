// For using ICS manager
#include <Arduino.h>

void setup() {
  pinMode(PIN_LED1, OUTPUT);

  Serial.begin(115200); // to USB
  Serial1.begin(115200, SERIAL_8E1); // to Motor
  Serial1.direction(HALFDUPLEX);
}

void loop() {
  if(Serial.available())
  {
    char c = Serial.read();
    Serial1.write(c);
  }

  if(Serial1.available())
  {
    char c = Serial1.read();
    Serial.write(c);
  }
}
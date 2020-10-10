#include <Arduino.h>
#include <ICS.h>

#define KRS_MIN 3500
#define KRS_MAX 11500
#define KRS_ORG 7500
#define KRS_FREE 0
#define SERVO_MIN -135
#define SERVO_MAX 135

IcsController ICS(Serial1);
IcsServo servo1;

void krs_setposition(IcsServo* servo, float radian){
  int angle = radian * 180 / PI;
  int pos = map(angle, SERVO_MIN, SERVO_MAX, KRS_MIN, KRS_MAX);
  if(pos > KRS_MIN && pos < KRS_MAX){
    servo->setPosition(pos);
    delay(1);
  }
}

float krs_getposition(IcsServo* servo){
  int pos = servo->getPosition();
  delay(1);
  int angle = map(pos, KRS_MIN, KRS_MAX, SERVO_MIN, SERVO_MAX);
  return angle * PI / 180; // angle to radian
}

void setup() {
  Serial.begin(9600);
  ICS.begin();
  servo1.attach(ICS, 0x01);
  
  krs_setposition(&servo1, 0);
}

void loop() {
  static bool id1, id2, id3;
  krs_setposition(&servo1, (PI/2));
  delay(1000);
  Serial.println(krs_getposition(&servo1));
  krs_setposition(&servo1, -(PI/2));
  delay(1000);
  Serial.println(krs_getposition(&servo1));
}
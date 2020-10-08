#include <Arduino.h>
#include <ICS.h>

#define KRS_MIN 3500
#define KRS_MAX 11500
#define KRS_ORG 7500
#define KRS_FREE 0
#define SERVO_MIN -135
#define SERVO_MAX 135

IcsController ICS(Serial1);
IcsServo servo[3];

void krs_setposition(IcsServo* servo, float radian){
  int angle = radian * 180 / PI;
  int pos = map(angle, SERVO_MIN, SERVO_MAX, KRS_MIN, KRS_MAX);
  if(pos > KRS_MIN && pos < KRS_MAX){
    servo->setPosition(pos);
    delay(1);
  }
}

void setup() {
  Serial.begin(9600);
  ICS.begin();
  for(int i = 0; i < 3; i++){
    servo[i].attach(ICS, i+1); // id1 to id3
    servo[i].setStretch(30);
    delay(1);
    servo[i].setSpeed(30);
    delay(1);
    krs_setposition(&servo[i], 0);
    delay(1);
  }
}

void loop() {
  for(int i = 0; i < 3; i++){
    int angle = random(-45, 45);
    float radian = angle * PI / 180;
    krs_setposition(&servo[i], radian);
    delay(200);
  }
}
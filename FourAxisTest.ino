// 4軸グリッパ確認動作

// ICS
#include <Arduino.h>
#include <ICS.h>

#define KRS_MIN 3500
#define KRS_MAX 11500
#define KRS_ORG 7500
#define KRS_FREE 0
#define SERVO_MIN -135
#define SERVO_MAX 135

// ROS
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}
ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb );
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

IcsController ICS(Serial1);
IcsServo servo[4];

void krs_setposition(IcsServo* servo, float radian){
  int angle = radian * 180 / PI;
  int pos = map(angle, SERVO_MIN, SERVO_MAX, KRS_MIN, KRS_MAX);
  if(pos > KRS_MIN && pos < KRS_MAX){
    servo->setPosition(pos);
    delay(1);
  }
}

void setup() {
  // ICS
  Serial.begin(9600);
  ICS.begin();
  for(int i = 0; i < 4; i++){
    servo[i].attach(ICS, i+1); // id1 to id4
    servo[i].setStretch(30);
    delay(1);
    servo[i].setSpeed(30);
    delay(1);
    krs_setposition(&servo[i], 0);
    delay(1);
    
  //ROS
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
  }
}

void loop() {
  //ICS
  for(int i = 0; i < 4; i++){
    int angle = random(-45, 45);
    float radian = angle * PI / 180;
    krs_setposition(&servo[i], radian);
    delay(200);
  }
    
   //ROS
  str_msg.data = "hello";
  chatter.publish( &str_msg );
  nh.spinOnce();
}
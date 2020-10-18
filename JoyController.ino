
#include <Arduino.h>
#include <ICS.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

#define KRS_MIN 3500
#define KRS_MAX 11500
#define KRS_ORG 7500
#define KRS_FREE 0
#define SERVO_MIN -135
#define SERVO_MAX 135

ros::NodeHandle  nh;

IcsController ICS(Serial1);
IcsServo servo[4];
float angle[4];
char hello[13] = "hello world!";

void messageCb( const geometry_msgs::Twist& cmd_vel){
  angle[0] = cmd_vel.linear.x * 90 ;
  angle[1] = cmd_vel.linear.y * 90 ;
  angle[2] = cmd_vel.angular.x * 45 ;
  angle[3] = cmd_vel.angular.y * 45 ;
}

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );

void krs_setposition(IcsServo* servo, float radian){
  int angle = radian * 180 / PI;
  int pos = map(angle, SERVO_MIN, SERVO_MAX, KRS_MIN, KRS_MAX);
  if(pos > KRS_MIN && pos < KRS_MAX){
    servo->setPosition(pos);
    delay(1);
  }
}

void setup()
{
  pinMode(PIN_LED1, OUTPUT);
  
  // ICS Setup
  Serial.begin(9600);
  ICS.begin();
  for(int i = 0; i < 4; i++){
    servo[i].attach(ICS, i+1); // id1 to id4
    servo[i].setStretch(50);
    delay(1);
    servo[i].setSpeed(50);
    delay(1);
    krs_setposition(&servo[i], 0);
    delay(1);
  }

  // ROS Setup
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop()
{
  //ICS
  for(int i = 0; i < 4; i++){
    // int angle = random(-45, 45);
     float radian = angle[i] * PI / 180;
    krs_setposition(&servo[i], radian);
  delay(10);
  }

  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(10);
}
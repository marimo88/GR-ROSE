/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 * GR-ROSE用LEDピン指定
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;


void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(PIN_LED1, HIGH-digitalRead(PIN_LED1));   // blink the led
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb );



std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

void setup()
{
  pinMode(PIN_LED1, OUTPUT);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(500);
}
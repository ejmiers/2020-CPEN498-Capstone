/*
Publisher of joystick data
*/

#include <ros.h>
#include <main_node/lightDetected.h>

main_node::lightDetected light_detected_msg;

ros::Publisher light_detected("lightDetected", &light_detected_msg);
ros::NodeHandle nh;

const int lightSensorPin = A0;

void setup()
{ 
  Serial.begin(9600);
  
  nh.initNode();
  nh.advertise(light_detected);
}

void loop()
{
   
  int lightSensorValue = analogRead(lightSensorPin);
  
  if (lightSensorValue >= 700) {
    light_detected_msg.value = lightSensorValue;
    light_detected.publish(&light_detected_msg);
    nh.spinOnce();
    delay(2000);
  }
  
  delay(100);
}

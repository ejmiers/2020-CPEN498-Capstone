/* Node responsible for collecting light intensity data from sensor
   Publishes a message with the "light_detected" topic when intensity values cross a threshold
   
   Written by: Eric Miers, 1/31/2020
*/

#include <ros.h>
#include <main_node/light_detected.h>
#include <main_node/move_on.h>
#include <main_node/comp_stop.h>

#define LIGHT_SENSOR_PIN A0
#define LIGHT_DETECTED 1

//Allocate message datasructures to hold message being published
main_node::light_detected lightDetectedMsg;

//Initialize ROS publishers
ros::Publisher lightDetectedPub("light_detected", &lightDetectedMsg);

//Initialize ROS Node Handler
ros::NodeHandle nh;

//Allocate Flags
int stopLoop;

//Called if a "comp_stop" message was received by the corresponding subscriber
void compStopCallback(const main_node::comp_stop& msg) {
  
  //Set Flag
  if (msg.stop == 1) {
    stopLoop = 1;
  }
} 

//Initialize ROS Subscribers
ros::Subscriber<main_node::comp_stop> compStopSub("comp_stop", &compStopCallback);

//Intialize/Set ROS node, publishers/subscribers, flags
void setup() {
  Serial.begin(56000);
  nh.getHardware()->setBaud(56000);
  stopLoop = 0;
  
  nh.initNode();
  nh.advertise(lightDetectedPub);
  nh.subscribe(compStopSub);
}

//Main method for the node
void loop() {
  if (stopLoop == 0) {
      //Read from the analog pin connected to light sensor
      int lightSensorValue = analogRead(LIGHT_SENSOR_PIN);
      Serial.println(lightSensorValue);
      
      //If the value has crossed the "threshold" indicating a lit button is present, publish a message to the drivetrain
      if (lightSensorValue >= 700){
        lightDetectedMsg.detected = LIGHT_DETECTED;
        lightDetectedPub.publish(&lightDetectedMsg);
        
        delay(2500);
      }
      
      nh.spinOnce();
      delay(100);
  }
}

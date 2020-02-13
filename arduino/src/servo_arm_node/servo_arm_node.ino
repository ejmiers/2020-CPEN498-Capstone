/* Node responsible for contolling the servo arm

   Upon Receiving a "move_arm" message, the servo will be rotated until either the FSR threshold is met or the servo is fully extended
   Will pause for 25ms before resetting the servo to its original state
   
   Written by: Eric Miers, 1/31/2020
*/

#include <Servo.h>
#include <ros.h>
#include <main_node/move_arm.h>
#include <main_node/move_on.h>
#include <main_node/comp_stop.h>

#define FSR_PIN   A0
#define SERVO_PIN 9

//Allocate a servo object
Servo servo;

//Allocate a ROS Node Handler
ros::NodeHandle nh;

//Allocate message datasructures to hold message being published
main_node::move_on moveOnMsg;

//Initialize ROS publishers
ros::Publisher moveOnPub("move_on", &moveOnMsg);

//Allocate Flags
int stopLoop;

//Called if a "move_on" message was received by the corresponding subscriber
void moveArmCallback(const main_node::move_arm& msg) {
  
  //Verify that the move flag in the message is set to 1
  if (msg.move == 1){
    
    //Reinitialize servo position and fsr data
    int pos = 0;
    int fsrValue = 0;
    
    // Slowly extrend the servo motor arm until either the fsr threshold is met or the servo completes 180 degree rotation
    while ((fsrValue < 1000) && (pos < 110)){
      fsrValue = analogRead(FSR_PIN);
      servo.write(pos);
      delay(15);
      pos +=1;
    }
    
    //Wait for atleast 25ms while the button is pushed in (per IEEE competition guidelines)
    delay(500);
    
    //Reset the servo motor's position to 0
    servo.write(0);
    
    //Publish message indicating the device is ready to move on to the next state
    moveOnMsg.moveOn = 1;
    moveOnPub.publish(&moveOnMsg);
    nh.spinOnce();
    //moveOnMsg.moveOn = 0;
  }
}

//Called if a "comp_stop" message was received by the corresponding subscriber
void compStopCallback(const main_node::comp_stop& msg) {
  
  //Set Flag
  if (msg.stop == 1) {
    stopLoop = 1;
  }
} 

//Initialize ROS Subscribers
ros::Subscriber<main_node::move_arm> moveArmSub("move_arm", &moveArmCallback);
ros::Subscriber<main_node::comp_stop> compStopSub("comp_stop", &compStopCallback);

//Intialize/Set ROS node, publishers/subscribers, flags
void setup() {
//  Serial.begin(9600);
//  nh.getHardware()->setBaud(9600);
  Serial.begin(56000);
  nh.getHardware()->setBaud(56000);
  servo.attach(SERVO_PIN);
  servo.write(0);
  stopLoop = 0;
  
  nh.initNode();
  nh.advertise(moveOnPub);
  nh.subscribe(moveArmSub);
  nh.subscribe(compStopSub);
}

////Main method for the node
void loop() {
  while (stopLoop == 0) {
      nh.spinOnce();
      delay(100);  
    }
}


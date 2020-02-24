/* Node responsible for moving robot to the buttons

   Upon Receiving a "move_dt" message, the direction of the next button is computed and the wheel servos spin until the ultrasonic sensor confirms the button is in range.
   Instructs the arm device to activate when the distance is within range
   
   Written by: Chris Samuelsen, Eric Miers, 2/23/2020
*/

#include <ros.h>
#include <main_node/comp_stop.h>
#include <main_node/move_dt.h>
#include <main_node/move_arm.h>
#include <main_node/move_on.h>

#include "Wire.h"
#include <Servo.h>

Servo motorLeft;
Servo motorRight;

// 500 digits of pi stored as a list (Extremely Optimistic)
int Button_Distances[10] = {5, 13, 20, 28, 35, 44, 52, 59, 67, 74};

extern "C" {
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

//#include <Adafruit_VL53L0X_master/src/Adafruit_VL53L0X.h>
//#include "Adafruit_VL53L0X.h"

//Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// this constant won't change. It's the pin number of the sensor's output:
const int pingPin = 7;

//Allocate a ROS Node Handler
ros::NodeHandle nh;

//Allocate message datasructures to hold message being published
main_node::move_arm moveArmMsg;
main_node::move_on moveOnMsg;

//Initialize ROS publishers
ros::Publisher moveArmPub("move_arm", &moveArmMsg);

//Allocate Flags
int stopLoop;
int ackFlag;

/*#define TCAADDR 0x70

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}
// standard Arduino setup()*/

//Called if a "comp_stop" message was received by the corresponding subscriber
void compStopCallback(const main_node::comp_stop& msg) {
  
  //Set Flag
  if (msg.stop == 1) {
    motorLeft.detach();
    motorRight.detach();
    stopLoop = 1;
  }
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

long read_ultra(){
// ultrasonic sensor reading/printing
  long duration, cm;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  char cBuff[4];
  dtostrf(cm, 4, 0, cBuff);
  nh.loginfo(cBuff);
  return cm;
}

void moveOnCallback(const main_node::move_on& msg) {
  if (msg.moveOn == 1){
    ackFlag = 1;
  }
}

void moveDTCallback(const main_node::move_dt& msg) { 
  int currentDigit = msg.currentDigit;
  int nextDigit = msg.nextDigit;
  long stop_Distance = Button_Distances[nextDigit];
  int currLoc;
  int counter = 0;
  nh.loginfo("Made it to Drivetrain callback");
 
  while(1){    //move until current measurement is equal to distance of button
      nh.spinOnce();
      
      if(currentDigit > nextDigit){  //move left
        motorLeft.attach(10);
        motorRight.attach(9);
        currLoc = read_ultra();
        motorLeft.write(110);
        motorRight.write(70);
        if(stop_Distance+2 >= currLoc && stop_Distance-2 <= currLoc){    //change this to stop_Distance >= read_ultra()
          nh.loginfo("At Button, greater than");
          char cBuff[4];
          dtostrf(currLoc, 4, 0, cBuff);
          nh.loginfo(cBuff);
          counter++;
        }
      }
      
      else if(currentDigit < nextDigit){  //move right
        motorLeft.attach(10);
        motorRight.attach(9);
        currLoc = read_ultra();
        motorLeft.write(80);
        motorRight.write(100);
        if(stop_Distance-2 <= currLoc && stop_Distance+2 >= currLoc){    //change this to stop_Distance >= read_ultra()
          nh.loginfo("At Button, less than");
          char cBuff[4];
          dtostrf(currLoc, 4, 0, cBuff);
          nh.loginfo(cBuff);
          counter ++;
        }
         
        if(stop_Distance-2 <= currLoc && stop_Distance+2 >= currLoc){
           counter++;
        }
           
      }
      
      if (counter >= 5) {
         motorLeft.detach();
         motorRight.detach();
         counter = 0;
         delay(1000);  
            
            
            // Check for acknowledgement
         while (ackFlag != 1) {
           moveArmMsg.move = 1;
           moveArmPub.publish(&moveArmMsg);
           nh.spinOnce();
           nh.loginfo("Published to ARM Node");
              
           for (int i = 0; i < 5; i++){
             delay(1000);
             nh.spinOnce();
           }
         }
            
         ackFlag = 0;
         break;  
      }
    }
    
    nh.loginfo("Waiting for next digit");     
}  

//Initialize ROS Subscribers
ros::Subscriber<main_node::move_dt> moveDTSub("move_dt", &moveDTCallback);
ros::Subscriber<main_node::move_on> moveOnSub("move_on", &moveOnCallback);
ros::Subscriber<main_node::comp_stop> compStopSub("comp_stop", &compStopCallback);

void setup(){
  Wire.begin();
  
  Serial.begin(57600);
  nh.getHardware()->setBaud(57600);
  stopLoop = 0;
  
  nh.initNode();
  nh.advertise(moveArmPub);
  nh.subscribe(moveOnSub);
  nh.subscribe(moveDTSub);
  nh.subscribe(compStopSub);
  
  ackFlag = 0;

  //Serial.print("Start.");

  /*tcaselect(1);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  tcaselect(2);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }*/

  //Serial.println(" End setup");
}

void loop(){
  
  while (stopLoop == 0) {
      nh.spinOnce();
      delay(100);  
  }
}

// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
#include <ros.h>
#include <main_node/lightDetected.h>
#include <main_node/servoExtend.h>
#include <main_node/servoRetract.h>
#include <main_node/servoComplete.h>
#include <main_node/fsrTriggered.h>

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

const int fsrPin = A0;
 
int fsrValue = 0;
int pos = 0;    // variable to store the servo position
int servoExtended = 0;
int servoRetracted = 0;
int servoCompleted = 0;

ros::NodeHandle nh;
main_node::servoExtend servo_extend_msg;
main_node::servoRetract servo_retract_msg;
main_node::servoComplete servo_complete_msg;
main_node::fsrTriggered fsr_triggered_msg;

ros::Publisher servo_extend("servoExtend", &servo_extend_msg);
ros::Publisher servo_retract("servoExtend", &servo_retract_msg);
ros::Publisher servo_complete("servoExtend", &servo_complete_msg);
ros::Publisher fsr_triggered("fsrTriggered", &fsr_triggered_msg);
  
void servoController(const main_node::lightDetected& msg) {
  
  //if (msg.value >= 700){
    
    servo_extend_msg.extend = 1;
    servo_extend.publish(&servo_extend_msg);
    nh.spinOnce();
    
    int fsrValue = 0;
    while (fsrValue < 1000)  // goes from 0 degrees to 180 degrees 
    { 
      fsrValue = analogRead(fsrPin); 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(5);       // waits 15ms for the servo to reach the position 
      pos += 1;
    }
    
    delay(100);
    
    fsr_triggered_msg.triggered = fsrValue;
    fsr_triggered.publish(&fsr_triggered_msg);
    nh.spinOnce();
    
    servo_retract_msg.retract = 1;
    servo_retract.publish(&servo_retract_msg);
    nh.spinOnce();
    
    while(pos >= 1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(5);      // waits 15ms for the servo to reach the position 
      pos -= 1;
    } 
    
    servo_complete_msg.complete = 1;
    servo_complete.publish(&servo_complete_msg);
    nh.spinOnce();
  //}
} 

ros::Subscriber<main_node::lightDetected> sub("lightDetected", &servoController);

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
  
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(servo_extend);
  nh.advertise(servo_retract);
  nh.advertise(servo_complete);
  nh.advertise(fsr_triggered);
} 

void loop() {
  nh.spinOnce();
  delay(100);
}

// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
#include <ros.h>
#include <main_node/joystick_btn.h>
#include <main_node/servo.h>

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 

ros::NodeHandle nh;
main_node::servo servo_pos_msg;
ros::Publisher servo_pos("servo", &servo_pos_msg);
 
void servoController(const main_node::joystick_btn& msg) {
  
  if (msg.pushed == 0){
    
    for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(5);                       // waits 15ms for the servo to reach the position 
    } 
    delay(100);
    for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(5);                       // waits 15ms for the servo to reach the position 
    } 
    
    servo_pos_msg.pos = pos;
    servo_pos.publish(&servo_pos_msg);
    nh.spinOnce();
  }
} 

ros::Subscriber<main_node::joystick_btn> sub("joystick_btn", &servoController);

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(servo_pos);
} 

void loop() {
  nh.spinOnce();
  delay(100);
}

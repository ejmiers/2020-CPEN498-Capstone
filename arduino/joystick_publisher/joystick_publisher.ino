/*
Publisher of joystick data
*/

#include <ros.h>
#include <main_node/joystick.h>
#include <main_node/joystick_btn.h>

const int xPin = A0; //X attach to A0
const int yPin = A1; //Y attach to A1
const int zPin = 7; //Bt attach to digital 7

int joyStickX = 0;
int joyStickY = 0;
int joyStickZ = 0;

main_node::joystick js_an_msg;
main_node::joystick_btn js_btn_msg;

ros::Publisher js_analog("joystick_analog", &js_an_msg);
ros::Publisher js_btn("joystick_btn", &js_btn_msg);
ros::NodeHandle nh;

void setup()
{ 
  pinMode(zPin,INPUT); //set btpin as INPUT
  digitalWrite(zPin, HIGH); //and HIGH
  Serial.begin(9600); //initialize serial
  
  nh.initNode();
  nh.advertise(js_analog);
  nh.advertise(js_btn);
}

void loop()
{
 
  joyStickX = analogRead(xPin);
  Serial.print("X: ");//print "X: "
  Serial.print(analogRead(xPin),DEC); //read the value of A0 and print it in decimal
  
  joyStickY = analogRead(yPin);
  Serial.print("\tY: ");//print "X: "
  Serial.print(joyStickY,DEC); //read the value of A0 and print it in decimal
  
  joyStickZ = digitalRead(zPin);
  Serial.print("\tZ: ");//print "X: "
  Serial.print(joyStickZ,DEC); //read the value of A0 and print it in decimal
    
  if (joyStickX != 510 && joyStickX != 511 && joyStickY != 508){
    js_an_msg.x = joyStickX;
    js_an_msg.y = joyStickY;
    js_an_msg.z = joyStickZ;
    
    js_analog.publish(&js_an_msg);
    nh.spinOnce();
  }
  
  if (joyStickZ == 0){
    js_btn_msg.pushed = joyStickZ;
    
    js_btn.publish(&js_btn_msg);
    nh.spinOnce();
  }
  
  delay(100);
  
  /*
  Serial.print("\tY: "); //print "Y: "
  Serial.print(analogRead(yPin),DEC); //read the value of A1 and print it in decimal
  Serial.print("\tZ: "); //print "Z: "
  Serial.println(digitalRead(btPin)); ////read the value of pin7 and print it
  delay(100);//delay 100ms
  */
}

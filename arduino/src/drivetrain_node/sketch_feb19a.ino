/**
   CODE by Johnathan Martin a.k.a the_jmart
   By using the TCA9548A I2C Multiplexer Breakout you can read
   four VL53L0X Time-of-Flight range sensors at the same time over
   one I2C address. This code is written specific for the devices
   used.

   TCA9548 I2CScanner.pde -- I2C bus scanner for Arduino
   Based on code c. 2009, Tod E. Kurt, http://todbot.com/blog/

*/

#include "Wire.h"
#include <Servo.h>;
Servo motorLeft;
Servo motorRight;

// 500 digits of pi stored as a list (Extremely Optimistic)
int PI_LIST[11] = {5, 3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
int Button_Distances[10] = {5, 13, 20, 28, 35, 44, 52, 59, 67, 74};

int PI_Index = 0;
int currentDigit, nextDigit, prevDigit;
int currLoc, nextLoc;

extern "C" {
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// this constant won't change. It's the pin number of the sensor's output:
const int pingPin = 7;

#define TCAADDR 0x70

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}
// standard Arduino setup()
void setup()
{

  while (!Serial);
  delay(1000);
  Wire.begin();
  Serial.begin(9600);

  Serial.print("Start.");

  tcaselect(1);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  tcaselect(2);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }

  Serial.println(" End setup");
  delay(2000);

}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
//Method to move forwards to next location
void move_F(int currLoc, int nextLoc) {
  if(currLoc>nextLoc) {
    motorLeft.attach(10);
    motorRight.attach(9);
    //currLoc=microsecondsToCentimeters(duration);
    motorLeft.write(0);
    motorRight.write(180);
    //currLoc = getLocation();
    delay(50);
    return;  
  }
}
//Method to move backwards to next location
void move_B(int currLoc, int nextLoc) {
  if(currLoc<nextLoc) {
    motorLeft.attach(10);
    motorRight.attach(9);
    motorLeft.write(180);
    motorRight.write(0);
    delay(50);
    return;
    
      //currLoc = getLocation();
  }
}
int read_ultra(){
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
  Serial.print("read_ultra reading: ");
  Serial.println(cm);

  return cm;
}

void loop(){
  //PI_Index=0;  
  currentDigit = PI_LIST[PI_Index];
  nextDigit = PI_LIST[PI_Index + 1];
  int stop_Distance = Button_Distances[PI_LIST[PI_Index+1]];
  int currLoc = read_ultra();
 // int nextLoc = Button_Distances[nextDigit];
 // if (PI_LIST[PI_Index] > PI_LIST[PI_Index+1]) {   //move left
 
    while(currLoc != stop_Distance){    //move until current measurement is equal to distance of button
      currentDigit = PI_LIST[PI_Index];
      nextDigit = PI_LIST[PI_Index + 1];
      if(currentDigit > nextDigit){  //move left
      Serial.println(currentDigit);
      Serial.println(nextDigit);
      motorLeft.attach(10);
      motorRight.attach(9);
      currLoc=read_ultra();
      motorLeft.write(100);
      motorRight.write(80);
      currLoc=read_ultra();
      Serial.println("in first if statement, moving left");
      if(stop_Distance >= read_ultra()){    //change this to stop_Distance >= read_ultra()
      Serial.println("found the button");
      motorLeft.detach();
      motorRight.detach();
      PI_Index++;
      stop_Distance = Button_Distances[PI_LIST[PI_Index+1]];
      currentDigit = PI_LIST[PI_Index];
      nextDigit = PI_LIST[PI_Index + 1];
      delay(5000);
      //break;
    }
      }
      if(stop_Distance+1 == read_ultra()|| stop_Distance-1==read_ultra()){    //change this to stop_Distance >= read_ultra()
      Serial.println("found the button");
      motorLeft.detach();
      motorRight.detach();
      PI_Index++;
      stop_Distance = Button_Distances[PI_LIST[PI_Index+1]];
      currentDigit = PI_LIST[PI_Index];
      nextDigit = PI_LIST[PI_Index + 1];
      delay(5000);
      //break;
    }
      if(currentDigit < nextDigit){  //move right
      Serial.println(currentDigit);
      Serial.println(nextDigit);
      motorLeft.attach(10);
      motorRight.attach(9);
      currLoc=read_ultra();
      motorLeft.write(80);
      motorRight.write(100);
      currLoc=read_ultra();
      Serial.println("in second if statement, moving right");
    }
      }
      currLoc=read_ultra();
    Serial.print("nextDigit is: ");
    Serial.println(nextDigit);
    currLoc=read_ultra();
    Serial.print("Travling to: ");
    Serial.println(currentDigit);
    currLoc=read_ultra();
    Serial.print("stop_Distance is: " );
    Serial.println(stop_Distance);
    currLoc=read_ultra();
    //Serial.print(")");
    //Serial.println();
    
    Serial.print("PI_INDEX is: ");
    Serial.println(PI_Index);
    currLoc=read_ultra();
    if(stop_Distance+1 == read_ultra()|| stop_Distance-1==read_ultra()){    //change this to stop_Distance <= read_ultra()
      Serial.println("found the button");
      motorLeft.detach();
      motorRight.detach();
      PI_Index++;
      stop_Distance = Button_Distances[PI_LIST[PI_Index+1]];
      currentDigit = PI_LIST[PI_Index];
      nextDigit = PI_LIST[PI_Index + 1];
      delay(5000);
      //break;
    
    }

}

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Encoders encoders;

// 909.7 counts per revolution, wheel diameter = 122.52211349
//millimetersPerCount = 122.52211349/909.7 = 0.1346840865
const float milliMetersPerCount = 0.1346840865; 

// encoder counts, wich will be coverted to length
int newCounts;
int lastCounts;

// variables for millis()
unsigned long timeAfterLastCount = 0;
unsigned long timeBeforeNewCount = 0;
unsigned long updateTime = 0;

float lengthInMilliMeters; // length descirbed in millimeters

//total lengths and counts for averaging speed
unsigned long totalLength = 0;
unsigned long totalCounts = 0;

//counter used for calculations of average speed
int counter = 0;

//actual speed
int speedInCmPerSec = 0;

// variables used to calculate average, max and speed over 70 % 
int timeOverSeventyPercent = 0;
int maxSpeed = 0;
int averageSpeed = 0;
int totalSpeed = 0;
const int seventySpeed = 45.5; // maximum speed according to datasheet with 75:1 gear is 65cm/s. 65*0.7 = 45.5 cm/s 

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  int speedometer();

  //runs every 60 sec
  if (millis() - updateTime > 60000){
  sixtySecUpdate();
  }
}

// calculates speed in cm/s and updates values for:
// totalCounts, totalSpeed, totalLength
int speedometer(){
  timeBeforeNewCount = millis() - timeAfterLastCount; // setting time before getting and resetting encoders
  newCounts = ((encoders.getCountsAndResetLeft()+encoders.getCountsAndResetRight())/2)-lastCounts; //average encoder numbers for both motors
  lengthInMilliMeters = newCounts * milliMetersPerCount; // encoders converted to length in millimeters
  speedInCmPerSec = (lengthInMilliMeters/10)/(millis()*1000); // calculate speed from millimeters and millis()

  //updating total values for later calculations
  totalSpeed += speedInCmPerSec;
  totalLength += lengthInMilliMeters;
  totalCounts += newCounts;

  // saving millis and encoder values for next time
  lastCounts = newCounts;
  timeAfterLastCount = timeBeforeNewCount;

  // this saves time that the speed is over 70% of max
  if (speedInCmPerSec > seventySpeed){
  timeOverSeventyPercent += timeBeforeNewCount/1000; // divide by 1000 to go from millis to sec
  }
  return speedInCmPerSec;
}



// this function gives average speed, max speed and time spent over 70% of max speed
// this function will run every 60 sec
int sixtySecUpdate(){
  updateTime = millis(); // saving new time for next 60 sec run through
  averageSpeed = totalSpeed / counter; // calculating average

  //reset values to get new numbers for next 60 sec cycle
  counter = 0;
  totalSpeed = 0;
  timeOverSeventyPercent = 0; 
}

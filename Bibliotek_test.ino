#include <Wire.h>
#include <Zumo32U4.h>
#include "speed_controls.h"
Zumo32U4Encoders encoders;
speed_controls test;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 int lastCounts;
 int newCounts = ((encoders.getCountsAndResetLeft()+encoders.getCountsAndResetRight())/2)-lastCounts; //average encoder numbers for both motors
 Serial.println(test.speedometer(newCounts, lastCounts));
 Serial.println(test.totalLength(newCounts));

if (test.speedometer(newCounts, lastCounts) > 0){
  newTime = millis() - lastTime
  lastTime = newTime
}

if (lastTime > 60000){
  averageSpeed = (test.totalLength / 6000)
  topSpeed = test.speedometer(newCounts, lastCounts);
}

}

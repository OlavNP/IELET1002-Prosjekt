#include "speed_controls.h"
speed_controls::speed_controls(){
  
}
int speed_controls::speedometer(int counts, int lastCounts){
  timeBeforeNewCount = millis() - timeAfterLastCount; // setting time before getting and resetting encoders
  lengthInMilliMeters = counts * milliMetersPerCount; // encoders converted to length in millimeters
  speedInCmPerSec = (lengthInMilliMeters/10)/(millis()*1000); // calculate speed from millimeters and millis()

  // saving millis and encoder values for next time
  lastCounts = counts;
  timeAfterLastCount = timeBeforeNewCount;
 
  return speedInCmPerSec;
}

int speed_controls::total_distance(int counts){
  totalLength += counts * milliMetersPerCount;
  return totalLength;
}

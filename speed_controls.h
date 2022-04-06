#pragma once
#include <Arduino.h>


class speed_controls {
  public:
  speed_controls();
  int speedometer(int counts, int lastCounts);
  int total_distance(int counts);
  private:
    // 909.7 counts per revolution, wheel diameter = 122.52211349
    //millimetersPerCount = 122.52211349/909.7 = 0.1346840865
    const float milliMetersPerCount = 0.1346840865;

    // variables for millis()
    unsigned long timeAfterLastCount = 0;
    unsigned long timeBeforeNewCount = 0;
    unsigned long updateTime = 0;

    float lengthInMilliMeters; // length descirbed in millimeters
    int speedInCmPerSec = 0; // value read from speedometer

    // variables used to calculate average, max and speed over 70 %
    const int seventySpeed = 45.5; // maximum speed according to datasheet with 75:1 gear is 65cm/s. 65*0.7 = 45.5 cm/s

    int totalLength;

};

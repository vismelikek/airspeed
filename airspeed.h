#ifndef AIRSPEED_H
#define AIRSPEED_H

#include <Wire.h>  
#include <Arduino.h>

#endif

class AIRSPEED {
  public:
    AIRSPEED();
    byte fetchPressure(unsigned int *p_P_dat);
    float AS();

  private:
    byte address;
    float initial_PR;
    float k;
};


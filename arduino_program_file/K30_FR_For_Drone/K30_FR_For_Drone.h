#ifndef K30_FR_For_Drone_h
#define K30_FR_For_Drone_h
#include "Arduino.h"
#include "Wire.h"

class K30_FR_For_Drone{
  int address;
  int retryCount;
  public:
  K30_FR_For_Drone(int _address);
  int errorCheck(int &eroorCode);
  bool abcSetup(int hour); 
  int read(int &CO2level);
}

#endif
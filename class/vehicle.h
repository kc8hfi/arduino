#ifndef vehicle_h
#define vehicle_h

#include "Arduino.h"  //so we have access to all the standard types and constants in the arduino language

class vehicle
{
public:
     vehicle(String color, String engine);
     String getColor();
     String getEngine();
     int getCylinders();
     
     void setColor(String c);
     void setEngine(String e);
     void setCylinders(int c);
     
private:
     String color;
     String engine;
     int cylinders;
};


#endif

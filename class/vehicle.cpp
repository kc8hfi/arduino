#include "Arduino.h"  //so we have access to all the standard types and constants in the arduino language
#include "vehicle.h"


vehicle::vehicle(String c, String e)
{
     color = c;
     engine = e;
}

String vehicle::getColor()
{
     return color;
}

String vehicle::getEngine()
{
     return engine;
}

int vehicle::getCylinders()
{
     return cylinders;
}

void vehicle::setColor(String c)
{
     color = c;
}

void vehicle::setEngine(String e)
{
     engine = e;
}

void vehicle::setCylinders(int c)
{
     cylinders = c;
}

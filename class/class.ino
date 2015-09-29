#include "vehicle.h"

vehicle one("red","2.8 liter");
vehicle two("black","383 stroker");

void setup()
{
     Serial.begin(115200);
     
     Serial.println("vehicle one's color is " + one.getColor());
     
     Serial.println("vehicle two's engine is " + two.getEngine());
}
     
void loop()
{
}


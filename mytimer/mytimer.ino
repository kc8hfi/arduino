/*
our very own timer sketch
demonstrates how an event can be executed after a given time has expired

millis() = returns the time in milliseconds since the arduino started running the program

After 50 days of running time,  the millis will return to 0
*/

unsigned long theTime;

void setup()
{
     Serial.begin(115200);
     
     //initialize the time
     theTime = millis();
}

void loop ()
{
     //Serial.println("start: " + String(theTime));
     //Serial.println("now: " + String(millis()));
     
     if ( (millis() - theTime)/1000 == 2)
     {
          theTime = millis();
          myEvent();
     }
}


void myEvent()
{
     Serial.println("I'm supposed to be printed every 2 seconds");
}
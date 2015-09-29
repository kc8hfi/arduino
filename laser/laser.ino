/*
 * turn on the laser
 * keyes model,  labeled S,(no name),-
 * hook the ground to the -, nothing on the middle, and S to a pin
 */

byte laser = 2;
bool stringComplete = false;
String inputString;

void setup()
{
     Serial.begin(115200);
     
     pinMode(laser, OUTPUT);
     
     //make sure the laser is off
     digitalWrite(laser,LOW);
     
     Serial.println("1 toggles the laser");
}
void loop()
{
     if (stringComplete)
     {
          if(inputString.equals("1"))
          {
               
               dolaserstuff();
          }
          stringComplete = false;
          inputString = "";
     }
}

void dolaserstuff()
{
     digitalWrite(laser,!digitalRead(laser));
}

void serialEvent()
{
     while(Serial.available())
     {
          char inChar = (char)Serial.read();
          if(inChar == '\n')
               stringComplete = true;
          else
               inputString += inChar;     
     }
}

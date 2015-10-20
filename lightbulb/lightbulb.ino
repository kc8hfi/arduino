/* 
 * The relay
 * COM - incoming outside power source
 * NO - outgoing outside power source
 * 
 */

String inputString;
boolean stringComplete;

const int relay = 6;

void setup()
{
     Serial.begin(9600);
     inputString = "";
     stringComplete = false;
     
     //set up the relay pin
     pinMode(relay,OUTPUT);
     digitalWrite(relay,LOW);
     
     Serial.println("arduino ready");
}

void loop()
{
     if(stringComplete)
     {
          if (inputString == "light")
          {
               digitalWrite(relay,!digitalRead(relay));
          }
          else
          {
               Serial.println("you said \"" + inputString+ "\"");
          }
          
          inputString = "";
          stringComplete = false;
     }
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
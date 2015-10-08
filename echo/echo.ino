
String inputString;
boolean stringComplete;

void setup()
{
     Serial.begin(9600);
     inputString = "";
     stringComplete = false;
     Serial.println("arduino ready");
}

void loop()
{
     if(stringComplete)
     {
          Serial.println("you said: " + inputString);
          
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


<<<<<<< HEAD

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

=======

String inputString;
boolean stringComplete;

void setup()
{
     Serial.begin(9600);
     inputString = "";
     stringComplete = false;
     
     //turn off the led
     pinMode(13,OUTPUT);
     digitalWrite(13,LOW);
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

>>>>>>> b97d0cd76ed4dd9a13f641031ba5938145e6e0eb

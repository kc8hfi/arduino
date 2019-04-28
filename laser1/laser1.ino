String inputString = "";
boolean stringComplete = false;

void setup() {
  // put your setup code here, to run once:
  
   pinMode(7,OUTPUT);
   digitalWrite(7,LOW); 
   Serial.begin(9600);
   Serial.println("arduino is ready");
}

void loop() {
   // put your main code here, to run repeatedly:
    //digitalWrite(7, !digitalRead(7));
   if(stringComplete)
   {
     if(inputString == "on")
     {
       digitalWrite(7,HIGH);
     }
     else if (inputString == "off")
     {
       digitalWrite(7,LOW);
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

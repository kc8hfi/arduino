void setup()
{
     Serial.begin(115200);
     
     int value1 = 10;
     int value2 = 20;
     if(value1 < value2)
     {
          Serial.println( String(value1) + " is less than " + String(value2));
     }
          
}

void loop()
{
}
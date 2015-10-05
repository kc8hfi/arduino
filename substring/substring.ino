void setup()
{
     Serial.begin(115200);
     String myString = "this is a big string";     
     Serial.println(myString.substring(0,4));
     
     //this will start at position 5 and go to the end
     Serial.println(myString.substring(5));
     
     
     
     //seed generator
     randomSeed(analogRead(2));
     
     long number1 = random(); //number between -2 and 2 billion
     
     //number between 0 and 50
     long number2 = random (0,51);
     
     
     
     //if you want sequence to be the same
     randomSeed(10);    
     long number2 = random();
     
     random();
}

void loop()
{
}

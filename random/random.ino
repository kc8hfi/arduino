void setup()
{
     Serial.begin(115200);
     
     randomSeed(analogRead(2));
}

void loop()
{
     myfunc();
     
}


void myfunc()
{
     long number = random(0,10);
     Serial.println(String(number));

}
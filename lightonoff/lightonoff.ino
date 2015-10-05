/*
on - turns the light on
anything else will turn the light off
*/


//string to hold the incoming stuff
String incoming = "";  

//whether or not the string is complete yet
boolean completestring = false;   

//the light is on pin 13
int light = 13;

void setup()
{
  Serial.begin(115200);  //set the port speed, default to 8 data bits, no parity, 1 stop bit
  pinMode(light,OUTPUT);
}

void loop()
{
  //check to see if we have a complete string yet
  if(completestring)
  {
    //repeat back out the entire completed string
    if (incoming == "on")
    {
      //turn the light on
      digitalWrite(light,HIGH);
    }
    else
    {
      //turn the light off, anything other than the word on will turn it off
      digitalWrite(light,LOW);
    }
    Serial.println(incoming);
    //clear the string now
    incoming = "";
    //completestring is now false
    completestring = false;
  }
}

//this gets called after the loop has executed, and if there
//is serial data in the buffer
void serialEvent()
{
  while(Serial.available() > 0)
  {
    char inchar = (char)Serial.read();
    //check to see if we get a newline, if so, the string is 
    //complete and its time for the loop() to do something
    //but don't add the \n to the string
    if (inchar == '\n')
    {
      completestring = true;
    }
    //otherwise, add the incoming character to the string
    else
    {
      incoming = incoming + inchar;
    }
  }
}

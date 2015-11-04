/*
 * relay:
 * COM = bat +
 * NO  = to the motor +
 * 
 * motor - = bat - 
*/

//string to hold the incoming stuff
String incoming = "";  

//whether or not the string is complete yet
boolean completestring = false;   

//the light is on pin 13
byte light = 13;
byte left = 7;
byte right = 6;
byte forward = 0;

void setup()
{
     Serial.begin(115200);  //set the port speed, default to 8 data bits, no parity, 1 stop bit
     pinMode(light,OUTPUT);
     pinMode(left,OUTPUT);
     pinMode(right,OUTPUT);
     
     //turn off the light
     digitalWrite(light,LOW);
     
     Serial.println("arduino ready");
}

/*
 * bvf - go forward
 * evf - end forward
 * bvl - go left
 * evl - end left
 * bvr - go right
 * evr - end right
 */

void loop()
{
     //check to see if we have a complete string yet
     if(completestring)
     {
          //repeat back out the entire completed string
          if (incoming == "bvf")
          {
               //turn the relay on
               digitalWrite(left,HIGH);
               digitalWrite(right,HIGH);
               forward = 1;
          }
          else if (incoming == "evf")
          {
               digitalWrite(left,LOW);
               digitalWrite(right,LOW);
               forward = 0;
          }
          else if (incoming == "bvl")
          {
               if (forward == 1)
               {
                    digitalWrite(left,LOW);
               }
               else
               {
                    digitalWrite(right,HIGH);
               }
          }
          else if (incoming == "evl")
          {
               if (forward == 1)
               {
                    digitalWrite(left,HIGH);
               }
               else
               {
                    digitalWrite(right,LOW);
               }
          }
          else if(incoming == "bvr")
          {
               if (forward == 1)
               {
                    digitalWrite(right,LOW);
               }
               else
               {
                    digitalWrite(left,HIGH);
               }
          }
          else if(incoming == "evr")
          {
               if (forward == 1)
               {
                    digitalWrite(right,HIGH);
               }
               else
               {
                    digitalWrite(left,LOW);
               }
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
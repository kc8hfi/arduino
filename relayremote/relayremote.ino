/*
tsop4838 ir sensor

pioneer car stereo remote model cxc3173
and cxc1265

volume down    3747631068
volume up 552493270
B    1476375678
ATT  3026238454
up   1938763546
left 414219326
right     2893538684
down 617239776
F    2452411324
A    2813070852
cd   1429926878
pause     2727811706
stereo    48774522


*/

/*
 * wiring:
 * ir receiver, put the round thing towards you, the pins are:
 * signal, ground, 3.3Volts   NOT 5v power!!!!!
 * 
 * signal pin 7
 */

#include <IRremote.h> 


const int red = 10;
const int green = 9;
const int blue = 8;

const int relay = 6;

const int irReceiverPin = 7; 
const int ledPin = 13;
IRrecv irrecv(irReceiverPin); //create an IRrecv object
decode_results decodedSignal; //stores results from IR sensor

boolean lightState = false; //keep track of whether the LED is on
unsigned long last = millis(); //remember when we last received an IRmessage

 
void setup()
{
     pinMode(red, OUTPUT);     
     pinMode(green, OUTPUT);
     pinMode(blue, OUTPUT); 
     pinMode(relay, OUTPUT);


     pinMode(ledPin, OUTPUT);
     irrecv.enableIRIn(); // Start the receiver object

     Serial.begin(115200);

}
void loop()
{
     if (irrecv.decode(&decodedSignal) == true) //this is true if a message has been received
     {
          //if (millis() - last > 250)
          if (millis() - last > 250)
          { //has it been 1 sec since last message
               Serial.println(decodedSignal.value);
               doSomething(decodedSignal.value);
               //lightState = !lightState; //toggle the LED
               //digitalWrite(ledPin, lightState);
          }
          last = millis();
          irrecv.resume(); // watch out for another message
     }
}


void doSomething(unsigned long value)
{
     switch(value)
     {
          //cd   1429926878
          //turn on/off red
          case 414219326:
               if (digitalRead(red) ) //high
               {
                    digitalWrite(red, LOW);
               }
               else
               {
                    digitalWrite(red,HIGH);
               }
          break;
          //turn on/off green
          case 1938763546:
               if (digitalRead(green) ) //high
               {
                    digitalWrite(green, LOW);
               }
               else
               {
                    digitalWrite(green,HIGH);
               }
          break;
          //turn on/off blue
          case 2893538684:
               if (digitalRead(blue) ) //high
               {
                    digitalWrite(blue, LOW);
               }
               else
               {
                    digitalWrite(blue,HIGH);
               }
          break;
          case 617239776:
               if (digitalRead(relay) ) //high
               {
                    digitalWrite(relay, LOW);
               }
               else
               {
                    digitalWrite(relay,HIGH);
               }
          break;
          
          default:
          break;
     }
}//end doSomething
/*
 * adsfadsf
 * 
 * asdfasefd
 * 
tsop4838 ir sensor

pioneer car stereo remote model cxc3173

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

cxc1265 emits these codes

volume down 3041579055
volume up 3430204583
B 3041544375
ATT 3041538255
up 3041526525
left 3041542845
right 3041575485
down 3041559165
F 3041564775
A 3041570895
cd 3041556615
pause 3041532645
stereo 3041540295

*/

/*
 * wiring:
 * ir receiver, put the round thing towards you, the pins are:
 * signal, ground, 3.3Volts   NOT 5v power!!!!!
 * 
 * signal -  pin 7
 * ground - ground pin
 * 3.3volts - into 3.3 volts power
 * 
 * the 3 led module
 * it's labeled RGB on the back, the R and B are reversed
 * R - blue light, pin 8
 * G - green light, pin 9
 * B - red light, pin 10
 * 
 * 
 * The relay
 * COM - incoming outside power source
 * NO - outgoing outside power source
 * 
 */

#include <IRremote.h>

String inputString;
boolean stringComplete;

const int red = 10;
const int green = 9;
const int blue = 8;

const int relay = 6;
const byte outlet = 5;

const int irReceiverPin = 7; 
const int ledPin = 13;

IRrecv irrecv(irReceiverPin); //create an IRrecv object
decode_results decodedSignal; //stores results from IR sensor
unsigned long last = millis(); //remember when we last received an IRmessage

String sendme;

void setup()
{
     Serial.begin(9600);
     inputString = "";
     sendme = "";
     stringComplete = false;
     
     //turn off all the lights
     pinMode(ledPin,OUTPUT);
     pinMode(red,OUTPUT);
     pinMode(green,OUTPUT);
     pinMode(blue,OUTPUT);
     digitalWrite(ledPin,LOW);
     digitalWrite(red,LOW);
     digitalWrite(green,LOW);
     digitalWrite(blue,LOW);

     //set up the relay pin
     pinMode(relay,OUTPUT);
     digitalWrite(relay,LOW);
     
     //set up the outlet pin
     pinMode(outlet,OUTPUT);
     digitalWrite(outlet,LOW);
     
     irrecv.enableIRIn(); // Start the receiver object
     
     Serial.println("arduino ready");
}

void loop()
{
     if (irrecv.decode(&decodedSignal) == true) //this is true if a message has been received
     {
          //if (millis() - last > 250)
          if (millis() - last > 250)
          { //has it been 1 sec since last message
               sendme += ((String)decodedSignal.value) + ":";
               remoteHandler(decodedSignal.value);
               //lightState = !lightState; //toggle the LED
               //digitalWrite(ledPin, lightState);
          }
          last = millis();
          irrecv.resume(); // watch out for another message
     }
     
     if(stringComplete)
     {
          if(inputString == "orange")
          {
               digitalWrite(ledPin,!digitalRead(ledPin));
               //Serial.println(inputString);
          }
          else if(inputString == "red")
          {
               digitalWrite(red,!digitalRead(red));
               //Serial.println(inputString);
          }
          else if (inputString == "green")
          {
               digitalWrite(green,!digitalRead(green));
               //Serial.println(inputString);
          }
          else if (inputString == "blue")
          {
               digitalWrite(blue,!digitalRead(blue));
               //Serial.println(inputString);
          }
          else if (inputString == "light")
          {
               digitalWrite(relay,!digitalRead(relay));
          }
          else if (inputString == "outlet")
          {
               digitalWrite(outlet, !digitalRead(outlet));
          }
          else 
          {
               Serial.println("you said \"" + inputString+ "\"");
          }
          
          inputString = "";
          stringComplete = false;
     }
}

void remoteHandler(unsigned long value)
{  remoteHandler(decodedSignal.value);
     switch(value)
     {
          //cd   1429926878
          //turn on/off red
          case 3041542845:
//           case 9770670:
               digitalWrite(red,!digitalRead(red));
               //Serial.println("redir");
               sendme += "redir";
          break;
          //turn on/off green
          case 3041526525:
               digitalWrite(green,!digitalRead(green));
               //Serial.println("greenir");
               sendme += "greenir";
          break;
          //turn on/off blue
          case 3041575485:
               digitalWrite(blue,!digitalRead(blue));
               //Serial.println("blueir");
               sendme += "blueir";
          break;
          case 3041559165:
               digitalWrite(ledPin,!digitalRead(ledPin));
               //Serial.println("orangeir");
               sendme += "orangeir";
          break;
          case 3041544375:
               digitalWrite(relay,!digitalRead(relay));
               sendme += "relay";
          break;
          case 3041538255:
               digitalWrite(outlet, !digitalRead(outlet));
               sendme += "outlet";
          break;
          default:
               sendme += "not defined";
          break;
     }
     Serial.println(sendme);
     sendme = "";
}//end doSomething

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

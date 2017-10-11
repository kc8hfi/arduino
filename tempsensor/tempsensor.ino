#include <Wire.h>
#include <Adafruit_BMP085.h>

byte light = 13;
Adafruit_BMP085 bmp;

double temperature = 0.0;
boolean timer = false;

void setup()
{
     Serial.begin(9600);

     if (!bmp.begin())
     {
          Serial.println("Could not find a valid BMP085 sensor, check wiring!");
          while (1) {}
     }

     /*
      * compare match register values
      * 1 second  = 15625
      * 2 seconds = 31250
      * 4 seconds = 62500
      * prescalar, 1,8,64,256,1024
      
      * [16 million/(time in hz)(prescalar)] -1
      */

     //stop all the interrupts
     cli();
     
     //use timer1 to interrupt every second,  1hz
     TCCR1A = 0;    //sets the entire register to 0
     TCCR1B = 0;    //sets the entire register to 0
     TCNT1 = 0;     //set the initial counter value to 0
     OCR1A = 15625; //set the compare match register value
     TCCR1B |= (1<<WGM12);  //turns on the clear timer on compare match (CTC mode)
     TCCR1B |= (1<<CS12) | (1<<CS10);  //set CS10 and CS12 bits for a 1024 prescaler
     TIMSK1 |= (1<< OCIE1A);  //enables the timer compare interrupt
     
     //re-enable the interrupts
     sei();
}


//the interrupt service request for the Timer1 interrupt
ISR(TIMER1_COMPA_vect)
{
     timer += 1;  //since the timer goes off every second,  add one to the timer
}

void loop()
{

     if (timer == 1)//if its been one second,  get the temp and print it out
     {
          temperature = bmp.readTemperature();          
          double t = (temperature * 9.0)/5.0 + 32.0;
          Serial.println("temp in *F: " + String(t));
          timer = 0;
     }
}

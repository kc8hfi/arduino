/*
 * hall effect sensor on the front wheel
 * black - 14 orange - ground
 * blue - 13 brown - signal, pin 2
 * red - 15 yellow - +5vdc
 * 
 * diameter of the wheel - 16.5 inches
 * circumference - 51.83627 inches
 * 7 magnets, evenly spaced, 7.40518 inches apart
 */

#define hall_effect_interrupt_num   0           //Pin for hall effect interrupt
#define hall_effect_pin   2                     //Pin the hall effect sensor wire is connected to 
#define ledPin 13

volatile int ticks = 0;                         //Counts the number of ticks per revolution
volatile int revolutions = 0;                   //Counts the number of revolutions of the wheel
int hallState = 0;                              //reading sensor status

void setup()
{
     // Open the serial connection,
     Serial.begin(9600);
     
     //enable the built in pullup resistor
     pinMode(hall_effect_pin,INPUT_PULLUP);
     digitalWrite(hall_effect_pin,HIGH);
     
     //set the led pin so we can turn the light on/off
     pinMode(ledPin, OUTPUT);     
     
     //3rd parameter defines what triggers the interrupt. Falling indicates that a voltage drop fires the interrupt
     attachInterrupt(digitalPinToInterrupt(hall_effect_pin),tickhandler,FALLING);    
     
     Serial.println("Arduino now ready!");
}

void loop()
{
}

void tickhandler()
{
     ticks++;
     if (ticks >7)
     {
          ticks = 0;
          revolutions++;
     }
     digitalWrite(ledPin, !digitalRead(ledPin) );                   //Visual inidcator that the tickhandler has fired
}

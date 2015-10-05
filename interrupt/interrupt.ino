//used for a sensor 
volatile int counter = 0;
 
void setup()
{
     Serial.begin(115200);
     
     //modes to look for
     //LOW - when the pin is LOW
     //CHANGE - when the pin changes value
     //RISING - when the pin goes from low to high
     //FALLING - when pin goes high to low
     
     attachInterrupt( 2,  myInterrupt, LOW    );
     
}


void loop()
{
     Serial.println("i'm printing now");

     Serial.println("the counter is: " + String(counter));
     
}



void myInterrupt()
{
     counter++;
     
     
}

byte light = 13;
 
void setup()
{
     Serial.begin(115200);
     
     pinMode(light,OUTPUT);
     //make sure the light is off
     digitalWrite(light, LOW);
     
     
     //stop all the interrupts
     cli();
     
     //use timer1 to interrupt every second,  1hz
     TCCR1A = 0;    //sets the entire register to 0
     TCCR1B = 0;    //sets the entire register to 0
     TCNT1 = 0;     //set the initial counter value to 0
     OCR1A = 15624; //set the compare match register value
     TCCR1B |= (1<<WGM12);  //turns on the clear timer on compare match (CTC mode)
     TCCR1B |= (1<<CS12) | (1<<CS10);  //set CS10 and CS12 bits for a 1024 prescaler
     TIMSK1 |= (1<< OCIE1A);  //enables the timer compare interrupt
     
     //re-enable the interrupts
     sei();
}


//the interrupt service request for the Timer1 interrupt
ISR(TIMER1_COMPA_vect)
{
     Serial.println("timer went off, toggle the light");
     digitalWrite(light,!digitalRead(light));
}

void loop()
{
     
}
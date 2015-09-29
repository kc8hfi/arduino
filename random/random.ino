/*
random () - function that generates random numbers
random (max value ) - upper bound, doesn't include this number
random (min value, max value) - lower bound, including,  upper bound, not including

can seed it, with randomSeed() and some number,  fixed number will make it generate a 
sequence the same as before
seed it with like an analogread from a pin that isn't connect
randomSeed(analogRead(1))
*/
 
void setup()
{
     Serial.begin(115200);
     
     //seed the number generator, with whatever signal is coming from analog pin 0
     //electrical noise is always a good seeder
     randomSeed( analogRead(0) ); 
}

void loop()
{
     //random() = generates a random number between -2,147,483,648 to 2,147,483,648
     long randomNumber = random();
     Serial.println(String(randomNumber));
     delay(2000);
     
     
     //random(min,max) = generate a random number between 1 and 4,    5 is not included
     //if you want a random number between 1 and 5, including 1 and 5,  set the range to 1,6
     randomNumber = random(1,5);  
     Serial.println(String(randomNumber));
     delay(2000);
     
     //random(min) = generate random number 
     randomNumber = random(10);
     Serial.println(String(randomNumber));
     delay(2000);
     
     
     Serial.println("again");
     
}
// the setup routine runs once when you press reset:

int red = 8;
int green = 9;
int blue = 10;

void setup() 
{ 
     pinMode(red, OUTPUT);     
     pinMode(green, OUTPUT);
     pinMode(blue, OUTPUT);  
}


void loop() 
{
     Serial.println("red");
     digitalWrite(red, HIGH);
     delay(500);
     digitalWrite(red, LOW);
     
     Serial.println("green");
     digitalWrite(green, HIGH);
     delay(500);
     digitalWrite(green, LOW);
     
     Serial.println("blue");
     digitalWrite(blue, HIGH);
     delay(500);
     digitalWrite(blue, LOW);
}

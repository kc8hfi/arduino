/*
 * switch statements can only switch on numbers and character constants
 */ 
 
void setup()
{
     Serial.begin(115200);
     
     int y = 10;
     switch (y)
     {
          case 10:
               Serial.println("y is: " + String(y));
          break;
          default:
          break;
     }
     
     char z = 'a';
     switch (z)
     {
          case 'a':
               Serial.println("z is " + String(z));
          break;
          default:
          break;
     }
}

void loop()
{
}
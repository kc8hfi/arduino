#include <Wire.h>
#include <Adafruit_BMP085.h>

/*************************************************** 
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/391

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here


/*
 * if you try and block the loop, this is what happens
 */

Adafruit_BMP085 bmp;
void setup()
{
     Serial.begin(9600);
     if (!bmp.begin())
     {
          Serial.println("Could not find a valid BMP085 sensor, check wiring!");
          while (1) {}
     }
     Serial.println("arduino ready");
}
  
void loop()
{
     
     float celcius = bmp.readTemperature();
//      Serial.print("*C: ");
//      Serial.println(celcius);


     //convert to F
     float f = (celcius * 9.0)/ 5.0 + 32.0;
     Serial.print("in *F: ");
     Serial.println(f);
     
     if (f < 80.0)
     {
          Serial.println("turn off the ac!");
     }
     else
     {
          Serial.println("turn on the ac!");
     }
     
     Serial.println("We are going to wait here forever until we get some serial data");
     Serial.println("This is bad, because the temperature keeps going up.");
     Serial.println("The code doesn't know that the temperature is going up");
     Serial.println("because we are stuck here waitin on serial data");
     while(!Serial.available());
     
     String s = Serial.readStringUntil('\n');
     //do something with the incoming string
     Serial.println("you said: " + s);

}
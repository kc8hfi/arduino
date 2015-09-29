void setup()
{
     Serial.begin(115200);
     
     Serial.println("byte: " + String(sizeof(byte)));
     Serial.println("int: " + String(sizeof(int)));
     Serial.println("double: " + String (sizeof(double)));
     Serial.println("float: " + String (sizeof(float)));
     Serial.println("string: " + String (sizeof(String)));
     Serial.println("char: " + String( sizeof(char)));
     
     
     //float - only have 6-7 numbers,   doesnt matter how many numbers after the decimal
     // place either,   its still 6-7 total numbers
     
     //double - pretty much the same as a float
}

void loop()
{
 
}

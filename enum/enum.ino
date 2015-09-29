/*
 * enum types - set of named constants
 */

//create one
enum colors {red,blue,black};

enum trucks {s10,silverado,ram};

void setup()
{
     Serial.begin(115200);
     
     colors mycolor = blue;
     
     
     Serial.println(mycolor);
     
}

void loop()
{
}
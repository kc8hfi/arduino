
String stuff[] = {"hello","greetings","howdy"};

int numbers[4] = {42,73,17,19};

int test[5] = {1,2,3};

void setup()
{
     Serial.begin(115200);
     
     //sizeof returns the size in bytes
     Serial.println("size of stuff: " + String(sizeof(stuff)/sizeof(String)));
     
     Serial.println("size of numbers: " + String(sizeof(numbers)/sizeof(int)));
     
     //Serial.println(stuff[10]);
     
     for(int i=0;i<sizeof(stuff)/sizeof(String);i++)
     {
     }
}

void loop()
{
}
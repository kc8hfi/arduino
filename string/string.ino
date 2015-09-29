void setup()
{
     Serial.begin(115200);
     
     for(int i=0;i<5; i++)
     {
          Serial.println(String(i));
     }
     
     
     myfunction();
     
     
     
     //or the compareTo() function
     /*
      * evaluates on the first character that's different.  if that character comes first 
      * in alphanumeric order,  this function will be greater than 0
      * 
      */
     
     String mystring = "rickjames";
     String str2 = "rickspringfield";
     
     if (mystring.compareTo(str2) < 0)
          Serial.println(mystring + " comes before " + str2);
  
}

void loop ()
{
     
}



void myfunction()
{
          String mystring = "hello";
     String str2 = "";
  
     //concatenate another string
     mystring = mystring + " world";
     Serial.println(mystring);

     //or like
     mystring = String(mystring + " yaar!");
     Serial.println(mystring);

     //concatenate an int
     mystring = mystring + String(12);
     Serial.println(mystring);
     
     //check equality
     str2 = "something";
     if (mystring == str2)
     {
          Serial.println(mystring = " is something");
     }
     
     //or by using the equals()function
     mystring = "something";
     if (mystring.equals(str2))
     {
          Serial.println("mystring is equal to str2");
     }
}

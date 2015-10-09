/*
Programming assignment #1

The menu:
1.  Add a fortune
2.  Display a random fortune
3.  Toggle the onboard led
4.  Print all the available fortunes
5.  Count to 10
6.  Say “Hello” to your arduino

Output
option 1 – lets the user type in a string of characters that represents a fortune.  This string of characters will get added to an array

option 2 – randomly selects a fortune from the list and prints it out.  If there are no fortunes available, print out “Sorry the fortune teller isn't in right now”

option 3 – make the led light change its current state.  If its off, turn it on and then print out “The light is on!”.  If the light is on, turn it off and print out “The light is off!”.

4.  print out all the fortunes one per line.  For example,  if the list contains 4 things,  print them one per line, surrounded by quotes.  (the arduino is telling us the fortune, so we want to quote it)
“Don't get mad – get even”
“Cheap, fast and reliable.  Pick two”,
”A bug in the code is worth two in the documentation.”
“There's no replacement for displacement”

5.  count from 1 to 10,   print the numbers out separated by a comma,  e.g.  1,2,3,4..........10.  Don't print a comma after the last number.

6.  the arduino should respond with a nice greeting,  such as “Greetings!” or  “Yaaar!” or “Weeeee!”. 

*/




byte light = 13;
String inputString;
boolean stringComplete;
//String stuff[] = {"There's no replacement for displacement","Git r done!","Silly rabbit, trix are for kids"};
String stuff[10];
int whichspot = 0;

boolean adding = false;
int lastChoice;

void setup()
{
     Serial.begin(115200);
     pinMode(light,OUTPUT);
     //make sure the light is off
     digitalWrite(light,LOW);

     //seed the random number generator
     randomSeed(analogRead(0));
     
     menu ();
}

void loop()
{
     if (stringComplete)
     {
          //Serial.println(inputString);
          int value;
          if (lastChoice == 1)
          {
               value = 0;
          }
          else
          {
               value = inputString.toInt();
          };
          String numbers = "";
          switch(value)
          {
               case 1:
                    Serial.println("Type the fortune to be added:");
               break;
               case 2:
                    Serial.println("");
                    Serial.println(stuff[random(0,3)]);
               break;
               case 3:
                    digitalWrite(light,!digitalRead(light));
               break;
               case 4:
                    Serial.println("");
                    for(int i=0;i< sizeof(stuff)/sizeof(String);i++)
                    {
                         Serial.println("\"" + stuff[i] +"\"");
                    }
               break;
               case 5:
                    Serial.println("");
                    
                    for (int i=1;i<=10;i++)
                    {
                         numbers += String(i) + ",";
                         //Serial.print( String(i) + ",");
                    }
                    numbers = numbers.substring(0,numbers.length()-1);
                    Serial.println(numbers);

               break;
               case 6:
                    Serial.print("\nGreetings!\n");
               break;
               default:
                    if (lastChoice == 1)
                    {
                         Serial.println("add " + inputString + " to the array");
                         stuff[whichspot] = inputString;
                         whichspot ++;
                         value = 0;
                    }
                    else
                    {
                         Serial.println(String(value) + " was not a valid choice, please try again!");
                    }
               break;
          }
          if (value !=  1)
               menu();
          //reset everything to start again
          lastChoice = value;
          stringComplete = false;
          inputString = "";
     }
}

void serialEvent()
{
     while (Serial.available())
     {
          // get the new byte:
          char inChar = (char)Serial.read(); 
          // add it to the inputString:
          if (inChar != '\n')
          {
               inputString += inChar;
          }
          else
          {
               stringComplete = true;
          }
     }
}

void menu()
{
     Serial.println("");
     Serial.println("Pick a choice from the menu");
     Serial.println("1.  Add a fortune");
     Serial.println("2.  Display a random fortune");
     Serial.println("3.  Toggle the onboard led");
     Serial.println("4.  print all the available fortunes");
     Serial.println("5.  Count to 10");
     Serial.println("6.  Say 'Hello' to your arduino");
}

// byte light = 13;
// String inputString;
// boolean stringComplete;
// String stuff[] = {"There's no replacement for displacement","Git r done!","Silly rabbit, trix are for kids"};
// 
// void setup()
// {
//      Serial.begin(115200);
//      pinMode(light,OUTPUT);
//      //make sure the light is off
//      //digitalWrite(light,LOW);
// 
//      Serial.println( String( sizeof(stuff) ) );
// 
//      String s = "";
//      Serial.println("empty string: " + String(sizeof(s)));
//      
//      s = "test";
//      Serial.println("4 chars: " + String(sizeof(s)));
//      
//      s = "a whole gang of characters in here";
//      Serial.println("more chars: " + String(sizeof(s)));
//      
//      Serial.println("size of a String: " + String(sizeof(String)));// + sizeof(String));
//      
//      menu ();
//      
// }
// 
// void loop()
// {
//      if (stringComplete)
//      {
//           //Serial.println(inputString);
//           int value = inputString.toInt();
//           switch(value)
//           {
//                case 1:
//                     digitalWrite(light,!digitalRead(light));
//                break;
//                case 2:
//                     Serial.println("");
//                     Serial.println(stuff[random(0,3)]);
//                break;
//                case 3:
//                     Serial.println("");
//                     for (int i=1;i<=5;i++)
//                     {
//                          Serial.print( String(i) + " ");
//                     }
//                     Serial.println("");
//                break;
//                default:
//                     Serial.println(String(value) + " was not a valid choice, please try again!");
//                break;
//                
//           }
//           menu();
//           //reset everything to start again
//           stringComplete = false;
//           inputString = "";
//      }
// }
// 
// void serialEvent()
// {
//      while (Serial.available())
//      {
//           // get the new byte:
//           char inChar = (char)Serial.read(); 
//           // add it to the inputString:
//           if (inChar != '\n')
//           {
//                inputString += inChar;
//           }
//           else
//           {
//                stringComplete = true;
//           }
//      }
// }
// 
// void menu()
// {
//      Serial.println("");
//      Serial.println("Pick a choice from the menu");
//      Serial.println("To toggle the light, press 1");
//      Serial.println("To get your fortune, press 2");
//      Serial.println("To get a list of the numbers from 1 to 5, press 3");
//      
//      
// }
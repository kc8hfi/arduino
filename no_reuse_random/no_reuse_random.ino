String inputString = "";
boolean stringComplete = false;

int numbers[10];
int count=0;

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(2));
  
  Serial.begin(9600);
  Serial.println("ready");

}

void loop() 
{
     // put your main code here, to run repeatedly:
     if(stringComplete)
     {
          if(inputString.equals("2"))
          {
               //Serial.println(String(random(0,10)));

               boolean newNumber = false;
               boolean isthere = false;
               do
               {
                    int r = random(0,10);
                    //is r in the array?
                    for(int i=0;i<=count;i++)
                    {
                         if (r == numbers[i])
                         {
                              isthere = true;
                              break;
                         }
                         else
                         {
                              isthere = false;
                         }
                    }
                    if(!isthere)
                    {
                         Serial.println("add " + String(r) + " to the array");
                         numbers[count] = r;
                         count++;
                         newNumber = true;
                    }
                    else
                    {
                         Serial.println(String(r) + " already there");
                    }
                    Serial.println("count: " + String(count));
                    if (count == 9)
                    {
                         newNumber = true;
                    }
               }while(newNumber == false);
          }
          if(inputString.equals("3"))
          {
               for(int i=0;i<=count;i++)
               {
                    Serial.print(String(numbers[i]) + ",");
               }
               Serial.println("");
          }
          stringComplete = false;
          inputString = "";
     }
  

}


void serialEvent()
{
     while(Serial.available())
     {
          char inChar = (char)Serial.read();
          if (inChar == '\n')
          {
               stringComplete = true;
          }
          else
          {
               inputString = inputString + inChar;
          }
     }
}


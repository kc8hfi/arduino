 
String alphabet = "abcdefghijklmnopqrstuvwxyz";

int dot = 500;
int dash = 1500;
int nextLetter = 1500;
int space = 500;
int nextWord = 3500;

int light = 13;
int ledModule = 7;

String inputString;
boolean stringComplete;

typedef struct 
{
     int size;
     int code[5];
     
} Code;

Code whichcode;
Code codes[26];

void setup()
{
     Serial.begin(9600);  
     pinMode(light, OUTPUT);
     pinMode(ledModule, OUTPUT);
     
     //make sure light is off 
     digitalWrite(light, LOW);
     digitalWrite(ledModule, LOW);
     
     Code a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
     
     a.size = 2;
     a.code[0] = dot;
     a.code[1] = dash;
     
     b.size = 4;
     b.code[0] = dash;
     b.code[1] = dot;
     b.code[2] = dot;
     b.code[3] = dot;
     
     c.size = 4;
     c.code[0] = dash;
     c.code[1] = dot;
     c.code[2] = dash;
     c.code[3] = dot;
     
     d.size = 3;
     d.code[0] = dash;
     d.code[1] = dot;
     d.code[2] = dot;
     
     e.size = 1;
     e.code[0] = dot;
     
     f.size = 4;
     f.code[0] = dot;
     f.code[1] = dot;
     f.code[2] = dash;
     f.code[3] = dot;
     
     g.size = 3;
     g.code[0] = dash;
     g.code[1] = dash;
     g.code[2] = dot;
     
     h.size = 4;
     h.code[0] = dot;
     h.code[1] = dot;
     h.code[2] = dot;
     h.code[3] = dot;
     
     i.size = 2;
     i.code[0] = dot;
     i.code[1] = dot;
     
     j.size = 4;
     j.code[0] = dot;
     j.code[1] = dash;
     j.code[2] = dash;
     j.code[3] = dash;
     
     k.size = 3;
     k.code[0] = dash;
     k.code[1] = dot;
     k.code[2] = dash;
     
     l.size = 4;
     l.code[0] = dot;
     l.code[1] = dash;
     l.code[2] = dot;
     l.code[3] = dot;
     
     m.size = 2;
     m.code[0] = dash;
     m.code[1] = dash;
     
     n.size = 2;
     n.code[0] = dash;
     n.code[1] = dot;
     
     o.size = 3;
     o.code[0] = dash;
     o.code[1] = dash;
     o.code[2] = dash;

     p.size = 4;
     p.code[0] = dot;
     p.code[1] = dash;
     p.code[2] = dash;
     p.code[3] = dot;

     q.size = 4;
     q.code[0] = dash;
     q.code[1] = dash;
     q.code[2] = dot;
     q.code[3] = dash;
     
     r.size = 3;
     r.code[0] = dot;
     r.code[1] = dash;
     r.code[2] = dot;

     s.size = 3;
     s.code[0] = dot;
     s.code[1] = dot;
     s.code[2] = dot;
     
     t.size = 1;
     t.code[0] = dash;
     
     u.size = 3;
     u.code[0] = dot;
     u.code[1] = dot;
     u.code[2] = dash;
     
     v.size = 4;
     v.code[0] = dot;
     v.code[1] = dot;
     v.code[2] = dot;
     v.code[3] = dash;
     
     w.size = 3;
     w.code[0] = dot;
     w.code[1] = dash;
     w.code[2] = dash;
     
     x.size = 4;
     x.code[0] = dash;
     x.code[1] = dot;
     x.code[2] = dot;
     x.code[3] = dash;
     
     y.size = 4;
     y.code[0] = dash;
     y.code[1] = dot;
     y.code[2] = dash;
     y.code[3] = dash;
     
     z.size = 4;
     z.code[0] = dash;
     z.code[1] = dash;
     z.code[2] = dot;
     z.code[3] = dot;
     
     //Code temp[26] = {a,b,c};//,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
     //*codes = temp;
     codes[0] = a;
     codes[1] = b;
     codes[2] = c;
     codes[3] = d;
     codes[4] = e;
     codes[5] = f;
     codes[6] = g;
     codes[7] = h;
     codes[8] = i;
     codes[9] = j;
     codes[10] = k;
     codes[11] = l;
     codes[12] = m;
     codes[13] = n;
     codes[14] = o;
     codes[15] = p;
     codes[16] = q;
     codes[17] = r;
     codes[18] = s;
     codes[19] = t;
     codes[20] = u;
     codes[21] = v;
     codes[22] = w;
     codes[23] = x;
     codes[24] = y;
     codes[25] = z;
     
     Serial.println("arduino ready");
     
}//end setup

void loop()
{
     if(stringComplete)
     {
          for(int i=0; i<inputString.length(); i++)
          {
               int index = alphabet.indexOf(inputString.charAt(i));
               whichcode = codes[index];
               for (int j=0; j< whichcode.size; j++)
               {
                    digitalWrite(light, HIGH);
                    digitalWrite(ledModule, HIGH);
                    delay(whichcode.code[j]);

                    digitalWrite(light, LOW);
                    digitalWrite(ledModule, LOW);
                    delay(space);
               }
               delay(nextLetter);
          }
          inputString = "";
          stringComplete = false;
     }
}//end loop

void serialEvent()
{
     while(Serial.available())
     {
          char inChar = (char)Serial.read();
          if(inChar == '\n')
               stringComplete = true;
          else
               inputString += inChar;     
     }
}

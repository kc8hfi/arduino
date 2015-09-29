/*
 * structs are user defined objects, collection of data
 * these are basically same as a class,  except the members are public
 */ 
 

//create an object
typedef struct
{
     String manufacturer;
     String name;
     String size;
     int diameter;
} tire;

void setup()
{
     Serial.begin(115200);
     
     tire one = { "bfg", "radial ta", "215/60x15",15 };

     tire two = {"kelley","safari tsr"};
     two.size = "31x10.5";
     two.diameter = 15;

     tire three;
     three.manufacturer = "general";
     three.name = "grabber";
     three.size = "33x12.5";
     three.diameter = 17;
     
     //create an array of tires
     tire mytires[] = {one,two,three};
     
    
     for(int i=0;i< sizeof(mytires)/sizeof(tire);i++)
     {
          Serial.println(mytires[i].manufacturer);
          Serial.println(mytires[i].name);
          Serial.println(mytires[i].size);
          Serial.println(String(mytires[i].diameter));
     }
     
}

void loop()
{
}
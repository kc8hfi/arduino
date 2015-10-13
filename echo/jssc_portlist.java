/*
 * To compile this program:
 * javac -cp jssc.jar:. jssc_portlist.java
 * 
 * To execute:
 * java -cp jssc.jar:. jssc_portlist
 * 
 * 
 */
 
import jssc.SerialPortList;

public class jssc_portlist
{
     public static void main(String[] args)
     {
          String[] portNames = SerialPortList.getPortNames();
          for(int i = 0; i < portNames.length; i++)
          {
               System.out.println(portNames[i]);
          }
     }
}
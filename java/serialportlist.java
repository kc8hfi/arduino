import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;

import java.io.OutputStream;
import java.util.Enumeration;

/*
 * You'll need the RXTX library installed, and then specify
 * the path to the RXTXcomm.jar file.  Depending your linux distro, 
 * it may not be in /usr/share/java

 * to compile,  you'll add the RXTXcomm.jar to the class path,  
 * linux:  javac -cp /usr/share/java/RXTXcomm.jar:. serialportlist.java
 * windows: javac -cp rxtxcomm.jar;. serialportlist.java
 *
 * If your serial port isn't detected when you try to connect to it,  specify it as an 
 * execution parameter.  
 * for example, -Dgnu.io.rxtx.SerialPorts=/dev/ttyACM0:/dev/ttyS8:/dev/<your serial port name here>
 * 
 * to run:
 * linux:  java -cp /usr/share/java/RXTXcomm.jar:. -Dgnu.io.rxtx.SerialPorts=/dev/ttyACM0 serialportlist
 * windows: java -cp rxtxcomm.jar;. serialportlist
 *
 * windows  replace the : with a ;  for the class path stuff
 * 
 */
 
public class serialportlist
{
     public static void main(String[] args)
     {
          System.out.println("hello world!");
          listPorts();
     }
     
     static void listPorts()
     {
          Enumeration portEnums = CommPortIdentifier.getPortIdentifiers();
          while(portEnums.hasMoreElements())
          {
               CommPortIdentifier portId = (CommPortIdentifier)portEnums.nextElement();
               System.out.println(portId.getName()  +  " - " +  getPortTypeName(portId.getPortType()) );
               //System.out.println(portId.getName());
          }
          
     }
     
     static String getPortTypeName(int p)
     {
          switch(p)
          {
               case CommPortIdentifier.PORT_I2C:
                    return "I2C";
               case CommPortIdentifier.PORT_PARALLEL:
                    return "Parallel";
               case CommPortIdentifier.PORT_RAW:
                    return "Raw";
               case CommPortIdentifier.PORT_RS485:
                    return "RS485";
               case CommPortIdentifier.PORT_SERIAL:
                    return "Serial";
               default:
                    return "unknown type";
          }
     }
     
}
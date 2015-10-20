/* This program uses the jssc serial library.  
 * https://github.com/scream3r/java-simple-serial-connector
 * 
 * This program has an ant build file
 * ant -p to list all the targets
 * ant build - to compile the program
 * ant run - to execute the program

 * to compile:
 * javac -cp jssc.jar:. *.java
 * 
 * to run:
 * java -cp jssc.jar:. server
 *
 * linux:
 * probably won't need to worry about this part with using the jssc library for everything,
 * including the arduino ide
 * 
 * look at the serial port,  stty -F /dev/ttyACM0 -a | grep hupcl   , replace /dev/ttyACM0 with your port
 * if it has -hupcl,  fix it by running:  stty -F /dev/ttyACM0 hup
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.File;
import java.util.TimerTask;
import java.util.Timer;
import java.util.Date;
import java.io.FileWriter;
import java.io.IOException;

import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;

public class server
{ 
     public static void main(String[] args)
     {
          BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
          String input = "";
          
          String port = "/dev/ttyACM0";
          String consoleReaderName = "Reader";
          
          String filename = "/var/www/mainsite/testsite/data.txt";
          File file = new File(filename);
          
          serialPort = new SerialPort(port);
          try 
          {
               serialPort.openPort();
               serialPort.setParams(SerialPort.BAUDRATE_9600,
                              SerialPort.DATABITS_8,
                              SerialPort.STOPBITS_1,
                              SerialPort.PARITY_NONE);

               serialPort.addEventListener(new PortReader(), SerialPort.MASK_RXCHAR);
          }
          catch (SerialPortException ex)
          {
               System.out.println("There are an error on writing string to port т: " + ex);
          }
          
          try 
          {
               ConsoleReadingThread consoleReader1 = new ConsoleReadingThread(reader,consoleReaderName, serialPort);
               consoleReader1.start();
               System.out.println("port: " + port + " ready");
               
               //this is the stuff that reads from the file and sends it to the board
               DoWork stuff = new DoWork(file,serialPort);
               
               //we need to monitor the file, looking for changes
               TimerTask t = new FileWatcher(file,stuff);
               Timer thetimer = new Timer();
               thetimer.schedule(t,new Date(),1000);
          }
          catch ( Exception e )
          {
               e.printStackTrace();
          }
     }//end main
     
     private static SerialPort serialPort;
     private static String buffer = "";
     
     
private static class PortReader implements SerialPortEventListener
{
     public void serialEvent(SerialPortEvent event) 
     {
          if(event.isRXCHAR() && event.getEventValue() > 0) //If data is available
          {
               try
               {
                    buffer += serialPort.readString(event.getEventValue());//Read all available from serial port and add it to buffer
                    if(buffer.endsWith("\r\n"))
                    {
                         buffer = buffer.substring(0,buffer.length()-2);
                         System.out.println("Received response: " + buffer);
                         writeToFile(buffer);
                         buffer = "";
                    }
               }
               catch (SerialPortException ex)
               {
                    System.out.println("Error in receiving string from COM-port: " + ex);
               }
          }
     }
     
     public void writeToFile(String s)
     {
          String filename = "/var/www/mainsite/testsite/fromarduino.txt";
          try
          {
               FileWriter f = new FileWriter(filename);
               f.write(s);
               f.close();
          }
          catch (IOException e)
          {
               System.out.println("cannot write to: " + filename);
               e.printStackTrace();
          }
     }
}//end PortReader class
     
}//end class server

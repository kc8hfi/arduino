import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.io.IOException;
import java.io.InputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.TooManyListenersException;
/*
 * You'll need the RXTX library installed, and then specify
 * the path to the RXTXcomm.jar file.  Depending your linux distro, 
 * it may not be in /usr/share/java

 * to compile,  you'll add the RXTXcomm.jar to the class path,  
 * javac -cp /usr/share/java/RXTXcomm.jar:. <name of file>.java
 *
 * If your serial port isn't detected when you try to connect to it,  specify it as an 
 * execution parameter.  
 * for example, -Dgnu.io.rxtx.SerialPorts=/dev/ttyACM0:/dev/ttyS8:/dev/<your serial port name here>
 * 
 * to run:
 * java -cp /usr/share/java/RXTXcomm.jar:. -Dgnu.io.rxtx.SerialPorts=/dev/ttyACM0 <name of file>
 *
 * windows  replace the : with a ;  for the class path stuff
 * 
 */
 
public class SimpleEcho 
{
     public SimpleEcho()
     {
     }
     
     public void connect(String port)
     {
          try
          {
            System.out.println("the port is:"+port);
               CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(port);
               
               //name of the program is the owner,  and 2000 is the timeout period,
               //how long it blocks waiting for the port to open,  (2 seconds)
               CommPort commPort;
               try{
               commPort = portIdentifier.open(this.getClass().getName(),2000);
               
               if (commPort instanceof SerialPort) //check to see if it is a SerialPort type
               {
                    //cast it as a SerialPort object
                    SerialPort serialPort = (SerialPort)commPort;
                    
                    //set up the communication parameters
                    //serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.FLOWCONTROL_NONE);
                    //serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8, SerialPort.STOPBITS_1);
                    
                    serialPort.setSerialPortParams(9600,
                                        SerialPort.DATABITS_8,
                                        SerialPort.STOPBITS_1,
                                        SerialPort.PARITY_NONE );
                    
                    //serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN
//                              | SerialPort.FLOWCONTROL_RTSCTS_OUT);
                    
                    //serialPort.setDTR(false);
                    //serialPort.setRTS(false);
                    //don't get hung up on a read if something happens,, after 5 seconds, throw exception
                    serialPort.enableReceiveTimeout(5000);
                    
                    InputStream incoming = serialPort.getInputStream();
                    OutputStream outgoing = serialPort.getOutputStream();

                    BufferedReader r= new BufferedReader(new InputStreamReader(incoming));
                    OutputStreamWriter w = new OutputStreamWriter(outgoing);
                    BufferedWriter bufferedWriter = new BufferedWriter(w);
                    PrintWriter writer = new PrintWriter(bufferedWriter);
                    
                    
                    //send some text out the port
                    //writer.write("hello there, arduino!");
                    //writes a system property line separator,  may not be a \n
                    writer.println("hello there arduino");
                    System.out.println("where did the write go");
                    //flushes the stream
                    //writer.flush();
                    //System.out.println("flushed everything");

                    
                    //get something from the arduino
                    String line = null;
                    try
                    {
                         System.out.println("read from the arduino now");
                         while (!r.ready())
                         {
                           //System.out.println("waiting on arduino");
                         }


                           
                          //char[] buffer = new char[100];
                          //int b = r.read(buffer,0,10);
                          //System.out.println(buffer);

                         //readLine reads until it hits a \r, \n, or a \r\n.  it returns a string that does not include
                         //any of the new line stuff
                         line = r.readLine();
                         System.out.println("read line with " + line.length() + " characters: \"" + line + "\" ");
                       
                    }
                    catch(IOException e)
                    {
                      System.out.println("timed out reading");
                         //e.printStackTrace();
                    }
               }
               }
               catch(Exception e)
               {
                 System.out.println("something happened with opening the port");
               }
               
          }
          catch (Exception e)
          {
               e.printStackTrace();
          }
     }

     public static void main(String[] args)
     {
          System.out.println("hello world!");
          SimpleEcho mytest = new SimpleEcho();
          mytest.connect("/dev/ttyACM0");
     }
}

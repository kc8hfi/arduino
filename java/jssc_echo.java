/* This program uses the jssc serial library.  
 * https://github.com/scream3r/java-simple-serial-connector
 * 
 * to compile:
 * javac -cp jssc-2.8.0.jar:. jssc_echo.java
 * 
 * to run;
 * java -cp jssc-2.8.0.jar:. jssc_echo
 * 
 * linux:
 * look at the serial port,  stty -F /dev/ttyACM0 -a | grep hupcl   , replace /dev/ttyACM0 with your port
 * if it has -hupcl,  fix it by running:  stty -F /dev/ttyACM0 hup
 */

import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortTimeoutException;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;



public class jssc_echo 
{
     public static void main(String[] args)
     {
          System.out.println("Sample read from arduino");
          jssc_echo p = new jssc_echo();
          p.connect();
     }

     private SerialPort serialPort;
     private String buffer = "";
     
     public void jssc_echo()
     {
     }
     public void connect()
     {
          serialPort = new SerialPort("/dev/ttyACM3");
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
     }

private class PortReader implements SerialPortEventListener
{
     @Override
     public void serialEvent(SerialPortEvent event) 
     {
          if(event.isRXCHAR() && event.getEventValue() > 0) //If data is available
          {
               try
               {
                    buffer += serialPort.readString(event.getEventValue());//Read all available from serial port and add it to buffer
                    if(buffer.endsWith("\n"))
                    {//Check the end of buffer string
                         System.out.println("Received response: " + buffer);

                         buffer = "";
                         serialPort.closePort();
                    }
               }
               catch (SerialPortException ex)
               {
                    System.out.println("Error in receiving string from COM-port: " + ex);
               }
          }
     }
}

}//end jssc_echo
     

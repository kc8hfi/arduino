/* This program uses the jssc serial library.  
 * https://github.com/scream3r/java-simple-serial-connector
 * 
 * to compile:
 * javac -cp jssc.jar:. jssc_echo.java
 * 
 * to run;
 * java -cp jssc.jar:. jssc_echo
 * 
 * linux:
 * probably won't need to worry about this part with using the jssc library
 * look at the serial port,  stty -F /dev/ttyACM0 -a | grep hupcl   , replace /dev/ttyACM0 with your port
 * if it has -hupcl,  fix it by running:  stty -F /dev/ttyACM0 hup
 */

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.BoxLayout;
import java.awt.Container;
import java.awt.Color;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
 
import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortTimeoutException;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;

public class jssc_fancyecho implements SerialPortEventListener, ActionListener
{
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
                         incomingField.setText(buffer);
                         buffer = "";
                         //serialPort.closePort();
                    }
               }
               catch (SerialPortException ex)
               {
                    System.out.println("Error in receiving string from COM-port: " + ex);
               }
          }
     }//end serialEvent
          
          
     public void actionPerformed(ActionEvent e)
     {
          //get the text
         //System.out.println(outgoingField.getText());
          try
          {
               //write string of text, you'll hafta put your own line ending here
               serialPort.writeString(outgoingField.getText() + "\n");
               outgoingField.setText("");
          }
          catch (SerialPortException exception)
          {
          }
     }
     
     public void setupGUI()
     {
          JFrame myframe = new JFrame("Arduino echoer");
          myframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          
          Container contentPane = myframe.getContentPane();
          contentPane.setLayout(new BoxLayout(contentPane,BoxLayout.Y_AXIS));
          
          JPanel outgoing = new JPanel();
          //outgoing.setBackground(Color.cyan);
          JLabel outgoingLabel = new JLabel("Send to arduino:");
          outgoingField = new JTextField(20);
          outgoing.add(outgoingLabel);
          outgoing.add(outgoingField);
          
          JPanel incoming = new JPanel();
          //incoming.setBackground(Color.orange);
          JLabel incomingLabel = new JLabel("coming from arduino:");
          incomingField = new JLabel();
          incoming.add(incomingLabel);
          incoming.add(incomingField);

          JPanel buttons = new JPanel();
          //buttons.setBackground(Color.yellow);
          JButton ok = new JButton("Send");
          buttons.add(ok);
          //ok.addActionListener(new ActionListener()
          ok.addActionListener(this);
          
          
          contentPane.add(outgoing);
          contentPane.add(buttons);
          contentPane.add(incoming);
          
          
          myframe.pack();
          //myframe.setMinimumSize(new Dimension(200,200));
          myframe.setVisible(true);
     }
     
     
     
     public void connect(String port)
     {
          serialPort = new SerialPort(port);
          try 
          {
               serialPort.openPort();
               serialPort.setParams(SerialPort.BAUDRATE_9600,
                              SerialPort.DATABITS_8,
                              SerialPort.STOPBITS_1,
                              SerialPort.PARITY_NONE);

               //serialPort.addEventListener(new PortReader(), SerialPort.MASK_RXCHAR);
               serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
          }
          catch (SerialPortException ex)
          {
               System.out.println("There are an error on writing string to port т: " + ex);
          }

          
     }//end connect
     
     private JTextField outgoingField;
     private JLabel incomingField;
     private String buffer = "";
     private SerialPort serialPort;

     public static void main(String[] args)
     {
          jssc_fancyecho mytest = new jssc_fancyecho();
          mytest.connect("/dev/ttyACM0");
          mytest.setupGUI();
     }
}
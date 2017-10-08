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
// 
import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
// 
import java.io.IOException;
import java.io.InputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.BufferedWriter;
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

public class FancyEcho implements SerialPortEventListener, ActionListener
{
     public void serialEvent(SerialPortEvent e)
     {

          //get something from the arduino
          String line = null;
          try
          {
               //System.out.println("read from the arduino now");
//                          char[] buffer = new char[100];
//                          int b = r.read(buffer,0,100);
//                          System.out.println(buffer);

               //readLine reads until it hits a \r, \n, or a \r\n.  it returns a string that does not include
               //any of the new line stuff
               line = r.readLine();
               //System.out.println("read line with " + line.length() + " characters: \"" + line + "\" ");
               incomingField.setText(line);
               
          }
          catch(IOException iox)
          {
               iox.printStackTrace();
          }
     }
     
     public void actionPerformed(ActionEvent e)
     {
          //get the text
          //System.out.println(outgoingField.getText());
          try
          {
               writer.write(outgoingField.getText());
               //writes a system property line separator,  may not be a \n
               writer.newLine();
               //flushes the stream
               writer.flush();
               outgoingField.setText("");
          }
          catch (IOException exception)
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
          try
          {
               CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(port);
               
               //name of the program is the owner,  and 2000 is the timeout period,
               //how long it blocks waiting for the port to open,  (2 seconds)
               CommPort commPort = portIdentifier.open(this.getClass().getName(),2000);
               
               if (commPort instanceof SerialPort) //check to see if it is a SerialPort type
               {
                    //cast it as a SerialPort object
                    SerialPort serialPort = (SerialPort)commPort;
                    
                    //set up the communication parameters
                    serialPort.setSerialPortParams(115200,SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.FLOWCONTROL_NONE);
                    
                    //don't get hung up on a read if something happens,, after 5 seconds, throw exception
                    serialPort.enableReceiveTimeout(5000);
                    
                    //add a listener               
                    try
                    {
                         serialPort.addEventListener(this);
                         serialPort.notifyOnDataAvailable(true);
                    }
                    catch (TooManyListenersException e)
                    {
                    }
                    
                    
                    InputStream incoming = serialPort.getInputStream();
                    OutputStream outgoing = serialPort.getOutputStream();

                    r= new BufferedReader(new InputStreamReader(incoming));
                    w = new OutputStreamWriter(outgoing);
                    writer = new BufferedWriter(w);
               }
          }
          catch (Exception e)
          {
               e.printStackTrace();
          }
     }//end connect
     
     private BufferedReader r;
     private OutputStreamWriter w;
     private BufferedWriter writer;
     private JTextField outgoingField;
     private JLabel incomingField;

     public static void main(String[] args)
     {
          FancyEcho mytest = new FancyEcho();
          mytest.connect("/dev/ttyACM0");
          mytest.setupGUI();
     }
}
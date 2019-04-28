package echo_swt;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;

public class mywindow implements SerialPortEventListener
{
     protected Shell shlMyEchoProgram;
     private Text text;
     private SerialPort serialPort;
     private String incomingBuffer;
     private Label incomingText;
     private static mywindow window;

     /**
      * Launch the application.
      * 
      * @param args
      */
     public static void main(String[] args)
     {
          try
          {
               window = new mywindow();
               window.open();
          }
          catch (Exception e)
          {
               e.printStackTrace();
          }
     }

     // this is the function that gets called when something comes in from the
     // serial port
     public void serialEvent(SerialPortEvent event)
     {
          if (event.isRXCHAR() && event.getEventValue() > 0) // If data is available
          {
               try
               {
                    incomingBuffer += serialPort.readString(event.getEventValue());
                    // check the incoming data. if it has a new line character, update the UI
                    if (incomingBuffer.endsWith("\n"))
                    {
                         // to keep the ui from not waiting for data on the serial port, we
                         // need a thread to update the ui separately once we get data
                         Display.getDefault().asyncExec(new Runnable()
                         {
                              public void run()
                              {
                                   // set the text to the incoming string
                                   window.incomingText.setText(incomingBuffer);
                              }
                         });
                    }
               }
               catch (SerialPortException ex)
               {
               }
          }
     }

     /**
      * Open the window.
      */
     public void open()
     {
          // when the main UI opens up, set up the serial port
          serialPort = new SerialPort("/dev/ttyACM0");
          try
          {
               serialPort.openPort();
               serialPort.setParams(SerialPort.BAUDRATE_9600, SerialPort.DATABITS_8, SerialPort.STOPBITS_1,
                         SerialPort.PARITY_NONE);
               serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
          }
          catch (SerialPortException ex)
          {
               System.out.println("There are an error on writing string to port t: " + ex);
          }
          // set the string that will hold the data coming from the serial port to an
          // empty string
          incomingBuffer = "";

          // creates the gui stuff
          Display display = Display.getDefault();
          createContents();
          shlMyEchoProgram.open();
          shlMyEchoProgram.layout();
          while (!shlMyEchoProgram.isDisposed())
          {
               if (!display.readAndDispatch())
               {
                    display.sleep();
               }
          }

          // when the program closes, we should close the
          // serial port to keep the program from having to be terminated
          try
          {
               serialPort.closePort();
          }
          catch (SerialPortException ex)
          {
               System.out.println("There are an error closing the port: " + ex);
          }
     }

     /**
      * Create contents of the window.
      */
     protected void createContents()
     {
          shlMyEchoProgram = new Shell();
          shlMyEchoProgram.setSize(450, 388);
          shlMyEchoProgram.setText("My echo program");

          text = new Text(shlMyEchoProgram, SWT.BORDER);
          text.setBounds(48, 145, 179, 30);

          Button submit = new Button(shlMyEchoProgram, SWT.NONE);
          // when the button gets clicked, get the text from the box and send it
          // to the serial port
          submit.addSelectionListener(new SelectionAdapter()
          {
               @Override
               public void widgetSelected(SelectionEvent e)
               {
                    // we need a \n character, since the arduino program will be looking for it
                    String sendme = text.getText() + "\n";
                    try
                    {
                         // send the data out the serial port
                         serialPort.writeString(sendme);
                    }
                    catch (SerialPortException ex)
                    {
                         System.out.println("cannot write to serial port" + ex.toString());
                    }
                    text.setText("");
               }
          });
          submit.setBounds(48, 186, 94, 34);
          submit.setText("Send Text");

          incomingText = new Label(shlMyEchoProgram, SWT.NONE);
          incomingText.setBounds(48, 258, 355, 17);

          Label lblNewLabel_1 = new Label(shlMyEchoProgram, SWT.NONE);
          lblNewLabel_1.setBounds(48, 110, 274, 30);
          lblNewLabel_1.setText("Type some text to send to the arduino");

          Label lblNewLabel_2 = new Label(shlMyEchoProgram, SWT.NONE);
          lblNewLabel_2.setBounds(48, 235, 179, 17);
          lblNewLabel_2.setText("Coming from the arduino:");

          Label lblNewLabel = new Label(shlMyEchoProgram, SWT.WRAP);
          lblNewLabel.setBounds(48, 38, 284, 44);
          lblNewLabel.setText("This program uses the echo program on the arduino.");

     }
}

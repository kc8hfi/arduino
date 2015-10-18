import java.awt.Component;
import javax.swing.JOptionPane;
import javax.swing.JToggleButton;
import java.util.regex.PatternSyntaxException;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

public class myportlistener implements SerialPortEventListener
{
     public void serialEvent(SerialPortEvent event) 
     {
          if(event.isRXCHAR() && event.getEventValue() > 0) //If data is available
          {
               try
               {
                    buffer += w.getPort().readString(event.getEventValue());//Read all available from serial port and add it to buffer
                    if(buffer.endsWith("\r\n"))
                    {//Check the end of buffer string
//                          char lastchar = buffer.charAt(buffer.length()-1);
//                          System.out.println("last:" + (int)lastchar);
//                          char before = buffer.charAt(buffer.length()-2);
//                          System.out.println("before the last:" + (int)before);
                         
                         //get rid of the \r\n
                         buffer = buffer.substring(0,buffer.length()-2);
                         try
                         {
                              String[] parts = buffer.split(":");
                              if (parts.length == 2)
                              {
                                   //System.out.println(parts[0]); //the code
                                   //add code to the list
                                   w.addCode(parts[0]);
                                   buffer = parts[1];  //the command for which button to enable/disable
                              }
                         }
                         catch(PatternSyntaxException pse)
                         {
                              
                         }
                         
                         switch(buffer)
                         {
                              case "redir":
                                   w.getred().setSelected(!w.getred().isSelected());
                              break;
                              case "greenir":
                                   w.getgreen().setSelected(!w.getgreen().isSelected());
                              break;
                              case "blueir":
                                   w.getblue().setSelected(!w.getblue().isSelected());
                              break;
                              case "orangeir":
                                   w.getorange().setSelected(!w.getorange().isSelected());
                              break;
                              case "relay":
                              break;
                              default:
                                   w.setIncomingText(buffer);
                         }
                         //w.setIncomingText(buffer);
                         buffer = "";
                    }
               }
               catch (SerialPortException ex)
               {
                    String message = "There was an error trying to read from the serial port!";
                    JOptionPane.showMessageDialog(w,
                    message,
                    "Serial port read error!",
                    JOptionPane.ERROR_MESSAGE);
               }
          }
     }//end serialEvent
     
     public myportlistener(thewindow w)
     {
          this.w = w;
     }
     private thewindow w;     
     private String buffer = "";
}
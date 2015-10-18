import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JOptionPane;
import java.awt.Dimension;
import java.awt.Component;
import jssc.SerialPort;
import jssc.SerialPortException;

public class myactionhandler implements ActionListener
{
     public void actionPerformed(ActionEvent e)
     {
          //System.out.print("button handler:");
          //System.out.println(javax.swing.SwingUtilities.isEventDispatchThread());
          
          //System.out.println(e.getActionCommand());
          Component source = (Component) e.getSource();
          while (source.getParent() != null)
          {
               source = source.getParent();
          }          
          //System.out.println(source);
          thewindow w = (thewindow)source;
          SerialPort p = w.getPort();
          String sendme = w.getTextToSend();
          
          switch(e.getActionCommand())
          {
               case "send":
                    try
                    {
                         p.writeString(sendme + "\n");
                    }
                    catch (SerialPortException exception)
                    {
                         String message = "There was an error trying to write to the serial port!";
                         JOptionPane.showMessageDialog(w,
                         message,
                         "Serial port write error!",
                         JOptionPane.ERROR_MESSAGE);
                    }
               break;
               case "clear":
                    w.clearList();
               break;
               default:
                    writeToPort(e.getActionCommand(),w);
          }
     }
     public void writeToPort(String s, thewindow parent)
     {
          try
          {
               parent.getPort().writeString(s + "\n");
          }
          catch (SerialPortException exception)
          {
               String message = "There was an error trying to write to the serial port!";
               JOptionPane.showMessageDialog(parent,
               message,
               "Serial port write error!",
               JOptionPane.ERROR_MESSAGE);
          }
     }
}
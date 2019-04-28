import javax.swing.JFrame;
import javax.swing.*;
import javax.swing.BoxLayout;
import java.awt.*;
import java.awt.event.*;
import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;


public class thewindow extends JFrame implements ActionListener
{
    public thewindow()
    {
        sp = new SerialPort("/dev/ttyACM0");
        try
        {
            sp.openPort();
            sp.setParams(SerialPort.BAUDRATE_9600,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);                
        }
        catch(SerialPortException exception)
        {}
    
        on = new JButton("on");
        off = new JButton ("off");
        label = new JLabel ("click the corresponding button to activate laser");
        
        
        on.addActionListener(this);
        off.addActionListener(this);
        
        Container contentPane = getContentPane();
        contentPane.setLayout(new BoxLayout(contentPane,BoxLayout.Y_AXIS));
        
        
        contentPane.add(label);
        contentPane.add(on);
        contentPane.add(off);
        
    }
    
    public void actionPerformed(ActionEvent e)
    {
        try
        {
        if (e.getActionCommand() == "on")
        {
            sp.writeString("on\n");
        }
        else if (e.getActionCommand() == "off")
        {
            sp.writeString("off\n");
        }
        }
        catch(SerialPortException ex)
        {
            System.out.println(ex);
        }
        
    }
    
    private JButton on;
    private JButton off;
    private JLabel label;
    public SerialPort sp;
}

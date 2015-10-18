import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JToggleButton;
import javax.swing.BoxLayout;
import java.awt.Container;
import java.awt.Color;
import javax.swing.JOptionPane;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.DefaultListModel;
import java.awt.BorderLayout;
import javax.swing.BorderFactory;
import java.awt.GridLayout;
import javax.swing.Box;
import java.awt.Dimension;

import jssc.SerialPort;
import jssc.SerialPortList;
import jssc.SerialPortException;

public class thewindow extends JFrame
{
     public thewindow(String t)
     {
          setTitle(t);
          Container contentPane = getContentPane();
          contentPane.setLayout(new BoxLayout(contentPane,BoxLayout.Y_AXIS));
          
          JLabel outgoingLabel = new JLabel("Send to arduino:");
          outgoingField = new JTextField(20);
          outgoingField.setText("Hello World!");
     
          model = new MyListModel<>();
          codes = new JList<>(model);

          
          
          JPanel echoPanel = new JPanel();
          echoPanel.setLayout(new BoxLayout(echoPanel,BoxLayout.Y_AXIS));
          echoPanel.setBorder(BorderFactory.createTitledBorder("Echo"));
          
          JPanel sendString = new JPanel();
          sendString.add(outgoingLabel);
          sendString.add(outgoingField);
          
          JPanel sendButtonPanel = new JPanel();
          JButton echo = new JButton("send");
          sendButtonPanel.add(echo);
          
          JPanel fromArduinoPanel = new JPanel();
          JLabel incomingLabel = new JLabel("arduino message:");
          incomingField = new JLabel();
          fromArduinoPanel.add(incomingLabel);
          fromArduinoPanel.add(incomingField);
          
          echoPanel.add(sendString);
          echoPanel.add(sendButtonPanel);
          echoPanel.add(fromArduinoPanel);
          
          JPanel colorGrid = new JPanel(new GridLayout(2,2));
          colorGrid.setBorder(BorderFactory.createTitledBorder("Colors"));
          orange = new JToggleButton("orange");
          red = new JToggleButton("red");
          green = new JToggleButton("green");
          blue = new JToggleButton("blue");
          colorGrid.add(red);
          colorGrid.add(green);
          colorGrid.add(blue);
          colorGrid.add(orange);
          
          JPanel irCodePanel = new JPanel(new BorderLayout());
          irCodePanel.setBorder(BorderFactory.createTitledBorder("IR codes"));
          scrollPane = new JScrollPane(codes);
          irCodePanel.add(scrollPane,BorderLayout.CENTER);
          JButton clear = new JButton("Clear codes");
          clear.setActionCommand("clear");
          irCodePanel.add(clear,BorderLayout.PAGE_END);

          
          contentPane.add(echoPanel);
          contentPane.add(Box.createRigidArea(new Dimension(0, 20))); //width,height
          contentPane.add(colorGrid);
          contentPane.add(Box.createRigidArea(new Dimension(0, 20)));
          contentPane.add(irCodePanel);

          
          myactionhandler handler = new myactionhandler();
          orange.addActionListener(handler);
          red.addActionListener(handler);
          green.addActionListener(handler);
          blue.addActionListener(handler);
          echo.addActionListener(handler);
          clear.addActionListener(handler);
          
          portlistener = new myportlistener(this);
          askForPort();
          openPort();
     }
     
     private void askForPort ()
     {
          String[] portNames = SerialPortList.getPortNames();
          whichPort = (String)JOptionPane.showInputDialog(
                    this,
                    "Which serial port is your arduino?",
                    "Select a port",
                    JOptionPane.PLAIN_MESSAGE,
                    null,
                    portNames,
                    "");
     }
     
     private void openPort()
     {
          //serialPort
          serialPort = new SerialPort(whichPort);
          try 
          {
               serialPort.openPort();
               serialPort.setParams(SerialPort.BAUDRATE_9600,
                              SerialPort.DATABITS_8,
                              SerialPort.STOPBITS_1,
                              SerialPort.PARITY_NONE);
               serialPort.addEventListener(portlistener, SerialPort.MASK_RXCHAR);
          }
          catch (SerialPortException ex)
          {
               System.out.println("There are an error on writing string to port т: " + ex);
               String message = "There was an error trying to open the serial port: "+ whichPort;
               JOptionPane.showMessageDialog(this,
               message,
               "Serial port open error!",
               JOptionPane.ERROR_MESSAGE);
          }
     }
     
     public SerialPort getPort()
     {
          return serialPort;
     }
     
     public String getTextToSend()
     {
          return outgoingField.getText();
     }
     public void setIncomingText(String t)
     {
          incomingField.setText(t);
     }
     public JToggleButton getorange()
     {
          return orange;
     }
     public JToggleButton getred()
     {
          return red;
     }
     public JToggleButton getgreen()
     {
          return green;
     }
     public JToggleButton getblue()
     {
          return blue;
     }
     public JPanel getCodePanel()
     {
          return codePanel;
     }
     public void addCode(String s)
     {
          model.addElement(s);
          model.update(model.getSize()-1);
          codes.ensureIndexIsVisible(model.getSize()-1);
     }
     public void clearList()
     {
          model.removeAllElements();
     }
     
     private String whichPort;
     private String[] portNames;
     private JTextField outgoingField;
     private JLabel incomingField;
     private SerialPort serialPort;
     private JToggleButton orange;
     private JToggleButton red;
     private JToggleButton green;
     private JToggleButton blue;
     private JScrollPane scrollPane;
     private JList<String> codes;
     private MyListModel<String> model;
     private JPanel codePanel;
     private myportlistener portlistener;
     
     private class MyListModel<String> extends DefaultListModel<String>
     {
          public void update(int index)
          {
               fireContentsChanged(this, index, index);
          }
     }
}
/* This program uses the jssc serial library.  
 * https://github.com/scream3r/java-simple-serial-connector
 * 
 * This program has an ant build file
 * ant -p to list all the targets
 * ant build - to compile the program
 * ant run - to execute the program
 * 
 * OR, if you prefer to do everything yourself:
 * to compile:
 * javac -cp jssc.jar:. *.java
 * 
 * to run;
 * java -cp jssc.jar:. controller
 * 
 * linux:
 * probably won't need to worry about this part with using the jssc library for everything,
 * including the arduino ide
 * 
 * look at the serial port,  stty -F /dev/ttyACM0 -a | grep hupcl   , replace /dev/ttyACM0 with your port
 * if it has -hupcl,  fix it by running:  stty -F /dev/ttyACM0 hup
 * If you don't check the hang up signal on linux,  the program will have an issue
 * with the "get IR codes" button.  
 */

import javax.swing.JFrame;

public class controller
{
//      public static void buildinterface()
//      {
//           thewindow mywindow = new thewindow("Controller");
//           mywindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//           mywindow.pack();
//           mywindow.setVisible(true);
//      }
//      public static void main(String[] args)
//      {
//           javax.swing.SwingUtilities.invokeLater(new Runnable()
//           {
//                public void run()
//                {
//                     buildinterface();
//                }
//           });
//      }
     
     
     public static void main(String[] args)
     {
          thewindow mywindow = new thewindow("Controller");
          mywindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          mywindow.pack();
          mywindow.setVisible(true);
     }
}


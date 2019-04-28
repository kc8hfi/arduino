
/*
to compile:
javac -cp jssc-2.8.0.jar:. laser1.java

to run
java -cp jssc-2.8.0.jar:. laser1
*/
import java.util.Scanner;

import javax.swing.JFrame;


public class laser1 
{
    public static void main(String[] args)
    {
        //System.out.println("howdy");
        thewindow gui = new thewindow();
        gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        gui.pack();
        gui.setVisible(true);
        
        
//         Scanner input = new Scanner(System.in);
//         String inputString = "";
//         do
//         {
//             System.out.println("enter in text, quit  exits");
//             inputString = input.nextLine();
//             try
//             {
//                 sp.writeString(inputString + "\n");
//             }
//             catch(SerialPortException e)
//             {
//             }
//         }while(!inputString.equals("quit"));
//       try
//       {
//         sp.closePort();
//       }
//       catch(SerialPortException e)
//       {
//       }
        
                
    }
}

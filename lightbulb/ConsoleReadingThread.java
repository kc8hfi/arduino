import java.io.BufferedReader;
import java.io.BufferedWriter;
import jssc.SerialPort;

public class ConsoleReadingThread extends Thread
{

     private BufferedReader reader = null;
     private String readerId = "";
     //private BufferedWriter mywriter;
     private SerialPort serialPort;
     //public ConsoleReadingThread(BufferedWriter sw,BufferedReader br,String readerId)
     public ConsoleReadingThread(BufferedReader in, String id, SerialPort port)
     {
          this.reader = in; /* new BufferedReader(new InputStreamReader(System.in))*/
          this.readerId = id;
          //this.mywriter = sw;
          serialPort = port;
     }

     public void run()
     {
          System.out.println(readerId + " is ready");
          GetHoldOfTheConsole();
          super.run();
     }

     public void GetHoldOfTheConsole()
     {
          while(true)
          {
               try
               {
                    String getData = reader.readLine();
                    //System.out.println(readerId + " reads:'" + getData+"'");
                    System.out.println("keyboard input:'" + getData + "'");
                    
                    //write stuff to the serial port
                    serialPort.writeString(getData + "\n");
                    
                    //write the stuff out the serial port
                    //mywriter.write(getData);
                    //send a new line character
                    //mywriter.newLine();
                    //flush the buffer
                    //mywriter.flush();
               }
               catch(Exception ex)
               {
                    System.out.println("Go away!");
               }
          }
     }
}
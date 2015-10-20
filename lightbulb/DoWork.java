//import java.util.*;
//import java.io.*;

import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

import jssc.SerialPort;
import jssc.SerialPortException;

public class DoWork
{
     private File thefile;
     //private BufferedWriter writer;
     //private cartinfo status;
     private SerialPort serialPort;
     
     private int whichdir = 0;     //turning left or right
     
     public DoWork (File f, SerialPort p)
     {
          thefile = f;
          serialPort = p;
     }
     
     public void doit()
     {
          try 
          {
               // FileReader reads text files in the default encoding.
               FileReader fileReader = new FileReader(thefile);

               // Always wrap FileReader in BufferedReader.
               BufferedReader bufferedReader = new BufferedReader(fileReader);
               String line = null;
               while((line = bufferedReader.readLine()) != null) 
               {
                    System.out.println("the file contains:'" +line +"'");
                    try
                    {
                         serialPort.writeString(line + "\n");
                    }
                    catch(SerialPortException spe)
                    {
                         System.out.println("couldn't write to the serial port: " + line);
                    }
               }  
               // Always close files.
               bufferedReader.close();                    
          }
          catch(IOException e)
          {
          }
     }//end doit
}//end DoWork 

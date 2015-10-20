//import java.util.*;
//import java.io.*;
import java.util.TimerTask;
import java.io.File;

public  class FileWatcher extends TimerTask
{
     private File file;
     private long timestamp;
     private DoWork worker;

     public FileWatcher(File f, DoWork w)
     {
          file = f;
          timestamp = file.lastModified();
          worker = w;
          //System.out.println("got a new file watcher thing");
     }
     
     public void run()
     {
          long ts = file.lastModified();
          //System.out.println(ts);
          if(timestamp != ts)
          {
               timestamp = ts;
               //since the file has changed, go do something with it now!!
               //System.out.println("the file changed!");
               worker.doit();
          }
     }//end run
}//end filewatcher 

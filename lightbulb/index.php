<?php
session_start();
//print out an array and make it nice and readable
function print_array($array)
{

     echo "<hr><div style=\"font-family: 'Courier New', Courier, monospace; font-size: 12px;\">\n";
     print_array_recursive($array, '');
     echo "</div><hr>\n";
}
//used by the print_array function
function print_array_recursive($array, $prefix)
{
     foreach ($array as $k=>$v)
     {
          if (is_array($v))
          {
               echo $prefix.$k.' =&gt; '."<br>\n";
               print_array_recursive($v, $prefix."&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
          }
          else
          {
               echo $prefix.$k.' =&gt; '.$v."<br>\n";
          }
     }
}

//prints out some stuff to make an html5 compliant page
function begin()
{
     echo <<<EOF
<!DOCTYPE html>
<html><head>
<!-- <meta http-equiv="refresh" content="5"> -->

<style>

/***FIRST STYLE THE BUTTON***/
input#gobutton
{
     cursor:     pointer; /*forces the cursor to change to a hand when the button is hovered*/
     padding:    5px 25px; /*add some padding to the inside of the button*/
     background: #35b128; /*the colour of the button*/
     border:     1px solid #33842a; /*required or the default border for the browser will appear*/
     
     /*give the button curved corners, alter the size as required*/
     -moz-border-radius:    10px;
     -webkit-border-radius: 10px;
     border-radius:         10px;
     
     /*give the button a drop shadow*/
     -webkit-box-shadow:  0 0 4px rgba(0,0,0, .75);
     -moz-box-shadow:     0 0 4px rgba(0,0,0, .75);
     box-shadow:          0 0 4px rgba(0,0,0, .75);
     
     /*style the text*/
     color:     #f3f3f3;
     font-size: 1.1em;
}

/***NOW STYLE THE BUTTON'S HOVER AND FOCUS STATES***/
input#gobutton:hover, input#gobutton:focus
{
     background-color :#399630; /*make the background a little darker*/
     /*reduce the drop shadow size to give a pushed button effect*/
     -webkit-box-shadow: 0 0 1px rgba(0,0,0, .75);
     -moz-box-shadow: 0 0 1px rgba(0,0,0, .75);
     box-shadow: 0 0 1px rgba(0,0,0, .75);
}

</style>

<title>Arduino stuff</title>
EOF;
}

//prints out the content for the page
function form()
{
     $items = read_file();
     echo <<<EOF
     
<form method="POST" name="login" action="index.php">

<fieldset>
     <legend>Status Update</legend>
     <input id="gobutton" name="clickme" value="Update" type="submit">
</fieldset>

<fieldset>
     <legend>Echo</legend>
     <label>Enter some text</label>
     <input type="text" name="echo_text" value="" />
     <input id="gobutton" type="submit" name="clickme" value="Send">
     <p>$items</p>
</fieldset>
<fieldset>
     <legend>Toggle the light bulb</legend>
     <input id="gobutton" type="submit" name="clickme" value="Toggle Light" />
</fieldset>
<fieldset>
     <legend>Colored LED's</legend>
     <table>
     <tr>
          <td><input id="gobutton" name="clickme" value="red" type="submit"></td>
          <td><input id="gobutton" name="clickme" value="green" type="submit"></td>
     </tr>
     <tr>
          <td><input id="gobutton" name="clickme" value="blue" type="submit"></td>
          <td><input id="gobutton" name="clickme" value="orange" type="submit"></td>
     </tr>
     </table>
     
</fieldset>
</form>
EOF;
}



//prints out the ending stuff
function ending()
{
     echo <<<EOF
</body>
</html>
EOF;
}

function read_file()
{
     $filename = "fromarduino.txt";
     $contents = file_get_contents($filename);
     
//      var_dump($contents);
     
     $returnme = "";
     if (substr($contents,0,3) != "you")
     {
          $contents = "";
     }
     
//      $echo_response = "";
//      $whichled = "";
//      $ircodes = "";
// 
//      
//      $parts = explode(":",$contents);
//      if (count($parts) == 2)
//      {
//           //put the code in the text box
//           //$parts[0]
//           $ircodes = $parts[0];
//           //put the rest in the status
//           //$parts[1]
//           $contents = $parts[1];
//      }
//      switch($contents)
//      {
//           case "red":
//                //red
//                $s['whichled'] = "red led is on";
//           break;
//           case "green":
//                //red
//                $s['whichled'] = "green led is on";
//           break;
//           case "blue":
//                //red
//                $s['whichled'] = "blue led is on";
//           break;
//           case "orange":
//                //red
//                $s['whichled'] = "orange led is on";
//           break;
//           
//           default:
//                $s['echo_response'] = $contents;
//      }
//      print_array($s);
     return $contents;
}

function writeme($data)
{
     $filename = "data.txt";
     file_put_contents($filename,$data."\n");  //maybe append or something....
}

/*------------------------------------The code starts here----------*/
if (isset($_POST['clickme']))
{
     switch($_POST['clickme'])
     {
          case "Toggle Light":
               writeme("light");
          break;
          case "red":
               writeme("red");
          break;
          case "green":
               writeme("green");
          break;
          case "blue":
               writeme("blue");
          break;
          case "orange":
               writeme("orange");
          break;
          case "Send":
               writeme($_POST['echo_text']);
          break;
          default:
     }
     begin();
     form();
     ending();
}
else
{
     begin();
     form();
     ending();
}
?>
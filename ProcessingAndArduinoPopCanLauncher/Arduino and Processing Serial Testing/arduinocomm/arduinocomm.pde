/*
 * Arduino Communiacations Without Firmata
 *
 * Sends data to an Arduino over serial communications.
 * Can receive data from the Arduino.
 *
 * Too slow to be used for my pop can project but works.
 */
import processing.serial.*;
import processing.sound.*;
Serial serial;
SoundFile file;
String s = ""; 

void setup() {
  size(256, 150);
  file = new SoundFile(this, "file.mp3");
  println("Available serial ports:");
  // if using Processing 2.1 or later, use Serial.printArray()
  println(Serial.list());
  
  serial = new Serial(this, Serial.list()[0], 9600); //start serial communication with the first comm port at 9600 baud rate

  //port = new Serial(this, "COM3", 9600); //can be used if the name of the port you want to use is known
}

void draw() {
  frameRate(1); //slow the sketch down to one loop per second
  //println(port.read());
  /*if (port.read() == 1) {
   file.play();
   }*/
}

void serialEvent(Serial p) {
  /*if (p.read() == 1) {
   file.play();
   }*/
  //while (p.available() > 0) {


    
  char in = p.readChar();
  println(in);
  if (in == '/') {
    s = "";
  }
  s += in;
  if (in == ';') {
    println(s);
    inputReceived(s);
  }
  
  //}
  //println(s);
  //String s = p.readString();
  // println(p.read());
}

void inputReceived(String s) {
  if (s.charAt(1) == 'A') {
    if (s.charAt(2) == '6') {
      //do analog6 input stuff
      println("hmmm");
      //finds the value sent at the end of the string
      String num = "";
      for (int i = 3; i < s.length(); i ++) {
        if (s.charAt(i) >= '0' && s.charAt(i) <= '9') {
          num += s.charAt(i);
        }
      }
      int(num); //converts the string num to an int
    }
    if (s.charAt(2) == '7') {
      //do analog7 input stuff
    }
  }
}

void output(char aOrD, String port, String value) { //outputs a command over the serial port
  String s = "";
  s += "/";
  s += aOrD; //analog or digital
  s += port; //which input on the arduino
  s += ":";
  s += value; //the value to send
  s += ";";

  serial.write(s);
}

void keyPressed() {
  if (key == 'q') {
    output('d', "10", "1"); //turn digital pin 10 on
  } else if (key == 'w') {
    output('d', "10", "0"); //turn digital pin 10 off
  }
}
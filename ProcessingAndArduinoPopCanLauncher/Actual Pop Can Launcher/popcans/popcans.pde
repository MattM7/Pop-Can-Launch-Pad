import processing.serial.*;
import processing.sound.*;
Serial serial;
SoundFile file, file1, file2, file3, file4;
String s = ""; 
char c;
char prevC = 70; //placeholder

void setup() {
  size(256, 150);
  file = new SoundFile(this, "note1.wav");
  file1 = new SoundFile(this, "note3.wav");
  file2 = new SoundFile(this, "note2.wav");
  file3 = new SoundFile(this, "note5.wav");
  file4 = new SoundFile(this, "note7.wav");

  println("Available serial ports:");
  // if using Processing 2.1 or later, use Serial.printArray()
  println(Serial.list());

  if (Serial.list().length > 0) { // prevents a crash that freezes if there is no arduino connected
    serial = new Serial(this, Serial.list()[0], 9600); //use the first available port, sets the baud rate to 9600
  } else {
    println("no ports available");
    stop();
  }
}


void draw() {
  background(20); //dark grey screen
}

void serialEvent(Serial p) {
  if (p.available() > 0) { //if there is a character available on the serial port
    c = p.readChar();

    if (c != prevC) { //prevents a file from launching multiple times in a short period of time
                      //this is bad in general because you can't play the same sound twice in a row but it works well for Thunderstruck
                      //a better solution in the future would be to not allow a file to start playing if it was started < a second ago
      switch (c) { //decides which sound to play
      case 7:
        println("7");
        file.play();
        break;
      case 6:
        println("6");
        file1.play();
        break;
      case 5:
        // println("5");
        file2.play();
        break;
      case 4:
        println("4");
        file3.play();
        break;
      case 3:
        println("3");
        file4.play();
        break;
      default:
        //println("something went wrong");
        break;
      }
    }
    prevC = c;
  }
}

void keyPressed() {
  println("break"); //for an easier time reading the print out in the console
}
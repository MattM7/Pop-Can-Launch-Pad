/* 
 *  Processing Communications
 *  
 *  Allows analog or digital commands to be received and send values back to a Processing 
 *  program over serial comms. 
 *  
 *  Too slow to be used for my pop can project but works.
 */

String inputString = ""; //going to look something like /a10:500;
String out;
boolean stringComplete = false;

void setup() {
  Serial.begin(9600); //start serial output with 9600 baud rate

  //set pins as inputs and outputs
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(10, OUTPUT);

  inputString.reserve(200); //reserve 200 bytes to recieve a string
}

void loop() {

  /* //Serial.write(analogRead(A1)); //all of this was for writing out
    int nA6 = analogRead(A6);
    int nA7 = analogRead(A7);
    if (nA7 < 60 && nA7 > 0) {
     out += "A7";
     out += ":";
     out += String(nA7);
     Serial.println(out);
     //Serial.write(nA7);
     out = "";
     //Serial.write(nA7);
    }
    if (nA6 < 60 && nA6 > 0) {
     out += "A6";
     out += ":";
     out += String(nA6);
     //Serial.println(out);
     for (char i = 0; i < out.length(); i ++) {
       Serial.write(out.charAt(i));
     }
     out = "";
     //Serial.write(nA7);
    }

    //Serial.println(analogRead(A7));

    //Serial.println(analogRead(A1));
    //Serial.println(analogRead(A7));
    delay(1000);

    out += "/";
    out += "A6";
    out += ":";
    out += String(nA6);
    out += ";";
    //Serial.println(out);
    for (char i = 0; i < out.length(); i ++) {
     Serial.write(out.charAt(i));
    }
    out = "";
    //Serial.println(digitalRead(13));
    //Serial.println(digitalRead(12));
    //Serial.write(digitalRead(13));
  */

  parseInput();
}

// calls a digitalWrite based on information received
void digitalReceived(String port, String value) {
  int nPort = port.toInt();
  int nValue = value.toInt();
  digitalWrite(nPort, nValue);
  stringComplete = false;
  inputString = ""; //reset the string because I'm done with it
}

// calls an analogWrite based on information received
void analogReceived(String port, String value) {
  int nPort = port.toInt();
  int nVal = value.toInt();

  analogWrite(nPort, nVal);
  stringComplete = false;
  inputString = ""; //reset the string because I'm done with it
}

//decides what to do based on what string is recieved
void parseInput() {
  if (stringComplete) { //waits for a ; to make sure that everything is there
    //finds the pin and the value being sent to it
    char count = 2;
    String port = "";
    String value = "";

    while (inputString.charAt(count) != ':') {
      port += inputString.charAt(count); //going to look until there is a : to find the port number
      count ++;
    }
    count ++;
    while (inputString.charAt(count) != ';') {
      value += inputString.charAt(count); //going to look until the ; to get the value
      count ++;
    }
    
    if (inputString.charAt(1) == 'd') { //means it's a digital command

      digitalReceived(port, value);
    }

    if (inputString.charAt(1) == 'a') { //means it's an analog command

      analogReceived(port, value);
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    //read in a character and add it to the string
    char inChar = (char)Serial.read();
    inputString += inChar;

    if (inChar == ';') {
      stringComplete = true; //flag that the string is ready to be parsed
    }
  }
}

//sources
//https://www.arduino.cc/en/Tutorial/SerialEvent
//https://www.arduino.cc/en/Serial/Write

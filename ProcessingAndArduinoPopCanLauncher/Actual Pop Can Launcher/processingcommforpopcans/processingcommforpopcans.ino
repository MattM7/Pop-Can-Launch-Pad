/*
 * Serial Communications with Processing for the pop cans
 * Sends a number based on what pop can is pressed;
 *
 */

int nA7, nA6, nA5, nA4, nA3;
int nUpper =950; //the upper end of the range of analog values from the can being touched
int nLower = 0; //the lower end
void setup() {
  Serial.begin(9600); //start serial communication with 9600 baud rate
}

void loop() {
  //Serial.write(analogRead(A1));

  nA7 = analogRead(A7); // analogReads + println is better for seeing what the range of the popcan is than analog.write
  //Serial.println(nA7);
  if (nA7 < nUpper && nA7 > nLower) { //checks if the popcan is being touched 
    //Serial.println(5432);
    Serial.write(7); //all of the Serial.write should be commented out if analogRead is uncommented
  }

  nA6 = analogRead(A6);
  //Serial.println(nA6);
  if (nA6 < nUpper && nA6 > nLower) {
    Serial.write(6);
  }

  nA5 = analogRead(A5);
  //Serial.println(nA5);
  if (nA5 < nUpper && nA5 > nLower) {
    Serial.write(5);
  }

  nA4 = analogRead(A4);
  //Serial.println(nA4);
  if (nA4 < nUpper && nA4 > nLower) {
    Serial.write(4);
  }

  nA3 = analogRead(A3);
  //Serial.println(nA3);
  if (nA3 < nUpper && nA3 > nLower) {
    Serial.write(3);
  }

  //delay(10); //delay added here bc it is way too fast without it
}

//sources
//https://www.arduino.cc/en/Tutorial/SerialEvent
//https://www.arduino.cc/en/Serial/Write

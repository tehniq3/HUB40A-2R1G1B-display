/*
  use Shift Register Example - https://www.arduino.cc/en/Tutorial/ShftOut13
  sketch version 4m1j - 26.09.2015, Craiova - Romania
  for 2 display P20F04D-12L with HUB40A connector
  original sketch by niq_ro from http://www.tehnic.go.ro
  http://nicuflorica.blogspot.ro/
  http://arduinotehniq.blogspot.com/
 */
int latchPin = 10;  //  latch 
int clockPin = 9;   // clock

// upper row
int dataPin1 = 2;   // 1R1 colour
int dataPin2 = 3;   // 1G colour
int dataPin3 = 4;   // 1B colour
// lower row
int dataPin4 = 5;   // 2R1 colour
int dataPin5 = 6;   // 2G colour
int dataPin6 = 7;   // 2B colour

int OEPin = 11;  //  OE = Output enable terminal
//When OE (active) low, the output drivers are enabled;
//when OE high, all output drivers are turned OFF (blanked). 
// MBI5026 datasheet: 

//holders for infromation you're going to pass to shifting function
byte data, data2;
byte dataArray[32];


int spid = 500;  // time between moving text/image

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin1, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(dataPin3, OUTPUT);
  pinMode(dataPin4, OUTPUT);
  pinMode(dataPin5, OUTPUT);
  pinMode(dataPin6, OUTPUT);
  
  pinMode(OEPin, OUTPUT);
  
 digitalWrite(dataPin1, LOW);
 digitalWrite(dataPin2, LOW);
 digitalWrite(dataPin3, LOW);
 digitalWrite(dataPin4, LOW);
 digitalWrite(dataPin5, LOW);
 digitalWrite(dataPin6, LOW);
 
 digitalWrite(OEPin, LOW);

pinMode (11, OUTPUT);  // OE
digitalWrite(11, LOW);  
  
  Serial.begin(9600);

  //Binary notation as comment
//  dataArray[0] = 0xFF; //0b11111111
/*
dataArray[0] = 0b10011101;  
dataArray[1] = 0b10111001;  
dataArray[2] = 0b01000101;  
dataArray[3] = 0b01010100;
dataArray[4] = 0b11100000;
dataArray[5] = 0b00001110;
dataArray[6] = 0b10011001;
dataArray[7] = 0b10010110;
*/
//dataArray[8] = 0x00; //0b00000000
//  dataArray[9] = 0xE0; //0b11100000


dataArray[0] = 0b01111000;
dataArray[1] = 0b00000001;
dataArray[2] = 0b00100100;
dataArray[3] = 0b10001111;
dataArray[4] = 0b00011010;
dataArray[5] = 0b10000000;
dataArray[6] = 0b00000000;
dataArray[7] = 0b00101001;

dataArray[8] = 0b11000010;
dataArray[9] = 0b00101100;
dataArray[10] = 0b00100010;
dataArray[11] = 0b00101100;
/*
dataArray[12] = 0b01101001;
dataArray[13] = 0b10010110;
dataArray[14] = 0b00000000;
dataArray[15] = 0b00000000;
*/

dataArray[12] = 0b00000011;
dataArray[13] = 0b00110000;
dataArray[14] = 0b00000011;
dataArray[15] = 0b00110000;


dataArray[16] = 0b00010001;
dataArray[17] = 0b00010001;
dataArray[18] = 0b00000000;
dataArray[19] = 0b00010000;

dataArray[20] = 0b11110000;
dataArray[21] = 0b00001110;
dataArray[22] = 0b00010001;
dataArray[23] = 0b00011110;

dataArray[24] = 0b00110100;
dataArray[25] = 0b01000111;
dataArray[26] = 0b01000100;
dataArray[27] = 0b01000011;

dataArray[28] = 0b10000100;
dataArray[29] = 0b00001000;
dataArray[30] = 0b01000100;
dataArray[31] = 0b01001000;

  //function that blinks all the LEDs
  //gets passed the number of blinks and the pause time
//  blinkAll_2Bytes(2,500); 
}

void loop() {
 clearAll_2Bytes(2,500); 
 
for (int n = 2; n <= 4; n++) {  
for (int m = 2; m <= 4; m++) {  
for (int l = 2; l <= 4; l++) {  
//  int l = 5;
//for (int o = 0; o < 2; o++) {
for (int j = 0; j < 8; j++) {
    //load the light sequence you want from array
//    data = dataArray[2*j+1];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    //shiftOut(dataPin3, clockPin, data);
    shiftOut41(l, l+3, m, m+3, n, n+3, clockPin, dataArray[4*j], dataArray[4*j+2]);
 //   shiftOut31(l, l+3, m, m+3, n, n+3, clockPin, data);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
    //load the light sequence you want from array

   // data = dataArray[2*j];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
     shiftOut42(l, l+3, m, m+3, n, n+3, clockPin, dataArray[4*j+1], dataArray[4*j+3]);
//    shiftOut32(l, l+3, m, m+3, n, n+3, clockPin, data);
        //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
   
    delay(spid);
  }
//}
delay(5000);
  clearAll_2Bytes(2,500); 

}
}
}

/*
for (int k = 2; k <= 7; k++) {
for (int l = 2; l <= 7; l++) {  
for (int j = 0; j < 4; j++) {
    //load the light sequence you want from array
    data = dataArray[2*j];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    //shiftOut(dataPin3, clockPin, data);
    shiftOut2(k, l, clockPin, data);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
    //load the light sequence you want from array

    data = dataArray[2*j+1];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut2(k, l, clockPin, data);
        //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
   
    delay(spid);
  }

delay(2000);
  clearAll_2Bytes(2,500); 
}

}
*/
/*
for (int k = 2; k <= 7; k++) {
for (int l = 2; l <= 7; l++) {  
for (int m = 2; m <= 7; m++) {  
  for (int j = 0; j < 4; j++) {
    //load the light sequence you want from array
    data = dataArray[2*j];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    //shiftOut(dataPin3, clockPin, data);
    shiftOut3(k, l, m, clockPin, data);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
    //load the light sequence you want from array

    data = dataArray[2*j+1];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
     shiftOut3(k, l, m, clockPin, data);
        //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
   
    delay(spid);
  }

delay(spid);
  clearAll_2Bytes(2,500); 

}
}
}
*/
  
} // end main loop



// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

/*
//blinks the whole register based on the number of times you want to 
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin1, clockPin, 0);
  shiftOut(dataPin1, clockPin, 0);
  digitalWrite(latchPin, 1);

  shiftOut(dataPin2, clockPin, 0);
  shiftOut(dataPin2, clockPin, 0);
  digitalWrite(latchPin, 1);

  shiftOut(dataPin3, clockPin, 0);
  shiftOut(dataPin3, clockPin, 0);
  digitalWrite(latchPin, 1);


  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin1, clockPin, 255);
    shiftOut(dataPin1, clockPin, 255);
    digitalWrite(latchPin, 1);
    shiftOut(dataPin2, clockPin, 255);
    shiftOut(dataPin2, clockPin, 255);
    digitalWrite(latchPin, 1);
    shiftOut(dataPin3, clockPin, 255);
    shiftOut(dataPin3, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin1, clockPin, 0);
    shiftOut(dataPin1, clockPin, 0);
    digitalWrite(latchPin, 1);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin2, clockPin, 0);
    shiftOut(dataPin2, clockPin, 0);
    digitalWrite(latchPin, 1);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin3, clockPin, 0);
    shiftOut(dataPin3, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}
*/

void clearAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin1, clockPin, 0);
  shiftOut(dataPin1, clockPin, 0);
  digitalWrite(latchPin, 1);

  shiftOut(dataPin2, clockPin, 0);
  shiftOut(dataPin2, clockPin, 0);
  digitalWrite(latchPin, 1);

  shiftOut(dataPin3, clockPin, 0);
  shiftOut(dataPin3, clockPin, 0);
  digitalWrite(latchPin, 1);

  shiftOut(dataPin4, clockPin, 0);
  shiftOut(dataPin4, clockPin, 0);
  digitalWrite(latchPin, 1);

  shiftOut(dataPin5, clockPin, 0);
  shiftOut(dataPin5, clockPin, 0);
  digitalWrite(latchPin, 1);

  shiftOut(dataPin6, clockPin, 0);
  shiftOut(dataPin6, clockPin, 0);
  digitalWrite(latchPin, 1);


//  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin1, clockPin, 0);
    shiftOut(dataPin1, clockPin, 0);
    digitalWrite(latchPin, 1);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin2, clockPin, 0);
    shiftOut(dataPin2, clockPin, 0);
    digitalWrite(latchPin, 1);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin3, clockPin, 0);
    shiftOut(dataPin3, clockPin, 0);
    digitalWrite(latchPin, 1);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin4, clockPin, 0);
    shiftOut(dataPin4, clockPin, 0);
    digitalWrite(latchPin, 1);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin5, clockPin, 0);
    shiftOut(dataPin5, clockPin, 0);
    digitalWrite(latchPin, 1);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin6, clockPin, 0);
    shiftOut(dataPin6, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}


// the heart of the program
void shiftOut2(int myDataPin1, int myDataPin2, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin1, pinState);
    digitalWrite(myDataPin2, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

// the heart of the program
void shiftOut3(int myDataPin1, int myDataPin2, int myDataPin3, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);
  pinMode(myDataPin3, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myDataPin3, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin1, pinState);
    digitalWrite(myDataPin2, pinState);
    digitalWrite(myDataPin3, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
    digitalWrite(myDataPin3, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}


// the heart of the program
void shiftOut11(int myDataPin1, int myDataPin2, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
//    digitalWrite(myDataPin1, pinState);
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}


// the heart of the program
void shiftOut12(int myDataPin1, int myDataPin2, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin1, pinState);
 //   digitalWrite(myDataPin1, 0);
 //   digitalWrite(myDataPin2, pinState);
    digitalWrite(myDataPin2, 0);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}


// the heart of the program
void shiftOut21(int myDataPin1, int myDataPin2, int myDataPin3, int myDataPin4, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);
  pinMode(myDataPin3, OUTPUT);
  pinMode(myDataPin4, OUTPUT);
  

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myDataPin3, 0);
  digitalWrite(myDataPin4, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
//    digitalWrite(myDataPin1, pinState);
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin3, 0);
    digitalWrite(myDataPin2, pinState);
    digitalWrite(myDataPin4, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
    digitalWrite(myDataPin3, 0);
    digitalWrite(myDataPin4, 0); 
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}

// the heart of the program
void shiftOut22(int myDataPin1, int myDataPin2, int myDataPin3, int myDataPin4, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);
  pinMode(myDataPin3, OUTPUT);
  pinMode(myDataPin4, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myDataPin3, 0);
  digitalWrite(myDataPin4, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin1, pinState);
    digitalWrite(myDataPin3, pinState);
 //   digitalWrite(myDataPin1, 0);
 //   digitalWrite(myDataPin2, pinState);
    digitalWrite(myDataPin2, 0);
    digitalWrite(myDataPin4, 0);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
    digitalWrite(myDataPin3, 0);
    digitalWrite(myDataPin4, 0);
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}


// the heart of the program
void shiftOut31(int myDataPin1, int myDataPin2, int myDataPin3, int myDataPin4, int myDataPin5, int myDataPin6, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);
  pinMode(myDataPin3, OUTPUT);
  pinMode(myDataPin4, OUTPUT);
  pinMode(myDataPin5, OUTPUT);
  pinMode(myDataPin6, OUTPUT);
  
  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myDataPin3, 0);
  digitalWrite(myDataPin4, 0);
  digitalWrite(myDataPin5, 0);
  digitalWrite(myDataPin6, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
//    digitalWrite(myDataPin1, pinState);
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin3, 0);
    digitalWrite(myDataPin5, 0);
    digitalWrite(myDataPin2, pinState);
    digitalWrite(myDataPin4, pinState);
    digitalWrite(myDataPin6, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
    digitalWrite(myDataPin3, 0);
    digitalWrite(myDataPin4, 0); 
    digitalWrite(myDataPin5, 0);
    digitalWrite(myDataPin6, 0); 
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}


// the heart of the program
void shiftOut32(int myDataPin1, int myDataPin2, int myDataPin3, int myDataPin4, int myDataPin5, int myDataPin6, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);
  pinMode(myDataPin3, OUTPUT);
  pinMode(myDataPin4, OUTPUT);
  pinMode(myDataPin5, OUTPUT);
  pinMode(myDataPin6, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myDataPin3, 0);
  digitalWrite(myDataPin4, 0);
  digitalWrite(myDataPin5, 0);
  digitalWrite(myDataPin6, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin1, pinState);
    digitalWrite(myDataPin3, pinState);
    digitalWrite(myDataPin5, pinState);
 //   digitalWrite(myDataPin1, 0);
 //   digitalWrite(myDataPin2, pinState);
    digitalWrite(myDataPin2, 0);
    digitalWrite(myDataPin4, 0);
    digitalWrite(myDataPin6, 0);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
    digitalWrite(myDataPin3, 0);
    digitalWrite(myDataPin4, 0);
    digitalWrite(myDataPin5, 0);
    digitalWrite(myDataPin6, 0);
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}


// the heart of the program
void shiftOut41(int myDataPin1, int myDataPin2, int myDataPin3, int myDataPin4, int myDataPin5, int myDataPin6, int myClockPin, byte myDataOut1, byte myDataOut2) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState1, pinState2;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);
  pinMode(myDataPin3, OUTPUT);
  pinMode(myDataPin4, OUTPUT);
  pinMode(myDataPin5, OUTPUT);
  pinMode(myDataPin6, OUTPUT);
  
  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myDataPin3, 0);
  digitalWrite(myDataPin4, 0);
  digitalWrite(myDataPin5, 0);
  digitalWrite(myDataPin6, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut1 & (1<<i) ) {
      pinState1 = 1;
    }
    else {  
      pinState1 = 0;
    }
    if ( myDataOut2 & (1<<i) ) {
      pinState2 = 1;
    }
    else {  
      pinState2 = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
//    digitalWrite(myDataPin1, pinState);
    digitalWrite(myDataPin1, pinState1);
    digitalWrite(myDataPin3, pinState1);
    digitalWrite(myDataPin5, pinState1);
    digitalWrite(myDataPin2, pinState2);
    digitalWrite(myDataPin4, pinState2);
    digitalWrite(myDataPin6, pinState2);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
    digitalWrite(myDataPin3, 0);
    digitalWrite(myDataPin4, 0); 
    digitalWrite(myDataPin5, 0);
    digitalWrite(myDataPin6, 0); 
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}

// the heart of the program
void shiftOut42(int myDataPin1, int myDataPin2, int myDataPin3, int myDataPin4, int myDataPin5, int myDataPin6, int myClockPin, byte myDataOut1, byte myDataOut2) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState1, pinState2;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin1, OUTPUT);
  pinMode(myDataPin2, OUTPUT);
  pinMode(myDataPin3, OUTPUT);
  pinMode(myDataPin4, OUTPUT);
  pinMode(myDataPin5, OUTPUT);
  pinMode(myDataPin6, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin1, 0);
  digitalWrite(myDataPin2, 0);
  digitalWrite(myDataPin3, 0);
  digitalWrite(myDataPin4, 0);
  digitalWrite(myDataPin5, 0);
  digitalWrite(myDataPin6, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut1 & (1<<i) ) {
      pinState1 = 1;
    }
    else {  
      pinState1 = 0;
    }
    if ( myDataOut2 & (1<<i) ) {
      pinState2 = 1;
    }
    else {  
      pinState2 = 0;
    }


    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin1, pinState1);
    digitalWrite(myDataPin3, pinState1);
    digitalWrite(myDataPin5, pinState1);
 //   digitalWrite(myDataPin1, 0);
 //   digitalWrite(myDataPin2, pinState);
    digitalWrite(myDataPin2, pinState2);
    digitalWrite(myDataPin4, pinState2);
    digitalWrite(myDataPin6, pinState2);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin1, 0);
    digitalWrite(myDataPin2, 0);
    digitalWrite(myDataPin3, 0);
    digitalWrite(myDataPin4, 0);
    digitalWrite(myDataPin5, 0);
    digitalWrite(myDataPin6, 0);
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}

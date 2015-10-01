/*
  use Shift Register Example - https://www.arduino.cc/en/Tutorial/ShftOut13
  sketch version 4m1s1 - 01.10.2015, Craiova - Romania
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

int spid = 300;  // time between moving text/image
int spid2 = 2000; // time between texts
#include <DHT.h>
#define DHTPIN A2     // what pin we're connected the DHT output
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22 
DHT dht(DHTPIN, DHTTYPE);


// MATRIX DATA 16/8
byte baza3[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

byte numar[] = {0,0,0,0,0,0,
               0,0,0,0,0,0,
               0,0,0,0,0,0,
               0,0,0,0,0,0,
               0,0,0,0,0,0,
               0,0,0,0,0,0,
               0,0,0,0,0,0,
               0,0,0,0,0,0 };

byte gol[] = {0,0,0,0,0,0,
              0,0,0,0,0,0,
              0,0,0,0,0,0,
              0,0,0,0,0,0,
              0,0,0,0,0,0,
              0,0,0,0,0,0,
              0,0,0,0,0,0,
              0,0,0,0,0,0 };

byte unu[] = {0,0,1,0,0,0,
              0,0,1,0,0,0,
              0,1,1,0,0,0,
              1,0,1,0,0,0,
              0,0,1,0,0,0,
              0,0,1,0,0,0,
              0,0,1,0,0,0,
              1,1,1,1,1,0 };

byte doi[] = {0,1,1,1,0,0,
              1,0,0,0,1,0,
              0,0,0,0,1,0,
              0,0,0,1,0,0,
              0,0,1,0,0,0,
              0,1,0,0,0,0,
              1,0,0,0,0,0,
              1,1,1,1,1,0 };

byte trei[] = {0,1,1,1,0,0,
               1,0,0,0,1,0,
               0,0,0,0,1,0,
               0,0,1,1,0,0,
               0,0,0,0,1,0,
               0,0,0,0,1,0,
               1,0,0,0,1,0,
               0,1,1,1,0,0 };

byte patru[] = {0,0,1,0,1,0,
                0,1,0,0,1,0,
                1,0,0,0,1,0,
                1,0,0,0,1,0,
                1,1,1,1,1,0,
                0,0,0,0,1,0,
                0,0,0,0,1,0,
                0,0,0,0,1,0 };

byte cinci[] = {1,1,1,1,1,0,
                1,0,0,0,0,0,
                1,0,0,0,0,0,
                1,1,1,1,0,0,
                0,0,0,0,1,0,
                0,0,0,0,1,0,
                1,0,0,0,1,0,
                0,1,1,1,0,0 };

byte sase[] = {0,1,1,1,0,0,
               1,0,0,0,1,0,
               1,0,0,0,0,0,
               1,1,1,1,0,0,
               1,0,0,0,1,0,
               1,0,0,0,1,0,
               1,0,0,0,1,0,
               0,1,1,1,0,0 };

byte sapte[] = {1,1,1,1,1,0,
                0,0,0,0,1,0,
                0,0,0,0,1,0,
                0,0,0,1,0,0,
                0,0,0,1,0,0,
                0,0,1,0,0,0,
                0,0,1,0,0,0,
                0,0,1,0,0,0 };

byte opt[] = {0,1,1,1,0,0,
              1,0,0,0,1,0,
              1,0,0,0,1,0,
              0,1,1,1,0,0,
              1,0,0,0,1,0,
              1,0,0,0,1,0,
              1,0,0,0,1,0,
              0,1,1,1,0,0 };

byte noua[] = {0,1,1,1,0,0,
               1,0,0,0,1,0,
               1,0,0,0,1,0,
               0,1,1,1,1,0,
               0,0,0,0,1,0,
               0,0,0,0,1,0,
               1,0,0,0,1,0,
               0,1,1,1,0,0 };

byte zero[] = {0,1,1,1,0,0,
               1,0,0,0,1,0,
               1,0,0,1,1,0,
               1,0,1,0,1,0,
               1,0,1,0,1,0,
               1,1,0,0,1,0,
               1,0,0,0,1,0,
               0,1,1,1,0,0 };
              
byte plus[] = {0,0,0,0,
               0,0,0,0,
               0,1,0,0,
               1,1,1,0,
               0,1,0,0,
               0,0,0,0,
               0,0,0,0,
               0,0,0,0};
               
byte minus[] = {0,0,0,0,
               0,0,0,0,
               0,0,0,0,
               1,1,1,0,
               0,0,0,0,
               0,0,0,0,
               0,0,0,0,
               0,0,0,0};
 
byte virgula[] = {0,0,
                  0,0,
                  0,0,
                  0,0,
                  0,0,
                  0,0,
                  1,0,
                  1,0};

byte gradC[] = {0,1,0,0,0,1,1,0,
                1,0,1,0,1,0,0,1,
                1,0,1,0,1,0,0,0,
                0,1,0,0,1,0,0,0,
                0,0,0,0,1,0,0,0,
                0,0,0,0,1,0,0,0,
                0,0,0,0,1,0,0,1,
                0,0,0,0,0,1,1,0};

byte procent[] = {0,0,1,0,0,0,0,0,
                  0,1,0,1,0,0,1,0,
                  0,0,1,0,0,1,0,0,
                  0,0,0,0,1,0,0,0,
                  0,0,0,1,0,0,0,0,
                  0,0,1,0,0,1,0,0,
                  0,1,0,0,1,0,1,0,
                  0,0,0,0,0,1,0,0};
                  
byte r[] = {0,0,0,0,0,0,
            0,0,0,0,0,0,
            0,0,0,0,0,0,
            1,1,1,1,0,0,
            1,0,0,0,1,0,
            1,0,0,0,0,0,
            1,0,0,0,0,0,
            1,0,0,0,0,0};
            
byte h[] = {1,0,0,0,0,0,
            1,0,0,0,0,0,
            1,0,0,0,0,0,
            1,1,1,1,0,0,
            1,0,0,0,1,0,
            1,0,0,0,1,0,
            1,0,0,0,1,0,        
            1,0,0,0,1,0};



void setup() {
 //  Serial.begin(9600);
   dht.begin();  
   
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

clearAll_2Bytes(4,512); 
}


void loop() {
 
for (byte n = 2; n <= 4; n++) {      
for (byte m = 2; m <= 4; m++) {    
for (byte l = 2; l <= 4; l++) {  
clearAll_2Bytes(4,512); 
// conversie();
float ti = dht.readTemperature();
delay(1000);
temperatura(ti);

  for (int j = 0; j < 8; j++) {
    digitalWrite(latchPin, 0);
 shiftOut41(l, l+3, m, m+3, n, n+3, clockPin, dataArray[4*j], dataArray[4*j+2]);
    digitalWrite(latchPin, 1);
    digitalWrite(latchPin, 0);
 shiftOut42(l, l+3, m, m+3, n, n+3, clockPin, dataArray[4*j+1], dataArray[4*j+3]);
    digitalWrite(latchPin, 1);
    delay(spid);
  }
delay(spid2);
clearAll_2Bytes(2,512); 
 
int h = dht.readHumidity();
delay(1000);
umiditate(h);
for (int j = 0; j < 8; j++) {
    digitalWrite(latchPin, 0);
 shiftOut41(l, l+3, m, m+3, n, n+3, clockPin, dataArray[4*j], dataArray[4*j+2]);
    digitalWrite(latchPin, 1);
    digitalWrite(latchPin, 0);
 shiftOut42(l, l+3, m, m+3, n, n+3, clockPin, dataArray[4*j+1], dataArray[4*j+3]);
    digitalWrite(latchPin, 1);
    delay(spid);
  }
delay(spid2);
//  clearAll_2Bytes(2,500); 
}
}
}
 
} // end main loop


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

void temperatura(float te){
// clear matrix;
for (byte y=0; y<255; y++)  {  
baza3[y]=0;
}

Serial.println(te);
// finding numbers
int te0 = te*10;  // x 10;
if (te0 <0) te0 = -te0;
Serial.println(te0);
int te1 = te0/100;  // first number
Serial.println(te1);
int te4 = te0 - 100*te1;
int te2 = te4/10;  // second number
Serial.println(te2);
int te3 = te4 - 10*te2;  // last number
Serial.println(te3);
Serial.println("------------------");

// for temperature with 2 number
if (te0 >= 100) {
byte l = 4;
if (te >= 0)  {
  // plus 
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=plus[l*x+y];
  }
}
}
else {
te = -te;
  // minus 
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=minus[l*x+y];
  }
}
}

// display first number
byte l2 = 6;
if (te1 == 0) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=zero[l2*x+y];
}
}
}
// if is 1
if (te1 == 1) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=unu[l2*x+y];
  }
}
}
// if is 2
if (te1 == 2) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=doi[l2*x+y];
}
}
}
// if is 3
if (te1 == 3) {
//byte l2 = 6;
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=trei[l2*x+y];
}
}
}
// if is 4
if (te1 == 4) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=patru[l2*x+y];
}
}
}
// if is 5
if (te1 == 5) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=cinci[l2*x+y];
}
}
}
// if is 6
if (te1 == 6) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=sase[l2*x+y];
}
}
}
// if is 7
if (te1 == 7) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=sapte[l2*x+y];
}
}
}
// if is 8
if (te1 == 8) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=opt[l2*x+y];
}
}
}
// if is 9
if (te1 == 9) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=noua[l2*x+y];
}
}
}
}  // enf if
else {
// display nofill ....
byte l = 6;
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=gol[l*x+y];
}
}
  
byte l2 = 4;
if (te >= 0)  {
  // plus 
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l2; y++)  {  
//baza3[32*x+y]=plus[l*x+y];
baza3[32*x+y+l]=plus[l2*x+y];
  }
}
}
else {
te = -te;
  // minus 
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l2; y++)  {  
baza3[32*x+y]=minus[l2*x+y];
//baza3[32*x+y+l]=zero[l2*x+y];
  }
}
}
}

byte l = 4;
byte l2 = 6;
// te2 = 3;
// second number
byte l3 = 6;
// if is zero
if (te2 == 0) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=zero[l3*x+y];
}
}
}

// if is 1
if (te2 == 1) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=unu[l3*x+y];
}
}
}
// if is 2
if (te2 == 2) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=doi[l3*x+y];
}
}
}
// if is 3
if (te2 == 3) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=trei[l3*x+y];
}
}
}
// if is 4
if (te2 == 4) {
//byte l2 = 6;
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=patru[l3*x+y];
}
}
}
// if is 5
if (te2 == 5) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=cinci[l3*x+y];
}
}
}
// if is 6
if (te2 == 6) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=sase[l3*x+y];
}
}
}
// if is 7
if (te2 == 7) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=sapte[l3*x+y];
}
}
}
// if is 8
if (te2 == 8) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=opt[l3*x+y];
}
}
}
// if is 9
if (te2 == 9) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=noua[l3*x+y];
}
}
}

// virgula
byte l4 = 2;
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l4; y++)  {  
baza3[32*x+y+l+l2+l3]=virgula[l4*x+y];
   }
}


// third number
//int te3 == 6;
byte l5 = 6;
/*
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l5; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=numar[l5*x+y];
   }
}
*/

// if is zero
if (te3 == 0) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=zero[l5*x+y];
}
}
}
// if is 1
if (te3 == 1) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=unu[l5*x+y];
}
}
}
// if is 2
if (te3 == 2) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=doi[l5*x+y];
}
}
}
// if is 3
if (te3 == 3) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=trei[l5*x+y];
}
}
}
// if is 4
if (te3 == 4) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=patru[l5*x+y];
}
}
}
// if is 5
if (te3 == 5) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=cinci[l5*x+y];
}
}
}
// if is 6
if (te3 == 6) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=sase[l5*x+y];
}
}
}
// if is 7
if (te3 == 7) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=sapte[l5*x+y];
}
}
}
// if is 8
if (te3 == 8) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=opt[l5*x+y];
}
}
}
// if is 9
if (te3 == 9) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=noua[l5*x+y];}
}
}



// grad Celsius
byte l6 = 8;
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l6; y++)  {  
baza3[32*x+y+l+l2+l3+l4+l5]=gradC[l6*x+y];
}
}

for (byte x=0; x<=3; x++)  {
  for (byte y=0; y<=7; y++)  {
dataArray[x+4*y] = 128*baza3[32*2*x+4*y] + 64*baza3[32*2*x+1+4*y] + 32*baza3[32*2*x+2+4*y] + 16*baza3[32*2*x+3+4*y] + 8*baza3[32*(2*x+1)+4*y] + 4*baza3[32*(2*x+1)+1+4*y] + 2*baza3[32*(2*x+1)+2+4*y] + baza3[32*(2*x+1)+3+4*y]; 
}
}
}



void umiditate(int hasi){
// clear matrix;
for (byte y=0; y<255; y++)  {  
baza3[y]=0;
}
  
  
Serial.println(hasi);
// finding numbers
int h1 = hasi/10;  // first number
Serial.println(h1);
int h2 = hasi - 10*h1;  // last number
Serial.println(h2);
Serial.println("------------------");

// display first number
byte l = 6;
if (h1 == 0) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=zero[l*x+y];
}
}
}
// if is 1
if (h1 == 1) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=unu[l*x+y];
  }
}
}
// if is 2
if (h1 == 2) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=doi[l*x+y];
}
}
}
// if is 3
if (h1 == 3) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=trei[l*x+y];
}
}
}
// if is 4
if (h1 == 4) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=patru[l*x+y];
}
}
}
// if is 5
if (h1 == 5) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=cinci[l*x+y];
}
}
}
// if is 6
if (h1 == 6) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=sase[l*x+y];
}
}
}
// if is 7
if (h1 == 7) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=sapte[l*x+y];
}
}
}
// if is 8
if (h1 == 8) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=opt[l*x+y];
}
}
}
// if is 9
if (h1 == 9) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l; y++)  {  
baza3[32*x+y]=noua[l*x+y];
}
}
}


// display second number
byte l2 = 6;
if (h2 == 0) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=zero[l2*x+y];
}
}
}
// if is 1
if (h2 == 1) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=unu[l2*x+y];
  }
}
}
// if is 2
if (h2 == 2) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=doi[l2*x+y];
}
}
}
// if is 3
if (h2 == 3) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=trei[l2*x+y];
}
}
}
// if is 4
if (h2 == 4) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=patru[l2*x+y];
}
}
}
// if is 5
if (h2 == 5) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=cinci[l2*x+y];
}
}
}
// if is 6
if (h2 == 6) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=sase[l2*x+y];
}
}
}
// if is 7
if (h2 == 7) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=sapte[l2*x+y];
}
}
}
// if is 8
if (h2 == 8) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=opt[l2*x+y];
}
}
}
// if is 9
if (h2 == 9) {
for (byte x=0; x<=7; x++)  {  
for (byte y=0; y<l2; y++)  {  
baza3[32*x+y+l]=noua[l2*x+y];
}
}
}

// procent
byte l3 = 8;
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l3; y++)  {  
baza3[32*x+y+l+l2]=procent[l3*x+y];
}
}

// r
byte l4 = 6;
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l4; y++)  {  
baza3[32*x+y+l+l2+l3]=r[l4*x+y];
}
}

// h
byte l5 = 6;
for (byte x=0; x<=7; x++)  {  
  for (byte y=0; y<l5; y++)  {  
baza3[32*x+y+l+l2+l3+l4]=h[l5*x+y];
}
}


for (byte x=0; x<=3; x++)  {
  for (byte y=0; y<=7; y++)  {
dataArray[x+4*y] = 128*baza3[32*2*x+4*y] + 64*baza3[32*2*x+1+4*y] + 32*baza3[32*2*x+2+4*y] + 16*baza3[32*2*x+3+4*y] + 8*baza3[32*(2*x+1)+4*y] + 4*baza3[32*(2*x+1)+1+4*y] + 2*baza3[32*(2*x+1)+2+4*y] + baza3[32*(2*x+1)+3+4*y]; 
}
}
}


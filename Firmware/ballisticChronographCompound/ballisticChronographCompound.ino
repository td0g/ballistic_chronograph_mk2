/*
  Firmware for Ballistic Chronograph
  Written by Tyler Gerritsen
  vtgerritsen@gmail.com
  www.td0g.ca

DESCRIPTION:
  Basic firmware for an Arduino-based ballistic chronograph with 2 - 6 gates.  Connect the Arduino to a PC and it will automatically read out the speed.  
  This firmware uses Timer1 to measure the time between gate transits.

CHANGELOG:
1.0
  2020-07-04
  Initial Release
2.0
  2020-07-16
  Using watchdog timer for timeout function, this improves sampling speed
  Added individual gate separation override

LICENSE:
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */






//SETUP ####################################################################################
//Definitions - PLEASE SET UP BEFORE USING

 //Serial port baud rate
#define BAUD 9600       

//Default distance in mm between each pair of gates (NOT the entire length of multi-sensor array).  This distance can be overwritten by the individual gate separations below.
#define GATE_SEPARATION_DEFAULT 287.0 

//Override the individual gate separations here (OPTIONAL)
//#define GATE_AB_SEPARATION 287.0
//#define GATE_BC_SEPARATION 287.0
//#define GATE_CD_SEPARATION 287.0
//#define GATE_DE_SEPARATION 287.0
//#define GATE_EF_SEPARATION 287.0

//Enter the Arduino pin of the sensor input.  For A0, use 14.  A1, use 15. A2, use 16.  A3, use 17.  A4, use 18.  A5, use 19.  Gates A and B required.  Gates C, D, E, F are optional.
#define GATE_A_PIN 14
#define GATE_B_PIN 15      
#define GATE_C_PIN 16
#define GATE_D_PIN 17
#define GATE_E_PIN 18
#define GATE_F_PIN 19

//Active low means 0V is a gate trigger.  COMMENT OUT for active high (5V = gate is triggered). 
#define ACTIVE_LOW    

//Gate pins are pulled up.  COMMENT OUT to disable pullup resistors.
//#define PULLUP              

//Milliseconds between each gate before test resets. Valid values = 16, 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000
//Note that this will limit the time to output Serial data.  Use BAUD 57600 or higher if MAX_TRANSIT_TIME is less than 64.
#define MAX_TRANSIT_TIME 1000

//END OF SETUP ##############################################################################






//Other files
  #include <avr/wdt.h>
  #include "defs.h"
  
//Declare variables
  const unsigned int serialDelay = (unsigned long) 60000000 / BAUD;
  const float mTOf = 3.280;
  float gateSeparation[GATE_COUNT - 1] = GATE_SEPARATION_ARRAY;
  volatile byte ovfCount;
  volatile unsigned long testTime1; //This is the timer count
  volatile unsigned long testOvf1;  //This is the timer overflow count
  #ifdef GATE_C_PIN
    volatile unsigned long testTime2;
    volatile unsigned long testOvf2;
    #ifdef GATE_D_PIN
      volatile unsigned long testTime3;
      volatile unsigned long testOvf3;
      #ifdef GATE_E_PIN
        volatile unsigned long testTime4;
        volatile unsigned long testOvf4;
        #ifdef GATE_F_PIN
          volatile unsigned long testTime5;
          volatile unsigned long testOvf5;
        #endif
      #endif
    #endif
  #endif
  #define TAB Serial.print(F("\t")); Serial.print(F("\t"))
  
void setup() {
//Setup pin states
  #ifdef PULLUP
    pinMode(GATE_A_PIN, INPUT_PULLUP);
    pinMode(GATE_B_PIN, INPUT_PULLUP);
    #ifdef GATE_C_PIN
      pinMode(GATE_C_PIN, INPUT_PULLUP);
      #ifdef GATE_D_PIN
        pinMode(GATE_D_PIN, INPUT_PULLUP);
        #ifdef GATE_E_PIN
          pinMode(GATE_E_PIN, INPUT_PULLUP);
          #ifdef GATE_F_PIN
            pinMode(GATE_F_PIN, INPUT_PULLUP);
          #endif
        #endif
      #endif
    #endif
  #endif

//Setup timer1
  TCCR1A = 0; //No pin changes needed
  TCCR1B = (TCCR1B & 0b11100000) | 0b00000010;         // div8 = 1/2us per increment, 16-bit normal mode
  TIMSK1 |= 1;  //Turn on overflow interrupt
  
//Start communicating with PC
  Serial.begin(BAUD);   
  Serial.println("\n\nBallistic Chronograph - READY");  //Hello world message
  Serial.print(F("Max transit time per gate: "));
  Serial.print(MAX_TRANSIT_TIME);
  Serial.println(F(" ms"));
  delay(100);
}

void loop(){
//Reset variables
  testTime1 = 0;
  testOvf1 = 0;
  
//Turn off interrupts so that the microcontroller can focus on watching the gates
  disableInterrupts();
    
//Wait until GATE A gives a signal
  while (GATE_A) {};

//Reset Timer1 counter and overflow counter to 0
  TCNT1 = 0;
  ovfCount = 0;

//Turn on the watchdog timer
  cli();
  wdt_reset();
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = WDT_ON;
  sei();
  wdt_reset();

//Wait until GATE B gives a signal OR timeout happens.  If timeout happened, just end test.
  while(GATE_B) {};
  testTime1 = TCNT1;
  testOvf1 = ovfCount;
  wdt_reset();

  #ifdef GATE_C_PIN
    testTime2 = 0;
    testOvf2 = 0;
    while(GATE_C) {};
    testTime2 = TCNT1;
    testOvf2 = ovfCount;
    wdt_reset();
    
    #ifdef GATE_D_PIN
      testTime3 = 0;
      testOvf3 = 0;
      while(GATE_D_PIN2) {};
      testTime3 = TCNT1;
      testOvf3 = ovfCount;
      wdt_reset();
      
      #ifdef GATE_E_PIN
        testTime4 = 0;
        testOvf4 = 0;
        while(GATE_E_PIN2) {};
        testTime4 = TCNT1;
        testOvf4 = ovfCount;
        wdt_reset();
        
        #ifdef GATE_F_PIN
          testTime5 = 0;
          testOvf5 = 0;
          while(GATE_F_PIN2) {};
          testTime5 = TCNT1;
          testOvf5 = ovfCount;
          wdt_reset();
        #endif
      #endif
    #endif
  #endif
  

//Enable interrupts so that Serial functions work
  cli();
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 0;
  sei();
  enableInterrupts();

//Display stats
  double objectSpeed;
  Serial.println();
  Serial.println(F("Sensor# | Time in uS from previous gate | Time in uS from first gate | Speed in m/s | Speed in fps: "));
  Serial.print(F("1-2:"));
  TAB;
  testOvf1 = testOvf1 << 16;
  testTime1 += testOvf1;
  Serial.print(testTime1 / 2);
  TAB;
  Serial.print(testTime1 / 2);
  TAB;
  objectSpeed = gateSeparation[0];
  objectSpeed *= 2000;
  objectSpeed /= testTime1;
  Serial.print(objectSpeed);
  objectSpeed *= mTOf;
  TAB;
  Serial.println(objectSpeed);
  #ifdef GATE_C_PIN
    Serial.print(F("2-3:"));
    TAB;
    testOvf2 = testOvf2 << 16;
    testTime2 += testOvf2;
    Serial.print((testTime2 - testTime1) / 2);
    TAB;
    Serial.print(testTime2 / 2);
    TAB;
    objectSpeed = gateSeparation[1];
    objectSpeed *= 2000;
    objectSpeed /= (testTime2 - testTime1);
    Serial.print(objectSpeed);
    TAB;
    objectSpeed *= mTOf;
    Serial.println(objectSpeed);
    #ifdef GATE_D_PIN
      Serial.print(F("3-4:"));
      TAB;
      testOvf3 = testOvf3 << 16;
      testTime3 += testOvf3;
      Serial.print((testTime3 - testTime2) / 2);
      TAB;
      Serial.print(testTime3 / 2);
      TAB;
      objectSpeed = gateSeparation[2];
      objectSpeed *= 2000;
      objectSpeed /= (testTime3 - testTime2);
      Serial.print(objectSpeed);
      objectSpeed *= mTOf;
      TAB;
      Serial.println(objectSpeed);
      #ifdef GATE_E_PIN
        Serial.print(F("4-5:"));
        TAB;
        testOvf4 = testOvf4 << 16;
        testTime4 += testOvf4;
        Serial.print((testTime4 - testTime3) / 2);
        TAB;
        Serial.print(testTime4 / 2);
        TAB;
        objectSpeed = gateSeparation[3];
        objectSpeed *= 2000;
        objectSpeed /= (testTime4 - testTime3);
        Serial.print(objectSpeed);
        TAB;
        objectSpeed *= mTOf;
        Serial.println(objectSpeed);
        #ifdef GATE_F_PIN
          Serial.print(F("5-6:"));
          TAB;
          testOvf5 = testOvf5 << 16;
          testTime5 += testOvf5;
          Serial.print((testTime5 - testTime4) / 2);
          TAB;
          Serial.print(testTime5 / 2);
          TAB;
          objectSpeed = gateSeparation[4];
          objectSpeed *= 2000;
          objectSpeed /= (testTime5 - testTime4);
          Serial.print(objectSpeed);
          objectSpeed *= mTOf;
          TAB;
          Serial.println(objectSpeed);
        #endif
      #endif
    #endif
  #endif

//Wait until Serial is all finished
    delay(250);
  }


ISR(WDT_vect){
//This is called when the first gate is transit but some of the others are not.
//Cannot use Serial.print() here, so use the serialChar function instead.
//Really should edit the function to accept char arrays or strings...
  serialChar('T');
  serialChar('I');
  serialChar('M');
  serialChar('E');
  serialChar('O');
  serialChar('U');
  serialChar('T');
  serialChar('\n');
  serialChar('T');
  serialChar('i');
  serialChar('m');
  serialChar('e');
  serialChar(':');
  unsigned long _t;
  for (byte j = 0; j < 4; j++){
    char _c[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};
    serialChar('\t');
    serialChar('\t');
    switch (j){
      case 0: testOvf1 = testOvf1 << 16; testTime1 = testOvf1 + testTime1; _t = testTime1; break;
      case 1: testOvf2 = testOvf2 << 16; testTime2 = testOvf2 + testTime2; _t = testTime2;  break;
      case 2: testOvf3 = testOvf3 << 16; testTime3 = testOvf3 + testTime3; _t = testTime3;  break;
      case 3: testOvf4 = testOvf4 << 16; testTime4 = testOvf4 + testTime4; _t = testTime4;  break;
    }
    if (_t){
      ltoa(_t, _c, 10);
      for (byte i = 0; i < 7; i++) serialChar(_c[i]);
    }
  }  
  serialChar('\n');
  serialChar('d');
  serialChar('T');
  serialChar(':');
  serialChar(' ');
  serialChar(' ');
  if (testTime4) testTime4 -= testTime3;
  if (testTime3) testTime3 -= testTime2;
  if (testTime2) testTime2 -= testTime1;
  for (byte j = 0; j < 4; j++){
    char _c[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};
    serialChar('\t');
    serialChar('\t');
    switch (j){
      case 0: _t = testTime1;  break;
      case 1: _t = testTime2; break;
      case 2: _t = testTime3; break;
      case 3: _t = testTime4; break;
    }
    if (_t){
      ltoa(_t, _c, 10);
      for (byte i = 0; i < 7; i++) serialChar(_c[i]);
    }
  }
  serialChar('\n');
  serialChar('S');
  serialChar('p');
  serialChar('e');
  serialChar('e');
  serialChar('d');
  serialChar(':');
  for (byte j = 0; j < 4; j++){
    char _c[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};
    serialChar('\t');
    serialChar('\t');
    float _s = gateSeparation[j] * 2000;
    switch (j){
      case 0: _s = _s / testTime1;  break;
      case 1: _s = _s / testTime2; break;
      case 2: _s = _s / testTime3; break;
      case 3: _s = _s / testTime4; break;
    }
    if (_s > 0.001 && _s < 1000000){
      unsigned long _t = _s;
      ltoa(_t, _c, 10);
      for (byte i = 0; i < 8; i++)serialChar(_c[i]);
    }
  }
}

void serialChar(char _c){
  UDR0 = _c; //https://forum.arduino.cc/index.php?topic=86485.0
  for (unsigned long t = 0; t < serialDelay / 3; t++) __asm__ __volatile__ ("nop\n\t");
}

ISR(TIMER1_OVF_vect) {
  ovfCount++;
}

void disableInterrupts(){
  editInterrupts(0);
}

void enableInterrupts(){
  editInterrupts(1);
}

void editInterrupts(byte _s){
  static byte _tccr0b;
  static byte _tccr2b;
  static byte _intState = 1;
  if (_s != _intState){
    if (!_s){
      _intState = 0;
      _tccr0b = TCCR0B;
      _tccr2b = TCCR2B;
      TCCR0B |= 0b11111000;
      TCCR2B |= 0b11111000;
    }
    else {
      _intState = 1;
      TCCR0B = _tccr0b;
      TCCR2B = _tccr2b;
    }
  }
}

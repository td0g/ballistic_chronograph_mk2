/*
  Firmware for Ballistic Chronograph
  Written by Tyler Gerritsen
  vtgerritsen@gmail.com
  www.td0g.ca

DESCRIPTION:
  Basic firmware for an Arduino-based ballistic chronograph with 2 - 6 gates.  Connect the Arduino to a PC and it will automatically read out the speed.  
  This firmware uses Timer1 to measure the time between gate transits.
  This firmware is optimized for high-speed testing and the minimum gate to gate time is 14 microseconds

CHANGELOG:
1.0
  2020-07-04
  Initial Release
1.1
  2020-07-16
  Using watchdog timer for timeout function, this improves sampling speed
  Added individual gate separation override

1.2
  2020-07-21
  Improvements to interrupt disabling function
  Added acceleration calucations
  Added string-printing and integer-printing function for interurpt routine (easier to read code)
  Optimized watchdog serial speed
  Improved code readability
  
1.3
  2021-06-25
  Increased maximum gates from 6 to 16
  Added diagnostics check to beginning of routine

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
#define GATE_AB_SEPARATION 286.9
#define GATE_BC_SEPARATION 573.4-286.9
#define GATE_CD_SEPARATION 860.7-573.4
#define GATE_DE_SEPARATION 1146.6-860.7
#define GATE_EF_SEPARATION 1136.4-848.6
#define GATE_FG_SEPARATION 1136.4-848.6
#define GATE_GH_SEPARATION 1136.4-848.6
#define GATE_HI_SEPARATION 1136.4-848.6
#define GATE_IJ_SEPARATION 1136.4-848.6
#define GATE_JK_SEPARATION 1136.4-848.6
#define GATE_KL_SEPARATION 1136.4-848.6
#define GATE_LM_SEPARATION 1136.4-848.6
#define GATE_MN_SEPARATION 1136.4-848.6
#define GATE_NO_SEPARATION 1136.4-848.6
//#define GATE_OP_SEPARATION 1136.4-848.6

//Enter the Arduino pin of the sensor input.  For A0, use 14.  A1, use 15. A2, use 16.  A3, use 17.  A4, use 18.  A5, use 19.  Gates A and B required.  Gates C through P are optional.
#define GATE_A_PIN 14
#define GATE_B_PIN 15
#define GATE_C_PIN 16
#define GATE_D_PIN 17
#define GATE_E_PIN 18
#define GATE_F_PIN 19
//#define GATE_G_PIN 19
//#define GATE_H_PIN 19
//#define GATE_I_PIN 19
//#define GATE_J_PIN 19
//#define GATE_K_PIN 19
//#define GATE_L_PIN 19
//#define GATE_M_PIN 19
//#define GATE_N_PIN 19
//#define GATE_O_PIN 19
//#define GATE_P_PIN 19

//Active low means 0V is a gate trigger.  COMMENT OUT for active high (5V = gate is triggered). 
#define ACTIVE_LOW    

//Gate pins are pulled up.  COMMENT OUT to disable pullup resistors.
//#define PULLUP              

//Milliseconds between each gate before test resets. Valid values = 16, 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000
//Note that this will limit the time to output Serial data.  Use BAUD 57600 or higher if MAX_TRANSIT_TIME is less than 64.
#define MAX_TRANSIT_TIME 1000

//Number of times to perform diagnostics check before each test.  COMMENT OUT to disable check
#define DIAGNOSTICS_CHECKS 100000

//END OF SETUP ##############################################################################






//Other files
  #include <avr/wdt.h>
  #include "defs.h"
  
//Declare variables
  unsigned int testIndex = 0;
  const float mTOf = 3.280;
  float gateSeparation[GATE_COUNT - 1] = GATE_SEPARATION_ARRAY;
  volatile byte ovfCount;
  volatile unsigned long testTimes[GATE_COUNT-1];
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
          #ifdef GATE_G_PIN
            volatile unsigned long testTime6;
            volatile unsigned long testOvf6;
            #ifdef GATE_H_PIN
              volatile unsigned long testTime7;
              volatile unsigned long testOvf7;
              #ifdef GATE_I_PIN
                volatile unsigned long testTime8;
                volatile unsigned long testOvf8;
                #ifdef GATE_J_PIN
                  volatile unsigned long testTime9;
                  volatile unsigned long testOvf9;
                  #ifdef GATE_K_PIN
                    volatile unsigned long testTime10;
                    volatile unsigned long testOvf10;
                    #ifdef GATE_L_PIN
                      volatile unsigned long testTime11;
                      volatile unsigned long testOvf11;
                      #ifdef GATE_M_PIN
                        volatile unsigned long testTime12;
                        volatile unsigned long testOvf12;
                        #ifdef GATE_N_PIN
                          volatile unsigned long testTime13;
                          volatile unsigned long testOvf13;
                          #ifdef GATE_O_PIN
                            volatile unsigned long testTime14;
                            volatile unsigned long testOvf14;
                            #ifdef GATE_P_PIN
                              volatile unsigned long testTime15;
                              volatile unsigned long testOvf15;
                            #endif
                          #endif
                        #endif
                      #endif
                    #endif
                  #endif
                #endif
              #endif
            #endif
          #endif
        #endif
      #endif
    #endif
  #endif
  #define TAB Serial.print(F("\t")); Serial.print(F("\t"))
  
void setup() {
//Setup pin states
  setPinStates();

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
  runDiagnostics();
  
//Reset variables
  testTime1 = 0;
  testOvf1 = 0;
  for (byte i = 0; i < GATE_COUNT; i++) testTimes[i] = 0;
  
//Turn off interrupts so that the microcontroller can focus on watching the gates
  disableInterrupts();
    
//Wait until GATE A gives a signal
  while (GATE_A) {};
  
//Reset Timer1 counter and overflow counter to 0
  TCNT1 = 0;
  ovfCount = 0;
  testTimes[0] = 0;

//Turn on the watchdog timer
  cli();
  wdt_reset();
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = WDT_ON;
  sei();
  wdt_reset();

//Wait until each successive gate gives a signal OR timeout happens.  If timeout happened, just end test.
  while(GATE_B) {};
  testTime1 = TCNT1;
  testOvf1 = ovfCount;
  wdt_reset();
  testOvf1 = testOvf1 << 16;
  testTime1 += testOvf1;
  testTimes[1] = testTime1;

  #ifdef GATE_C_PIN
    testTime2 = 0;
    testOvf2 = 0;
    while(GATE_C) {};
    testTime2 = TCNT1;
    testOvf2 = ovfCount;
    wdt_reset();
    testOvf2 = testOvf2 << 16;
    testTime2 += testOvf2;
    testTimes[2] = testTime2;
    
    #ifdef GATE_D_PIN
      testTime3 = 0;
      testOvf3 = 0;
      while(GATE_D_PIN2) {};
      testTime3 = TCNT1;
      testOvf3 = ovfCount;
      wdt_reset();
      testOvf3 = testOvf3 << 16;
      testTime3 += testOvf3;
      testTimes[3] = testTime3;
      
      #ifdef GATE_E_PIN
        testTime4 = 0;
        testOvf4 = 0;
        while(GATE_E_PIN2) {};
        testTime4 = TCNT1;
        testOvf4 = ovfCount;
        wdt_reset();
        testOvf4 = testOvf4 << 16;
        testTime4 += testOvf4;
        testTimes[4] = testTime4;
        
        #ifdef GATE_F_PIN
          testTime5 = 0;
          testOvf5 = 0;
          while(GATE_F_PIN2) {};
          testTime5 = TCNT1;
          testOvf5 = ovfCount;
          wdt_reset();
          testOvf5 = testOvf5 << 16;
          testTime5 += testOvf5;
          testTimes[5] = testTime5;
        
          #ifdef GATE_G_PIN
            testTime6 = 0;
            testOvf6 = 0;
            while(GATE_G_PIN2) {};
            testTime6 = TCNT1;
            testOvf6 = ovfCount;
            wdt_reset();
            testOvf6 = testOvf6 << 16;
            testTime6 += testOvf6;
            testTimes[6] = testTime6;
        
            #ifdef GATE_H_PIN
              testTime7 = 0;
              testOvf7 = 0;
              while(GATE_H_PIN2) {};
              testTime7 = TCNT1;
              testOvf7 = ovfCount;
              wdt_reset();
              testOvf7 = testOvf7 << 16;
              testTime7 += testOvf7;
              testTimes[7] = testTime7;
        
              #ifdef GATE_I_PIN
                testTime8 = 0;
                testOvf8 = 0;
                while(GATE_I_PIN2) {};
                testTime8 = TCNT1;
                testOvf8 = ovfCount;
                wdt_reset();
                testOvf8 = testOvf8 << 16;
                testTime8 += testOvf8;
                testTimes[8] = testTime8;
        
                #ifdef GATE_J_PIN
                  testTime9 = 0;
                  testOvf9 = 0;
                  while(GATE_J_PIN2) {};
                  testTime9 = TCNT1;
                  testOvf9 = ovfCount;
                  wdt_reset();
                  testOvf9 = testOvf9 << 16;
                  testTime9 += testOvf9;
                  testTimes[9] = testTime9;
        
                  #ifdef GATE_K_PIN
                    testTime10 = 0;
                    testOvf10 = 0;
                    while(GATE_K_PIN2) {};
                    testTime10 = TCNT1;
                    testOvf10 = ovfCount;
                    wdt_reset();
                    testOvf10 = testOvf10 << 16;
                    testTime10 += testOvf10;
                    testTimes[10] = testTime10;
                    
                    #ifdef GATE_L_PIN
                      testTime11 = 0;
                      testOvf11 = 0;
                      while(GATE_L_PIN2) {};
                      testTime11 = TCNT1;
                      testOvf11 = ovfCount;
                      wdt_reset();
                      testOvf11 = testOvf11 << 16;
                      testTime11 += testOvf11;
                      testTimes[11] = testTime11;
        
                      #ifdef GATE_M_PIN
                        testTime12 = 0;
                        testOvf12 = 0;
                        while(GATE_M_PIN2) {};
                        testTime12 = TCNT1;
                        testOvf12 = ovfCount;
                        wdt_reset();
                        testOvf12 = testOvf12 << 16;
                        testTime12 += testOvf12;
                        testTimes[12] = testTime12;
        
                        #ifdef GATE_N_PIN
                          testTime13 = 0;
                          testOvf13 = 0;
                          while(GATE_N_PIN2) {};
                          testTime13 = TCNT1;
                          testOvf13 = ovfCount;
                          wdt_reset();
                          testOvf13 = testOvf13 << 16;
                          testTime13 += testOvf13;
                          testTimes[13] = testTime13;
                          
                          #ifdef GATE_O_PIN
                            testTime14 = 0;
                            testOvf14 = 0;
                            while(GATE_O_PIN2) {};
                            testTime14 = TCNT1;
                            testOvf14 = ovfCount;
                            wdt_reset();
                            testOvf14 = testOvf14 << 16;
                            testTime14 += testOvf14;
                            testTimes[14] = testTime14;
        
                            #ifdef GATE_P_PIN
                              testTime15 = 0;
                              testOvf15 = 0;
                              while(GATE_P_PIN2) {};
                              testTime15 = TCNT1;
                              testOvf15 = ovfCount;
                              wdt_reset();
                              testOvf15 = testOvf15 << 16;
                              testTime15 += testOvf15;
                              testTimes[15] = testTime15;
                            #endif
                          #endif
                        #endif
                      #endif
                    #endif
                  #endif
                #endif
              #endif
            #endif
          #endif
        #endif
      #endif
    #endif
  #endif
  
//Disable watchdog timer
  cli();
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 0;
  sei();
  
//Enable interrupts so that Serial functions work
  enableInterrupts();

//Display stats
  printStats();
  }


ISR(TIMER1_OVF_vect) {ovfCount++;}

/*
  Firmware for Ballistic Chronograph
  Written by Tyler Gerritsen
  vtgerritsen@gmail.com
  www.td0g.ca

DESCRIPTION:
  Very basic firmware for an Arduino-based ballistic chronograph.  Connect the Arduino to a PC and it will automatically read out the speed.  
  Can also display the speed on an LCD display using the LiquidCrystal library.

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
#define BAUD 9600           //Serial port baud rate
#define GATE_SEPARATION 500 //Distance in mm
#define TIMEOUT 2000        //Longest time something should take to cross both gates (in milliseconds)
#define GATE_A_PIN  PIN_A0  //Choose from the pins defined below
#define GATE_A_PIN2 A0      //Same as above, just write the pin in normal Arduino
#define GATE_B_PIN  PIN_A1  //Choose from the pins defined below
#define GATE_B_PIN2 A1      //Same as above, just write the pin in normal Arduino
#define ACTIVE_LOW          //Active low means 0V is a gate trigger.  COMMENT OUT for active high (5V = gate is triggered).  
#define PULLUP              //Gate pins are pulled up.  COMMENT OUT to disable pullup resistors.

//LCD Display - PLEASE SET UP BEFORE USING
#define LCD		                      //Comment out to disable the LCD output
#define LCD_PINS 8, 9, 4, 5, 6, 7   //RS, EN, D4, D5, D6, D7

//END OF SETUP ##############################################################################

//include the LiquidCrystal library:
  #ifdef LCD
    #include <LiquidCrystal.h>
    LiquidCrystal lcd(LCD_PINS);
  #endif
  
//include the Timer2 library:
  #include <eRCaGuy_Timer2_Counter.h> //Get this from https://www.electricrcaircraftguy.com/2014/02/Timer2Counter-more-precise-Arduino-micros-function.html

//Pin Selection Macros
  #define PIN_2 (PIND & 0b00000100)
  #define PIN_3 (PIND & 0b00001000)
  #define PIN_4 (PIND & 0b00010000)
  #define PIN_5 (PIND & 0b00100000)
  #define PIN_6 (PIND & 0b01000000)
  #define PIN_7 (PIND & 0b10000000)
  #define PIN_8 (PINB & 0b00000001)
  #define PIN_9 (PINB & 0b00000010)
  #define PIN_10 (PINB & 0b00000100)
  #define PIN_11 (PINB & 0b00001000)
  #define PIN_12 (PINB & 0b00010000)
  #define PIN_13 (PINB & 0b00100000)
  #define PIN_14 (PINC & 0b00000001)
  #define PIN_15 (PINC & 0b00000010)
  #define PIN_16 (PINC & 0b00000100)
  #define PIN_17 (PINC & 0b00001000)
  #define PIN_18 (PINC & 0b00010000)
  #define PIN_19 (PINC & 0b00100000)
  #define PIN_A0 PIN_14
  #define PIN_A1 PIN_15
  #define PIN_A2 PIN_16
  #define PIN_A3 PIN_17
  #define PIN_A4 PIN_18
  #define PIN_A5 PIN_19

void setup() {
  #ifdef PULLUP
    pinMode(GATE_A_PIN2, INPUT_PULLUP);
    pinMode(GATE_B_PIN2, INPUT_PULLUP);
  #endif
  #ifdef LCD
    lcd.setCursor(0, 0);
    lcd.print("Ready!");
  #endif
  timer2.setup();
  Serial.begin(BAUD);   
  Serial.println("Ballistic Chronograph - READY");  //Hello world message
}

void loop(){
  unsigned long millisTimeout;
  unsigned long startGate;
  unsigned long stopGate;

//Wait until GATE A gives a signal
  #ifdef ACTIVE_LOW
    while (GATE_A_PIN) {};
  #else
    while (!GATE_A_PIN) {};
  #endif

//Get the timer count from the eRCaGuy_Timer2_Counter library
  startGate = timer2.get_count();

//Set a timeout timer, if we don't get a GATE B signal by then, just restart the test
  millisTimeout = millis();
  millisTimeout += TIMEOUT;   //Timeout calc

//Wait until GATE B gives a signal OR timeout happens.  If timeout happened, just go back to beginning.
  #ifdef ACTIVE_LOW
    while(GATE_B_PIN && (millis() < millisTimeout)) {};
    if (!GATE_B_PIN){
  #else
    while(!GATE_B_PIN && (millis() < millisTimeout)) {};
    if (GATE_B_PIN){
  #endif

//Timeout did NOT happen.  Print out the speed over Serial.
    stopGate = timer2.get_count();
    double objectSpeed = GATE_SEPARATION;
    objectSpeed *= 2000000;
    objectSpeed /= (stopGate - startGate);
    Serial.print("Time in uS: ");
    Serial.println((stopGate - startGate) / 2);
    Serial.print("  Speed in m/s: ");
    Serial.print(objectSpeed);
    #ifdef LCD
      timer2.revert_to_normal();
      lcd.setCursor(0, 1);
      lcd.print(objectSpeed);
      lcd.print(" m/s");
      timer2.setup();
    #endif
    objectSpeed *= 3.2808;
    Serial.print("  (");
    Serial.print(objectSpeed);
    Serial.println(" fps)");
  }
}

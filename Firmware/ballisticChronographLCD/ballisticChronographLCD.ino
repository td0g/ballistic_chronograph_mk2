/*
  Firmware for Ballistic Chronograph
  Written by Tyler Gerritsen
  tyler@td0g.ca
  www.td0g.ca

DESCRIPTION:
  Basic firmware for an Arduino-based ballistic chronograph with 2 - 6 gates.  Connect the Arduino to a PC and it will automatically read out the speed.  
  This firmware uses Timer1 to measure the time between gate transits.
  This firmware is optimized for high-speed testing and the minimum gate to gate time is 14 microseconds

CHANGELOG:
1.0 2018-01-01
  Functional
  
1.1 2020-04-15
  Added Clock Calibration screen

1.2 2020-05-06
  Fixed clock calibration bug
  Displays gate separation in calibration screen

1.3 2020-06-05
  Switched to timer1 usage

1.4 2021-06-26
  Code not working previously due to couple bugs, major fixes
  New menu structure (Settings sub-menu)
  Fewer hard-coded settings, setup possible through EEPROM settings

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

/*
 Commands:

  g         Run SpeedTest
  d         Set distance to target
  pX tX     Set trigger on pin with tX microseconds preTrig
  pX tX h1  Set trigger on pin with tX microseconds preTrig, compatible with td0g high-speed flash
  rX        Remove trigger
  f         Live Feed
  b         Toggle backlight
  h         Help
  t         Fire flashes
  yXXX      Set test minimum speed in m/s
  zXXX      Set test timeout in seconds
 */




//SETUP ####################################################################################
//Definitions - PLEASE SET UP BEFORE USING

 //Serial port baud rate
#define BAUD 9600  

#define BUTTON_DEBOUNCE 300
#define GATE_SEPARATION_DEFAULT 385 //385
#define TEST_MIN_SPEED 0.1
#define TEST_MAX_SPEED_DEFAULT 3000

//Enter the Arduino pin of the sensor input.  For A0, use 14.  A1, use 15. A2, use 16.  A3, use 17.  A4, use 18.  A5, use 19.  Gates A and B required.  Gates C, D, E, F are optional.
#define GATE_A_PIN 15
#define GATE_B_PIN 16

//Active low means 0V is a gate trigger.  COMMENT OUT for active high (5V = gate is triggered). 
#define ACTIVE_LOW    

//Gate pins are pulled up.  COMMENT OUT to disable pullup resistors.
//#define PULLUP              

//Milliseconds between each gate before test resets. Valid values = 16, 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000
//Note that this will limit the time to output Serial data.  Use BAUD 57600 or higher if MAX_TRANSIT_TIME is less than 64.
#define MAX_TRANSIT_TIME 1000

//END OF SETUP ##############################################################################


//Basic definitions

#define MENU_AB_TEST 0
#define MENU_BA_TEST 1
#define MENU_MAIN 2
#define MENU_ENTER_SETTINGS 3
#define MENU_TRIGGER_ON_OFF 4
#define MENU_TRIGGER_DISTANCE 5
#define MENU_TRIGGER_TIME_OFFSET_0 6
#define MENU_TRIGGER_TIME_OFFSET_1 7
#define MENU_TRIGGER_MAIN 8
#define MENU_SETTINGS_SEPARATION 16
#define MENU_SETTINGS_CALIBRATION 17
#define MENU_SETTINGS_UNITS 18
#define MENU_SETTINGS_MAX_SPEED 19

#define MENU_LAST MENU_TRIGGER_MAIN
#define MENU_LAST_MAIN MENU_TRIGGER_ON_OFF
#define MENU_SETTINGS_FIRST MENU_SETTINGS_SEPARATION
#define MENU_SETTINGS_LAST MENU_SETTINGS_MAX_SPEED

#define EEPROM_ADDRESS_CLOCK 0
#define EEPROM_ADDRESS_BACKLIGHT 2
#define EEPROM_ADDRESS_TRIGGERING 3
#define EEPROM_ADDRESS_UNITS 4
#define EEPROM_ADDRESS_SEPARATION 5
#define EEPROM_ADDRESS_MAX_SPEED 7

#define FPS_CONVERSION 3.28

// include the library code:
  #include <avr/wdt.h>
  #include "defs.h"
  #include <LiquidCrystal.h>
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
  #include <EEPROM.h>

//Pins Setup
  byte pinReadValue;
  byte camPin = 0;
  byte gunPin = 0;
  const byte backlightPin = 10;
  const byte inputButtonPin = 14;
  #define BUTTON_INPUT analogRead(inputButtonPin)

//Chronograph Values
  unsigned int clockRate = 1000;
  unsigned int gateSeparation = GATE_SEPARATION_DEFAULT;
  volatile byte ovfCount;
  unsigned long bulletTransitTime;
  unsigned long testMaxSpeed = TEST_MAX_SPEED_DEFAULT;
  float testMinSpeed = TEST_MIN_SPEED;
  unsigned int maximumSpeed = TEST_MAX_SPEED_DEFAULT;
  
//Trigger Setup
  unsigned long _tTimeOffset[2];
  byte _tPin[2];
  unsigned long distToTarget;
  byte _tOn = 0;
  byte triggeringEnabled = 0;
  boolean distanceTrigger = false;
  boolean timeTrigger = false;
  unsigned long triggerDelay;
  unsigned long triggerTime;
  unsigned long triggerComp;
  byte safety = 1;

//Serial Commander
  char serialBuffer[64];
  int sofar;
  byte left;

//LCD Menu
  byte menuPosition = 2;
  byte backlightOn = 1;
  int backlightPwr = 127;
  byte units = 0;



void setup() {
//Begin Serial
  Serial.begin(BAUD);      

//Begin LCD
  lcd.begin(16, 2);
  pinMode(inputButtonPin, INPUT);
  pinMode(backlightPin, OUTPUT);
  backlightPwr = EEPROM.read(EEPROM_ADDRESS_BACKLIGHT);
  analogWrite(backlightPin, backlightPwr);
  units = EEPROM.read(EEPROM_ADDRESS_UNITS);
  const byte microsSymbol[8] = {
    0b00000,
    0b00000,
    0b10001,
    0b10001,
    0b11011,
    0b01101,
    0b00001,
  };
  lcd.createChar(1, microsSymbol);

//Setup chronograph pins
  #ifdef PULLUP
    pinMode(GATE_A_PIN, INPUT_PULLUP);
    pinMode(GATE_B_PIN, INPUT_PULLUP);
  #endif

//Recall triggering state
  if (EEPROM.read(EEPROM_ADDRESS_TRIGGERING) == 1) enableTriggering(); 

//Start communicating with PC
  Serial.println(F("\n\nBallistic Chronograph - READY"));  //Hello world message
  Serial.print(F("Max transit time per gate: "));
  Serial.print(MAX_TRANSIT_TIME);
  Serial.println(F(" ms"));

//Print info to display
  refreshDisplay();
  for (byte i = 0; i < 2; i++){
    _tPin[i] = 255;
  }

//Load clock calibration factor
  clockRate = EEPROMReadint(EEPROM_ADDRESS_CLOCK);
  if (clockRate < 500 || clockRate > 2000) {
    clockRate = 1000;
    EEPROMWriteint(EEPROM_ADDRESS_CLOCK, clockRate);
  }
  gateSeparation = EEPROMReadint(EEPROM_ADDRESS_SEPARATION);
  if (!gateSeparation || gateSeparation == 65535){
    gateSeparation = GATE_SEPARATION_DEFAULT;
    EEPROMWriteint(EEPROM_ADDRESS_SEPARATION, gateSeparation);
  }
  maximumSpeed = EEPROMReadint(EEPROM_ADDRESS_MAX_SPEED);
  if (!maximumSpeed || maximumSpeed == 65535){
    maximumSpeed = TEST_MAX_SPEED_DEFAULT;
    EEPROMWriteint(EEPROM_ADDRESS_MAX_SPEED, maximumSpeed);
  }
}

void loop(){
  getButton();
  runDisplay();
  getCommand();
}


ISR(TIMER1_OVF_vect) {ovfCount++;}

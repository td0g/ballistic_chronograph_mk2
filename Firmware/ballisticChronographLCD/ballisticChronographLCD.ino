/*
  Firmware for Ballistic Chronograph
  Written by Tyler Gerritsen
  tyler@td0g.ca
  www.td0g.ca

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

CHANGELOG
1.0 2018-01-01
  Functional
  
1.1 2020-04-15
  Added Clock Calibration screen

1.2 2020-05-06
  Fixed clock calibration bug
  Displays gate separation in calibration screen
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

//Definitions
#define DEBUG
#define BAUD 2400
#define BUTTON_DEBOUNCE 300
#define MAX_BUF 64 // What is the longest message Arduino can store?
#define MAX_TRIGGERS 4
#define GATE_SEPARATION 385 //385
#define HIGH_SPEED_FLASH_PULSE 1000 //us
#define HIGH_SPEED_FLASH_DELAY 5    //s

 // include the library code:
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#include <eRCaGuy_Timer2_Counter.h>

#include <EEPROM.h>

#define gatePort PINC
const byte gateA = 16;
const byte gateB = 15;  

unsigned long bulletTransitTime;
unsigned long _bTimeout = 600000;  //Default 10 minutes
unsigned long bulletDepartureTime;
unsigned long _bMinTime;

unsigned long _tTimeOffset[MAX_TRIGGERS];
byte _tPin[MAX_TRIGGERS];
unsigned long distToTarget;
byte _tOn = 0;
unsigned long _bTrigTime;

unsigned int clockRate = 1000;

char serialBuffer[MAX_BUF];
int sofar;
byte left;

const byte backlightPin = 10;
const byte inputButtonPin = 14;
#define BUTTON_INPUT analogRead(inputButtonPin)

//Pins Setup
  byte pinReadValue;
  byte camPin = 0;
  byte gunPin = 0;

//Chronograph Values
  unsigned long startGate;
  unsigned long startGateB;
  unsigned long stopGate;
  unsigned long stopGateB;

//Trigger Setup
  boolean distanceTrigger = false;
  boolean timeTrigger = false;
  unsigned long triggerDelay;
  unsigned long triggerTime;
  unsigned long triggerComp;

//Serial Commander
  String COMstring;
  unsigned long COMvalue;
  const char terminator = '/';

//Other
  const String indent = "   ";
  const String dindent = "    ";

//LCD Menu
  char menuPosition = 2;
  const byte menuPositionSize = 7;
  byte backlightOn = 1;
  int backlightPwr = 255;

  byte safety = 1;


void setup() {
  Serial.begin(BAUD);      
  lcd.begin(16, 2);
  pinMode(inputButtonPin, INPUT);
  pinMode(backlightPin, OUTPUT);
  digitalWrite(backlightPin, 1);
  pinMode(gunPin, OUTPUT);
  pinMode(camPin, OUTPUT);
  digitalWrite(gunPin, 0);

  pinMode(gateA, INPUT_PULLUP);        //Setup input and output pins
  pinMode(gateB, INPUT_PULLUP);

  Serial.println("Ballistic Chronograph - READY");  //Hello world message
  Serial.println("Type 'h' for more information");
  Serial.println();
  refreshDisplay();
  for (byte i = 0; i < MAX_TRIGGERS; i++){
    _tPin[i] = 255;
  }
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  timer2.setup();
  clockRate = 900 + EEPROM.read(0);
  if (clockRate == 900 || clockRate == 900 + 255) clockRate = 1000;
}

void loop(){
  getButton();
  runDisplay();
  getCommand();
}

/*
  Firmware for Ballistic Chronograph
  Written by Tyler Gerritsen
  vtgerritsen@gmail.com
  www.td0g.ca

DESCRIPTION:
  Very basic firmware for an Arduino-based ballistic chronograph.  Connect the Arduino to a PC and it will automatically read out the speed.  
  Can also display the speed on an LCD display using the LiquidCrystal library.

CHANGELOG:
  1.0
    2020-04-23
    Initial Release
  1.1
    2020-06-16
    Switched from eRCaGuy library to directly accessing Timer1
    Using watchdog timer to catch timeouts - better performance

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

//Distance in mm
#define GATE_SEPARATION 500

//Arduino pin for the gates sensors.  Use 14 for A0, 15 for A1, 16 for A2, 17 for A3, 18 for A4, 19 for A5
#define GATE_A_PIN  15      
#define GATE_B_PIN  14

//Active low means 0V is a gate trigger.  COMMENT OUT for active high (5V = gate is triggered).
#define ACTIVE_LOW

//Pullup resistors inside the Arduino can be turned on.  COMMENT OUT to disable pullup resistors.
//#define PULLUP

//LCD Display - PLEASE SET UP BEFORE USING
//#define LCD_PINS 8, 9, 4, 5, 6, 7   ////Comment out to disable the LCD output.  Set the pin numbers for the LCD: RS, EN, D4, D5, D6, D7

//Milliseconds between each gate before test resets. Valid values = 16, 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000
//Note that this will limit the time to output Serial data.  Use BAUD 57600 or higher if MAX_TRANSIT_TIME is less than 64.
#define MAX_TRANSIT_TIME 1000

//END OF SETUP ##############################################################################







//include the LiquidCrystal library:
  #ifdef LCD_PINS
    #include <LiquidCrystal.h>
    LiquidCrystal lcd(LCD_PINS);
  #endif
  
//Interrupt things
  #include <avr/wdt.h>
  volatile byte ovfCount;  //This is the timer overflow count
  

//Pin Selection Definitions
  #if (GATE_A_PIN == 2)
    #define GATE_A_PIN2 (PIND & 0b00000100)
  #elif (GATE_A_PIN == 3)
    #define GATE_A_PIN2 (PIND & 0b00001000)
  #elif (GATE_A_PIN == 4)
    #define GATE_A_PIN2 (PIND & 0b00010000)
  #elif (GATE_A_PIN == 5)
    #define GATE_A_PIN2 (PIND & 0b00100000)
  #elif (GATE_A_PIN == 6)
    #define GATE_A_PIN2 (PIND & 0b01000000)
  #elif (GATE_A_PIN == 7)
    #define GATE_A_PIN2 (PIND & 0b10000000)
  #elif (GATE_A_PIN == 8)
    #define GATE_A_PIN2 (PINB & 0b00000001)
  #elif (GATE_A_PIN == 9)
    #define GATE_A_PIN2 (PINB & 0b00000010)
  #elif (GATE_A_PIN == 10)
    #define GATE_A_PIN2 (PINB & 0b00000100)
  #elif (GATE_A_PIN == 11)
    #define GATE_A_PIN2 (PINB & 0b00001000)
  #elif (GATE_A_PIN == 12)
    #define GATE_A_PIN2 (PINB & 0b00010000)
  #elif (GATE_A_PIN == 13)
    #define GATE_A_PIN2 (PINB & 0b00100000)
  #elif (GATE_A_PIN == 14)
    #define GATE_A_PIN2 (PINC & 0b00000001)
  #elif (GATE_A_PIN == 15)
    #define GATE_A_PIN2 (PINC & 0b00000010)
  #elif (GATE_A_PIN == 16)
    #define GATE_A_PIN2 (PINC & 0b00000100)
  #elif (GATE_A_PIN == 17)
    #define GATE_A_PIN2 (PINC & 0b00001000)
  #elif (GATE_A_PIN == 18)
    #define GATE_A_PIN2 (PINC & 0b00010000)
  #elif (GATE_A_PIN == 19)
    #define GATE_A_PIN2 (PINC & 0b00100000)
  #else
    #error "You must set Gate A to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
  #endif

  #ifdef ACTIVE_LOW
    #define GATE_A GATE_A_PIN2
  #else
    #define GATE_A !GATE_A_PIN2
  #endif

   #if (GATE_B_PIN == 2)
    #define GATE_B_PIN2 (PIND & 0b00000100)
  #elif (GATE_B_PIN == 3)
    #define GATE_B_PIN2 (PIND & 0b00001000)
  #elif (GATE_B_PIN == 4)
    #define GATE_B_PIN2 (PIND & 0b00010000)
  #elif (GATE_B_PIN == 5)
    #define GATE_B_PIN2 (PIND & 0b00100000)
  #elif (GATE_B_PIN == 6)
    #define GATE_B_PIN2 (PIND & 0b01000000)
  #elif (GATE_B_PIN == 7)
    #define GATE_B_PIN2 (PIND & 0b10000000)
  #elif (GATE_B_PIN == 8)
    #define GATE_B_PIN2 (PINB & 0b00000001)
  #elif (GATE_B_PIN == 9)
    #define GATE_B_PIN2 (PINB & 0b00000010)
  #elif (GATE_B_PIN == 10)
    #define GATE_B_PIN2 (PINB & 0b00000100)
  #elif (GATE_B_PIN == 11)
    #define GATE_B_PIN2 (PINB & 0b00001000)
  #elif (GATE_B_PIN == 12)
    #define GATE_B_PIN2 (PINB & 0b00010000)
  #elif (GATE_B_PIN == 13)
    #define GATE_B_PIN2 (PINB & 0b00100000)
  #elif (GATE_B_PIN == 14)
    #define GATE_B_PIN2 (PINC & 0b00000001)
  #elif (GATE_B_PIN == 15)
    #define GATE_B_PIN2 (PINC & 0b00000010)
  #elif (GATE_B_PIN == 16)
    #define GATE_B_PIN2 (PINC & 0b00000100)
  #elif (GATE_B_PIN == 17)
    #define GATE_B_PIN2 (PINC & 0b00001000)
  #elif (GATE_B_PIN == 18)
    #define GATE_B_PIN2 (PINC & 0b00010000)
  #elif (GATE_B_PIN == 19)
    #define GATE_B_PIN2 (PINC & 0b00100000)
  #else
    #error "You must set Gate B to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
  #endif

  #ifdef ACTIVE_LOW
    #define GATE_B GATE_B_PIN2
  #else
    #define GATE_B !GATE_B_PIN2
  #endif

  #if (MAX_TRANSIT_TIME == 16)
    #define WDT_ON 0b00001000;
  #elif (MAX_TRANSIT_TIME == 32)
    #define WDT_ON 0b00001001;
  #elif (MAX_TRANSIT_TIME == 64)
    #define WDT_ON 0b00001010;
  #elif (MAX_TRANSIT_TIME == 125)
    #define WDT_ON 0b00001011;
  #elif (MAX_TRANSIT_TIME == 250)
    #define WDT_ON 0b00001100;
  #elif (MAX_TRANSIT_TIME == 500)
    #define WDT_ON 0b00001101;
  #elif (MAX_TRANSIT_TIME == 1000)
    #define WDT_ON 0b00001110;
  #elif (MAX_TRANSIT_TIME == 2000)
    #define WDT_ON 0b00001111;
  #elif (MAX_TRANSIT_TIME == 4000)
    #define WDT_ON 0b00101000;
  #elif (MAX_TRANSIT_TIME == 8000)
    #define WDT_ON 0b00101001;
  #else
    #error "you need to set MAX_TRANSIT_TIME correctly"
  #endif










void setup() {
//Setup pin states
  #ifdef PULLUP
    pinMode(GATE_A_PIN, INPUT_PULLUP);
    pinMode(GATE_B_PIN, INPUT_PULLUP);
  #endif

//Setup LCD
  #ifdef LCD_PINS
    lcd.setCursor(0, 0);
    lcd.print("Ready!");
  #endif

//Setup timer1
  TCCR1A = 0;                                   //No pin changes needed
  TCCR1B = (TCCR1B & 0b11100000) | 0b00000010;  // div8 = 1/2us per increment, 16-bit normal mode
  TIMSK1 |= 1;                                  //Turn on overflow interrupt

//Start communicating with PC
  Serial.begin(BAUD);   
  Serial.println("\n\nBallistic Chronograph - READY");  //Hello world message
  Serial.print(F("Max transit time per gate: "));
  Serial.print(MAX_TRANSIT_TIME);
  Serial.println(F(" ms"));
  delay(100);
}








void loop(){
//Prepare variables  
  unsigned long testTime; //This is the timer count
  unsigned long testOvf;
  
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

//Wait until GATE B gives a signal OR timeout happens.
  while(GATE_B) {};
  testTime = TCNT1;
  testOvf = ovfCount;

//Turn off the watchdog timer
  cli();
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 0;
  sei();
  
//Enable interrupts so that Serial functions work
  enableInterrupts();

//The testTime counts up to 65535.  Then it will overflow, and the testOvf will increment by one.
//We need to multiply the testOvf by 65536 and add it to the testTime.  This is the total Timer1 count.
//Note that we have Timer1 set to 2x counts per microsecond.
  testOvf = testOvf << 16;
  testTime += testOvf;

//Now we have the Timer1 count.  Calculate the object speed.
  float objectSpeed = GATE_SEPARATION;
  objectSpeed *= 2000000;
  objectSpeed /= testTime;

//Print the speed over Serial
  Serial.print("Time in uS: ");
  Serial.println(testTime / 2);
  Serial.print("  Speed in m/s: ");
  Serial.print(objectSpeed);
  
//Display the speed on the LCD
  #ifdef LCD_PINS
    lcd.setCursor(0, 1);
    lcd.print(objectSpeed);
    lcd.print(" m/s");
  #endif
  
//Print the speed in fps over Serial for the crazy people
  objectSpeed *= 3.2808;
  Serial.print("  (");
  Serial.print(objectSpeed);
  Serial.println(" fps)");


}


ISR(TIMER1_OVF_vect) {ovfCount++;}  //Keep count of how many times Timer1 overflows


void disableInterrupts(){editInterrupts(0);}  //Turn of Timer0 and Timer2


void enableInterrupts(){ editInterrupts(1);}  //Turn on Timer0 and Timer2


void editInterrupts(byte _s){
//We need to remember the states of the Timer0 and Timer2 registers before turning them off
  static byte _tccr0b;
  static byte _tccr2b;
  static byte _intState = 1;
  if (_s != _intState){
    if (!_s){
//Turning timer prescalers OFF
      _intState = 0;
      _tccr0b = TCCR0B;
      _tccr2b = TCCR2B;
      TCCR0B |= 0b11111000;
      TCCR2B |= 0b11111000;
    }
    else {
//Resetting timer prescalers to previous state
      _intState = 1;
      TCCR0B = _tccr0b;
      TCCR2B = _tccr2b;
    }
  }
}

/*
  Firmware for measuring Arduino clock speed
  Written by Tyler Gerritsen
  vtgerritsen@gmail.com
  www.td0g.ca

DESCRIPTION:
  Simple way to measure the actual speed of an Arduino Uno
  A stopwatch is required.  Start the stopwatch simultaneously with the Arduino by sending a serial character.
  Adjust the Arduino's clock speed by entering 't99.8' to slow the clock by 0.2%
  After a couple minutes, the clock can be calibrated very accurately!

CHANGELOG:
  1.0
    2020-07-26
    Initial Release

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

//END OF SETUP ##############################################################################


//Serial
  char serialBuffer[20];
  int sofar = 0;
  float _timeFactor = 1.0;
  unsigned long _time = 1000;
  unsigned long _adjustedTime = 1000;




void setup() {
//Start communicating with PC
  Serial.begin(BAUD);   
  Serial.println(F("Prepare a stopwatch"));  //Hello world message
  Serial.println(F("When you are ready, send a character over Serial"));
  Serial.println(F("Then the Arduino will count down until it begins its count"));
  Serial.println(F("Start the stopwatch when the count down reaches 0"));
  Serial.println(F("After some time, you may adjust the clock rate by entering a %"));
  Serial.println(F("For instance: enter 99.8 to slow down the clock by 0.2%"));
  delay(100);
  while (!Serial.available()){};
}


void loop(){
//Print clock
  if (millis() > _adjustedTime){
    Serial.print(_time / 1000);
    Serial.print(F(".0 s"));
    _time += 1000;
    _adjustedTime = _time / _timeFactor;
  }
//Read serial
  if (Serial.available()){
    char _c = Serial.read();
    if (_c == 10 || _c == 13){  //Newline character

    //Read new timefactor
      serialBuffer[sofar] = 0;
      _timeFactor = parseNumber('t',_timeFactor);
      Serial.print(F("New Time Factor: "));
      Serial.println(_timeFactor);
      Serial.print(F("Clock Speed: "));
      Serial.print(_timeFactor * 16);
      Serial.println(F(" MHz"));

    //Adjust clock
      _adjustedTime = _time / _timeFactor;
      while (_adjustedTime > millis()){
        _time -= 1000;
        _adjustedTime = _time / _timeFactor;
      }
      while (_adjustedTime < millis()){
        _time += 1000;
        _adjustedTime = _time / _timeFactor;
      }
      sofar = 0;
    }

  //Read serial into buffer
    else {
      serialBuffer[sofar] = Serial.read();
      sofar++;
    }
  }
}



float parseNumber(char code,float val) {
  char *ptr=serialBuffer;  // start at the beginning of buffer
  while((long)ptr > 1 && (*ptr) && (long)ptr < (long)serialBuffer+sofar) {  // walk to the end
    if(*ptr==code) {  // if you find code on your walk,
      return atof(ptr+1);  // convert the digits that follow into a float and return it
    }
    ptr++;  // take a step from here to the letter after the next space
  }
  return val;  // end reached, nothing found, return default val.
}

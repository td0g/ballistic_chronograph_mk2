#define PRESSED_UP 2
#define PRESSED_RIGHT 1
#define PRESSED_LEFT 3
#define PRESSED_DOWN 4
#define PRESSED_SELECT 5
byte button(){
  static unsigned long nextRead = 0;
  static int buttonInput;
  if (millis() < nextRead) return 0;
  buttonInput = analogRead(inputButtonPin);
  if (buttonInput > 1000) return 0;
  nextRead = millis() + BUTTON_DEBOUNCE;
  if (buttonInput < 100) return PRESSED_RIGHT;
  if (buttonInput < 200) return PRESSED_UP;
  if (buttonInput < 400) return PRESSED_DOWN;
  if (buttonInput < 600) return PRESSED_LEFT;
  return PRESSED_SELECT;
}


void getButton(){
  /*
   analogRead values (A0):
      nothing = 1023
      Select = 720
      Left = 477
      Down = 305
      Up = 131
      Right = 0
  
      D10 controls backlight
      
   */
  
   byte _btn = button();
   if (_btn){
     if (_btn == PRESSED_UP){ //Up
       if (!menuPosition) menuPosition = menuPositionSize;
       menuPosition--;
     }
     else if (_btn == PRESSED_DOWN){ //Down
       menuPosition++;
       menuPosition %= menuPositionSize;
     }
     else {
      switch (menuPosition){
        case 0: case 1:
          if (_btn == PRESSED_RIGHT){
            digitalWrite(backlightPin, 0);
            doTest(menuPosition);
            float _s = testSpeed();
            _s = _s * clockRate / 1000;
            timer2.revert_to_normal();
            digitalWrite(backlightPin, backlightOn);
            timer2.setup();
          }
          else if (_btn == PRESSED_LEFT) toggleBacklight();
          else if (_btn == PRESSED_SELECT){
            timer2.revert_to_normal();
            lcd.setCursor(0, 1);
            if (!menuPosition) lcd.print(testAB() * clockRate / 1000);
            else lcd.print(testBA() * clockRate / 1000);
            timer2.setup();
          }
        break;
        case 2:
          if (_btn == PRESSED_LEFT) toggleBacklight();
          else if (_btn == PRESSED_RIGHT) metronome();
        break;
        case 3:
          if (_btn == PRESSED_RIGHT)distToTarget += 50;
          else if (_btn == PRESSED_LEFT) distToTarget -= min(distToTarget, 10);
        break;
        case 4:
          if (_btn == PRESSED_RIGHT) _tTimeOffset[0] += 20;
          else if (_btn == PRESSED_LEFT) _tTimeOffset[0] -= min(5, _tTimeOffset[1]);
        break;
        case 5:
          if (_btn == PRESSED_RIGHT) _tTimeOffset[1] += 20;
          else if (_btn == PRESSED_LEFT)_tTimeOffset[1] -= min(5, _tTimeOffset[1]);
        break;
        case 6:
          if (_btn == PRESSED_SELECT) practiceRoutine();
          else if (_btn == PRESSED_RIGHT) {
            if (!gunPin) gunPin = 3;
            else gunPin = 0;
          }
          else if (_btn == PRESSED_LEFT) toggleBacklight();
        break;
      }
    }
    refreshDisplay();
  }
  
}

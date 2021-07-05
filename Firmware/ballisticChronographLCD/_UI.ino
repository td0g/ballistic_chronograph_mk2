#define PRESSED_UP 2
#define PRESSED_RIGHT 1
#define PRESSED_LEFT 3
#define PRESSED_DOWN 4
#define PRESSED_SELECT 5
byte button(byte _resetMillis){
  static unsigned int _lowPass;
  static unsigned long nextRead = 0;
  static byte _debounceFlag;
  static unsigned long _resetTimer = 0;
  int analogInput = analogRead(inputButtonPin);
  if (!_resetTimer && _resetMillis){
    _resetTimer = millis() + _resetMillis;
  }
  else if (millis() > _resetTimer && _resetTimer){
    _debounceFlag = 1;
    nextRead = millis() - 1;
    _resetTimer = 0;
  }
  _lowPass = _lowPass * 3 / 4 + analogInput;
  if (millis() < nextRead) return 0;
  byte _buttonInput = _lowPass >> 6;
  if (_buttonInput > 60) {
    _debounceFlag = 1;
    return 0;
  }
  if (abs((analogInput >> 4) - _buttonInput) > 1 || !_debounceFlag) return 0;
  _debounceFlag = 0;
  nextRead = millis() + BUTTON_DEBOUNCE;
  /*
   analogRead values (A0):
      nothing = 63
      Select = 45
      Left = 29
      Down = 19
      Up = 8
      Right = 0
  
      D10 controls backlight
   */
  if (_buttonInput < 6) return PRESSED_RIGHT;
  if (_buttonInput < 15) return PRESSED_UP;
  if (_buttonInput < 25) return PRESSED_DOWN;
  if (_buttonInput < 39) return PRESSED_LEFT;
  return PRESSED_SELECT;
}


void getButton(){
   byte _btn = button(0);
   if (_btn){
     if (_btn == PRESSED_DOWN){ //Down
       if (menuPosition == MENU_SETTINGS_FIRST) menuPosition = MENU_SETTINGS_LAST;
       else if (!menuPosition) {
        if (!triggeringEnabled) menuPosition = MENU_LAST_MAIN;
        else menuPosition = MENU_LAST;
       }
       else menuPosition--;
     }
     else if (_btn == PRESSED_UP){ //Up
       menuPosition++;
       if (menuPosition < MENU_SETTINGS_FIRST){
        if (!triggeringEnabled) menuPosition %= (MENU_LAST_MAIN + 1);
        menuPosition %= (MENU_LAST + 1);
       }
       else if (menuPosition > MENU_SETTINGS_LAST) {
        menuPosition = MENU_ENTER_SETTINGS;
        EEPROMWriteint(EEPROM_ADDRESS_MAX_SPEED, maximumSpeed);
        EEPROMWriteint(EEPROM_ADDRESS_SEPARATION, gateSeparation);
       }
     }
     else {
      switch (menuPosition){
        case MENU_AB_TEST: case MENU_BA_TEST:
          if (_btn == PRESSED_SELECT || _btn == PRESSED_RIGHT){
            digitalWrite(backlightPin, 0);
            measureHalfMicros(menuPosition);
            refreshDisplay();
            float _s = lastTestSpeed();
            _s = _s * 1000 / clockRate;
            analogWrite(backlightPin, backlightPwr);
          }
          else if (_btn == PRESSED_LEFT) toggleBacklight();
        break;
        case MENU_MAIN:
          if (_btn == PRESSED_LEFT) toggleBacklight();
        break;
        case MENU_ENTER_SETTINGS:
          if (_btn == PRESSED_RIGHT || _btn == PRESSED_SELECT) {
            menuPosition = MENU_SETTINGS_FIRST;
          }
          else if (_btn == PRESSED_LEFT) toggleBacklight();
        break;
        case MENU_TRIGGER_ON_OFF:
          if (_btn == PRESSED_RIGHT || _btn == PRESSED_SELECT) {
            if (triggeringEnabled) disableTriggering();
            else enableTriggering();
          }
          else if (_btn == PRESSED_LEFT) toggleBacklight();
        break;
        case MENU_TRIGGER_DISTANCE:
          if (_btn == PRESSED_RIGHT)distToTarget += 50;
          else if (_btn == PRESSED_LEFT) distToTarget -= min(distToTarget, 10);
        break;
        case MENU_TRIGGER_TIME_OFFSET_0:
          if (_btn == PRESSED_RIGHT) _tTimeOffset[0] += 20;
          else if (_btn == PRESSED_LEFT) _tTimeOffset[0] -= min(5, _tTimeOffset[1]);
        break;
        case MENU_TRIGGER_TIME_OFFSET_1:
          if (_btn == PRESSED_RIGHT) _tTimeOffset[1] += 20;
          else if (_btn == PRESSED_LEFT)_tTimeOffset[1] -= min(5, _tTimeOffset[1]);
        break;
        case MENU_TRIGGER_MAIN:
          if (_btn == PRESSED_SELECT) practiceRoutine();
          else if (_btn == PRESSED_RIGHT) {
            if (!gunPin) gunPin = 3;
            else gunPin = 0;
          }
          else if (_btn == PRESSED_LEFT) toggleBacklight();
        break;
        case MENU_SETTINGS_SEPARATION:
          if (_btn == PRESSED_RIGHT) gateSeparation++;
          else if (_btn == PRESSED_LEFT && gateSeparation) gateSeparation--;
          refreshDisplay();
            button(180);
        break;
        case MENU_SETTINGS_UNITS:
          if (_btn == PRESSED_RIGHT){
            units = (1 - units) & 1;
            EEPROM.write(EEPROM_ADDRESS_UNITS, units);
            refreshDisplay();
          }
        break;
        case MENU_SETTINGS_CALIBRATION:
          if (_btn == PRESSED_RIGHT && clockRate < 2000) clockRate++;
          else if (_btn == PRESSED_LEFT && clockRate > 500) clockRate--;
          else if (_btn == PRESSED_SELECT) metronome();
          if (_btn) refreshDisplay();
        break;
        case MENU_SETTINGS_MAX_SPEED:
          if (_btn == PRESSED_RIGHT){
            if (maximumSpeed > 999 && maximumSpeed < 10000) maximumSpeed += 100;
            else if (maximumSpeed > 99) maximumSpeed += 10;
            else maximumSpeed++;
            button(180);
            refreshDisplay();
          }
          else if (_btn == PRESSED_LEFT){
            unsigned long minMaximumSpeed =  gateSeparation / 30; // separation in mm divided by just less than one overflow period (30 milliseconds)
            if (maximumSpeed > 1000) maximumSpeed -= 100;
            else if (maximumSpeed > 100 && maximumSpeed > (minMaximumSpeed + 9)) maximumSpeed -= 10;
            else if (maximumSpeed > minMaximumSpeed) maximumSpeed--;
            button(180);
            refreshDisplay();
          }
        break;
      }
    }
    refreshDisplay();
  }
}

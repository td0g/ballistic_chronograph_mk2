


void runDisplay(){
  static unsigned int _a;
  static unsigned int _b;
  static unsigned int _t;
  static unsigned long lastLow;
  
  if (menuPosition == MENU_MAIN){
    if (GATE_A) _a++;
    if (GATE_B) _b++;
    if (!GATE_A || !GATE_B){
      if (lastLow < millis())digitalWrite(backlightPin, 0);
      else analogWrite(backlightPin, backlightPwr);
      lastLow = millis() + 750;
    }
    else analogWrite(backlightPin, backlightPwr);
    _t++;

    if (_t == 3000){
      if (_a < _t) _a = min(_a / 30, 99);
      else _a /= 30;
      if (_b < _t) _b = min(_b / 30, 99);
      else _b /= 30;
      //timer2.revert_to_normal();
      lcd.setCursor(3, 1);
      lcd.print(_a);
      if (_a < 100) lcd.print(" ");
      if (_a < 10) lcd.print(" ");
      lcd.setCursor(13, 1);
      lcd.print(_b);
      if (_b < 100) lcd.print(" ");
      if (_b < 10) lcd.print(" ");
      _a = 0;
      _b = 0;
      _t = 0;
    }
  }
}


void refreshDisplay(){
  static byte _menuPosition;
  if (_menuPosition != menuPosition){
    menuPosition &= 0b01111111;
    switch (menuPosition){
      case MENU_AB_TEST: case MENU_BA_TEST:
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print(F("A -"));
        lcd.write(126);
        lcd.print(F(" B Test"));
        lcd.setCursor(1, 1);
        lcd.print(F("A "));
        lcd.write(127);
        lcd.print(F("- B Test"));
        if (menuPosition == MENU_AB_TEST) lcd.setCursor(0, 1); 
        else lcd.setCursor(0, 0);
        lcd.write(126);
      break;
      case MENU_MAIN:
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print(F("Status"));
        lcd.setCursor(0, 1);
        lcd.print(F("A:"));
        lcd.setCursor(10, 1);
        lcd.print(F("B: "));
      break;
      case MENU_ENTER_SETTINGS: case MENU_TRIGGER_ON_OFF:
        lcd.clear();
        lcd.setCursor(1, 1);
        lcd.print(F("Settings"));
        lcd.setCursor(1, 0);
        lcd.print(F("Triggering "));
        if (menuPosition == MENU_ENTER_SETTINGS) lcd.setCursor(0, 1);
        else lcd.setCursor(0, 0);
        lcd.write(126);
      break;
      case MENU_TRIGGER_DISTANCE:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Distance To Trigger"));
        lcd.setCursor(0, 1);
        lcd.print(distToTarget);
        lcd.print(F(" mm"));
      break;
      case MENU_TRIGGER_TIME_OFFSET_0:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Pre-FlashDelay0"));
        lcd.setCursor(0, 1);
        lcd.print(_tTimeOffset[0]);
        lcd.print(F(" "));
        lcd.write(1);
        lcd.print(F("s"));
      break;
      case MENU_TRIGGER_TIME_OFFSET_1:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Pre-FlashDelay1"));
        lcd.setCursor(0, 1);
        lcd.print(_tTimeOffset[1]);
        lcd.print(F(" "));
        lcd.write(1);
        lcd.print(F("s"));
      break;
      case MENU_TRIGGER_MAIN:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("2 "));  
        if (gunPin) lcd.print(gunPin);
        else lcd.print(F(" "));
        lcd.print(F(" 11  12  13"));
        lcd.setCursor(0, 1);
        lcd.print(F("- G  C   F   F"));
      break;
      case MENU_SETTINGS_SEPARATION:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Gate Separation:"));
        lcd.setCursor(0, 1);
        lcd.write(126);
      break;
      case MENU_SETTINGS_UNITS: case MENU_SETTINGS_CALIBRATION:
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print(F("Units: "));
        lcd.setCursor(1, 1);
        lcd.print(F("Clock Cal:"));
        if (menuPosition == MENU_SETTINGS_UNITS) lcd.setCursor(0, 0);
        else lcd.setCursor(0, 1);  
        lcd.write(126);
      break;
      case MENU_SETTINGS_MAX_SPEED:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Max Speed:"));
        lcd.setCursor(0, 1);
        lcd.write(126);
      break;
    } 
    _menuPosition = menuPosition;
  }
  //timer2.revert_to_normal();
  switch (menuPosition){
    case MENU_AB_TEST:
      if (lastTestSpeed() > 0 && lastTestSpeed() < 99999){
        lcd.setCursor(0, 0);
        lcd.print(lastTestSpeed());
        if (units) lcd.print(F(" FPS    "));
        else lcd.print(F(" m/s    "));
      }
    break;
    case MENU_BA_TEST:
      if (lastTestSpeed() > 0 && lastTestSpeed() < 99999){
        lcd.setCursor(0, 1);
        lcd.print(lastTestSpeed());
        if (units) lcd.print(F(" FPS    "));
        else lcd.print(F(" m/s    "));
      }
    break;
    case MENU_ENTER_SETTINGS: case MENU_TRIGGER_ON_OFF:
      lcd.setCursor(12, 0);
      if (triggeringEnabled){
        lcd.print(F("ON "));
      }
      else {
        lcd.print(F("OFF"));
      }
    break;
    case MENU_TRIGGER_DISTANCE:
      lcd.setCursor(0, 1);
      lcd.print(distToTarget);
      lcd.print(F(" mm"));
    break;
    case MENU_TRIGGER_TIME_OFFSET_0:
      lcd.setCursor(0, 1);
      lcd.print(_tTimeOffset[0]);
      lcd.print(F(" "));
      lcd.write(1);
      lcd.print(F("s"));
    break;
    case MENU_TRIGGER_TIME_OFFSET_1:
      lcd.setCursor(0, 1);
      lcd.print(_tTimeOffset[1]);
      lcd.print(F(" "));
      lcd.write(1);
      lcd.print(F("s"));
    break;
    case MENU_TRIGGER_MAIN:
      lcd.setCursor(2, 0);
      if (gunPin) lcd.print(gunPin);
      else lcd.print(F(" "));
      lcd.print(F(" 11  12  13"));
    break;
    case MENU_SETTINGS_SEPARATION:
      lcd.setCursor(1, 1);
      lcd.print(gateSeparation);
      lcd.print(F(" mm "));  
    break;
    case MENU_SETTINGS_MAX_SPEED:
      lcd.setCursor(1, 1);
      if (units) {
        lcd.print(uint16_t(maximumSpeed * FPS_CONVERSION));
        lcd.print(F(" FPS "));
      }
      else {
        lcd.print(maximumSpeed);
        lcd.print(F(" m/s "));
      }
    break;
    case MENU_SETTINGS_UNITS: case MENU_SETTINGS_CALIBRATION:
      lcd.setCursor(8, 0);
      if (units) lcd.print(F("FPS"));
      else lcd.print(F("m/s"));
      lcd.setCursor(11, 1);
      float _c = clockRate;
      _c /= 1000;
      lcd.print(_c, 3);
    break;
  }
}

void toggleBacklight(){
  if (!backlightPwr) backlightPwr = 255;
  else if (backlightPwr == 255) backlightPwr = 63;
  else backlightPwr = 0;
  analogWrite(backlightPin, backlightPwr);
  EEPROM.write(EEPROM_ADDRESS_BACKLIGHT, backlightPwr);
}

void metronome(){
  unsigned long _timer = millis();
  byte _exit = 2;
  while (_exit){
    digitalWrite(backlightPin, 0);
    while (_timer + clockRate - 800 > millis() && _exit){
      byte _btn = button(0);
      if (!_btn)_exit = 1;
      else if (_btn == PRESSED_LEFT) {
        clockRate--;
        refreshDisplay();
      }
      else if (_btn == PRESSED_RIGHT) {
        clockRate++;
        refreshDisplay();
      }
      else if (_btn == PRESSED_UP){
        clockRate += 10;
        refreshDisplay();
      }
      else if (_btn == PRESSED_DOWN){
        clockRate -= 10;
        refreshDisplay();
      }
      else if (_exit == 1) _exit = 0;
    }
    analogWrite(backlightPin, backlightPwr);
    while (_timer + clockRate > millis() && _exit){
      byte _btn = button(0);
      if (!_btn)_exit = 1;
      else if (_btn == PRESSED_LEFT) {
        clockRate--;
        refreshDisplay();
      }
      else if (_btn == PRESSED_RIGHT) {
        clockRate++;
        refreshDisplay();
      }
      else if (_btn == PRESSED_UP){
        clockRate += 10;
        refreshDisplay();
      }
      else if (_btn == PRESSED_DOWN){
        clockRate -= 10;
        refreshDisplay();
      }
      else if (_exit == 1) _exit = 0;
    }
    _timer += clockRate;
  }
  refreshDisplay();
  analogWrite(backlightPin, backlightPwr);
  EEPROMWriteint(EEPROM_ADDRESS_CLOCK, clockRate);
}

void runDisplay(){
  static unsigned int _a;
  static unsigned int _b;
  static unsigned int _t;
  static unsigned long lastLow;
  
  if (menuPosition == 2){
    _a += gateStatus(0);
    _b += gateStatus(1);
    if (!gateStatus(0) || !gateStatus(1)){
      if (lastLow < millis())digitalWrite(backlightPin, 0);
      else digitalWrite(backlightPin, backlightOn);
      lastLow = millis() + 750;
    }
    else digitalWrite(backlightPin, backlightOn);
    _t++;

    if (_t == 3000){
      if (_a < _t) _a = min(_a / 30, 99);
      else _a /= 30;
      if (_b < _t) _b = min(_b / 30, 99);
      else _b /= 30;
      timer2.revert_to_normal();
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
      timer2.setup();
    }
    if (digitalRead(backlightPin) != backlightOn){
      if (lastLow - 700 < millis()) digitalWrite(backlightPin, backlightOn);
    }
  }
}


void refreshDisplay(){
  timer2.revert_to_normal();
  switch (menuPosition){
    case 0:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.write(127);
      lcd.print(F("spd A "));
      lcd.write(126);
      lcd.print(F(" B tst"));
      lcd.write(126);
      if (testSpeed() > 0 && testSpeed() < 99999){
        lcd.setCursor(0, 1);
        lcd.print(testSpeed());
        lcd.print(F(" m/s"));
      }
      else {
        lcd.setCursor(0, 1);
        lcd.print(F(" spd A "));
        lcd.write(127);
        lcd.print(F(" B tst"));
      }
    break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.write(127);
      lcd.print(F("spd A "));
      lcd.write(127);
      lcd.print(F(" B tst"));
      lcd.write(126);
      if (testSpeed() > 0 && testSpeed() < 99999){
        lcd.setCursor(0, 0);
        lcd.print(testSpeed());
        lcd.print(F(" m/s"));
      }
      else {
        lcd.setCursor(0, 0);
        lcd.print(F(" spd A "));
        lcd.write(126);
        lcd.print(F(" B tst"));
      }
    break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Status"));
      lcd.write(255);
      lcd.print(F("testClk"));
      lcd.write(126);
      lcd.setCursor(0, 1);
      lcd.print(F("A:"));
      lcd.setCursor(10, 1);
      lcd.print(F("B: "));
    break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Distance To Trigger"));
      lcd.setCursor(0, 1);
      lcd.print(distToTarget);
      lcd.print(F(" mm"));
    break;
    case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Pre-FlashDelay0"));
      lcd.setCursor(0, 1);
      lcd.print(_tTimeOffset[0]);
      lcd.print(F(" us"));
    break;
    case 5:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Pre-FlashDelay1"));
      lcd.setCursor(0, 1);
      lcd.print(_tTimeOffset[1]);
      lcd.print(F(" us"));
    break;
    case 6:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("2 "));  
      if (gunPin) lcd.print(gunPin);
      else lcd.print(F(" "));
      lcd.print(F(" 11  12  13"));
      lcd.setCursor(0, 1);
      lcd.print(F("- G  C   F   F"));
    break;
  }
  timer2.setup();
}

void toggleBacklight(){
  backlightOn = 1 - backlightOn;
  digitalWrite(backlightPin, backlightOn);
}

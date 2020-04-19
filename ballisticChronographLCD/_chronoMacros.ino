
unsigned long testAB(){
  return doTest(0);
}

unsigned long testBA(){
  return doTest(1);
}

unsigned long doTest(byte _backward){
  unsigned long _bStartTime;
  unsigned long _t = millis() + _bTimeout;
  boolean done = false;
  lcd.clear();
  while (!done){
    done = true;
    if (_backward) {
      while ((gatePort & 0b00000100) && (millis() < _t)){};
    }
    else {
      while ((gatePort & 0b00000010) && (millis() < _t)){};
    }
    _bStartTime = timer2.get_count();
    unsigned long _u = _bMinTime + _bStartTime;
    //while ((gatePort & 0b00000100) && (timer2.get_count() < _u) && (millis() < _t)){};
    if (_backward) {
      while ((gatePort & 0b00000010) && (millis() < _t)){};
    }
    else {
      while ((gatePort & 0b00000100) && (millis() < _t)){};
    }
    bulletDepartureTime = timer2.get_count();
    //if (bulletDepartureTime < _u) done = true;
  }
  
  if (millis() > _t) {
    bulletTransitTime = 0;
    return 0;
  }

  bulletTransitTime = bulletDepartureTime - _bStartTime;
  if (_tOn) triggerFlash();
  refreshDisplay();
  return bulletTransitTime;
}














void macro(){
  digitalWrite(backlightPin, 0);
  if (camPin){
    pinMode(camPin, OUTPUT);
    Serial.println(F("Camera Triggered"));
    delay(500);
  }
  else Serial.println(F("No Camera"));
  if (gunPin){
    if (!safety) {
      Serial.println(F("Gun Triggered"));
      pinMode(gunPin, OUTPUT);
      testAB();
      pinMode(gunPin, INPUT);
      triggerFlash();
    }
    else {
      Serial.println(F("Gun Available, Safety On"));
      Serial.print(triggerNow());
      Serial.println(" Triggers");
      Serial.println("Safety On");
    }
  }
  else {
    Serial.println(F("No Gun"));
    testAB();
    triggerFlash();
  }
  if (gunPin) pinMode(gunPin, INPUT);
  if (camPin) pinMode(camPin, INPUT);
  if (backlightOn){
    delay(500);
    digitalWrite(backlightPin, backlightOn);
  }
  Serial.println(F("DONE"));
}

void triggerFlash(){
  unsigned long _tTimeAct[MAX_TRIGGERS];
  byte _tRemaining = 0;
  unsigned long _t = bulletTransitTime;
  
  _t *= distToTarget;
  _t /= GATE_SEPARATION;
  _t += bulletDepartureTime;
  
  for (byte i = 0; i < MAX_TRIGGERS; i++){
    _tTimeAct[i] = _t - _tTimeOffset[i];
    if (_tPin[i] != 255) _tRemaining++;
  }
  while (_tRemaining){
    for (byte i = 0; i < MAX_TRIGGERS; i++){
      if (_tPin[i] != 255 && micros() > _tTimeAct[i]) {
        pinMode(_tPin[i], OUTPUT);
        _tRemaining--;
        _bTrigTime = micros();
      }
    }
  }
  delay(800);
  for (byte i = 0; i < MAX_TRIGGERS; i++){
    if (_tPin[i] != 255) pinMode(_tPin[i], INPUT);
  }
}

byte triggerNow(){ //Returns number of flashes fired
  byte _u;
  digitalWrite(backlightPin, 0);
  Serial.println(F("GO"));
  if (camPin){
    pinMode(camPin, OUTPUT);
    Serial.println(F("Camera Triggered"));
    delay(500);
  }
  for (byte i = 0; i < MAX_TRIGGERS; i++){
    if (_tPin[i] != 255 ){
      pinMode(_tPin[i], OUTPUT);
      _u++;
    }
  }
  delay(500);
  Serial.println(F("DONE"));
  if (camPin) pinMode(camPin, INPUT);
  if (backlightOn){
    delay(500);
    digitalWrite(backlightPin, backlightOn);
  }
  for (byte i = 0; i < MAX_TRIGGERS; i++){
    if (_tPin[i] != 255 ) pinMode(_tPin[i], INPUT);
  }
  return _u;
}

void practiceRoutine(){
  timer2.revert_to_normal();
  lcd.setCursor(1, 0);
  lcd.print("<");
  lcd.setCursor(1, 0);
  delay(200);
  pinMode(2, OUTPUT);
  delay(800);
  pinMode(2, INPUT);
  lcd.print("  3<");
  lcd.setCursor(4, 0);
  delay(200);
  pinMode(3, OUTPUT);
  delay(800);
  pinMode(3, INPUT);
  lcd.print("  11<");
  lcd.setCursor(8, 0);
  delay(200);
  pinMode(11, OUTPUT);
  delay(800);
  pinMode(11, INPUT);
  lcd.print("  12<");
  lcd.setCursor(12, 0);
  delay(200);
  pinMode(12, OUTPUT);
  delay(800);
  pinMode(12, INPUT);
  lcd.print(" >13");
  delay(200);
  pinMode(13, OUTPUT);
  delay(800);
  pinMode(13, INPUT);  
}

void metronome(){
  unsigned long _timer = millis();
  byte _exit = 2;
  digitalWrite(backlightPin, 0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(clockRate);
  delay(750);
  while (_exit){
    digitalWrite(backlightPin, 0);
    while (_timer + clockRate - 200 > millis() && _exit){
      byte _btn = button();
      if (!_btn)_exit = 1;
      else if (_btn == PRESSED_DOWN) {
        clockRate--;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(clockRate);
      }
      else if (_btn == PRESSED_UP) {
        clockRate++;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(clockRate);
      }
      else if (_exit == 1) _exit = 0;
    }
    digitalWrite(backlightPin, 1);
    while (_timer + clockRate > millis() && _exit){
      byte _btn = button();
      if (!_btn)_exit = 1;
      else if (_btn == PRESSED_DOWN) {
        clockRate--;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(clockRate);
      }
      else if (_btn == PRESSED_UP) {
        clockRate++;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(clockRate);
      }
      else if (_exit == 1) _exit = 0;
    }
    _timer += clockRate;
  }
  refreshDisplay();
  digitalWrite(backlightPin, backlightOn);
  EEPROM.write(0, clockRate - 900);
}

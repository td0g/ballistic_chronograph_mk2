void enableTriggering(){
  triggeringEnabled = 1;
  pinMode(gunPin, OUTPUT);
  pinMode(camPin, OUTPUT);
  digitalWrite(gunPin, 0);
  EEPROM.update(EEPROM_ADDRESS_TRIGGERING, triggeringEnabled);
}

void disableTriggering(){
  triggeringEnabled = 0;
  pinMode(gunPin, INPUT);
  pinMode(camPin, INPUT);
  EEPROM.update(EEPROM_ADDRESS_TRIGGERING, triggeringEnabled);
}


boolean setTrigger(byte _pin, unsigned long _comp){
  for (byte i = 0; i < 2; i++){
    if (_pin == _tPin[i]) {
      _tTimeOffset[i] = _comp;
      bitSet(_tOn, i);
      return true;
    }
  }
  for (byte i = 0; i < 2; i++){
    if (!(_tOn & (1 << i))){
      _tOn = _tOn | (1 << i);
      _tPin[i] = _pin;
      _tTimeOffset[i] = _comp;
      return true;
    }
  }
  return false;
}




byte triggerCount(){
  byte _t = 0;
  for (byte i = 0; i < 2; i++){
    if (_tOn & (1 << i)) _t++;
  }
  return _t;
}


boolean clearTrigger(byte _pin){
  for (byte i = 0; i < 2; i++){
    if (_tPin[i] == _pin){
      bitClear(_tOn, i);
      return true;
    }
  }
  return false;
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
      //testAB();
      pinMode(gunPin, INPUT);
      //triggerFlash();
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
    //testAB();
    //triggerFlash();
  }
  if (gunPin) pinMode(gunPin, INPUT);
  if (camPin) pinMode(camPin, INPUT);
  if (backlightOn){
    delay(500);
    analogWrite(backlightPin, backlightPwr);
  }
  Serial.println(F("DONE"));
}
/*
void triggerFlash(){
  unsigned long _tTimeAct[MAX_TRIGGERS];
  byte _tRemaining = 0;
  unsigned long _t = bulletTransitTime;
  
  _t *= distToTarget;
  _t /= gateSeparation;
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
*/

byte triggerNow(){ //Returns number of flashes fired
  byte _u;
  digitalWrite(backlightPin, 0);
  Serial.println(F("GO"));
  if (camPin){
    pinMode(camPin, OUTPUT);
    Serial.println(F("Camera Triggered"));
    delay(500);
  }
  for (byte i = 0; i < 2; i++){
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
    analogWrite(backlightPin, backlightPwr);
  }
  for (byte i = 0; i < 2; i++){
    if (_tPin[i] != 255 ) pinMode(_tPin[i], INPUT);
  }
  return _u;
}

void practiceRoutine(){
  //timer2.revert_to_normal();
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

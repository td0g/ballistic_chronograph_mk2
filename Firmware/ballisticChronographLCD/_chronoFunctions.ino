

byte gateStatus(byte _g){
  switch (_g){
    case 0: return ((gatePort >> 1) & 1);
    case 1: return ((gatePort >> 2) & 1);
  }
  return ((gatePort >> 1) & 3);
}



boolean clearTrigger(byte _pin){
  for (byte i = 0; i < MAX_TRIGGERS; i++){
    if (_tPin[i] == _pin){
      bitClear(_tOn, i);
      return true;
    }
  }
  return false;
}


float testSpeed(){
  //returns speed in m/s

  //  (Gate dist(mm) * (1m/1000mm) / Test Time (.5us) * (1s / 2000000))
  // = Gate Dist / Test Time * 2000
  float _t;
  _t = GATE_SEPARATION;
  _t *= 2000;
  _t /= bulletTransitTime;
  return _t;
}


void liveFeed(){
  unsigned long nextPrint = millis()+100;
  boolean Ahigh = false;
  boolean Bhigh = false;
  boolean Alow = false;
  boolean Blow = false;
  boolean Afail = false;
  boolean Bfail = false;
  while (!Serial.available() && BUTTON_INPUT > 800){
    while (millis() < nextPrint && !Serial.available() && BUTTON_INPUT > 800){
      if (gateStatus(0)) Ahigh = true;
      else Alow = true;
      if (gateStatus(1)) Bhigh = true;
      else Blow = true;
    }
    Serial.print(Ahigh);
    Serial.print(F(" Ahigh / Alow "));
    Serial.print(Alow);
    Serial.print(dindent);
    Serial.print(F("  "));
    Serial.print(Bhigh);
    Serial.print(F(" Bhigh / Blow "));
    Serial.println(Blow);
    if(Alow) Afail = true;
    if (Blow) Bfail = true;
    Ahigh = false;
    Alow = false;
    Bhigh = false;
    Blow = false;
    nextPrint += 500;
  }
  Serial.println(F("End of live feed"));
  Serial.println();
  Serial.print(F("Gate A "));
  if (Afail)  Serial.println(F("FAIL"));
  else Serial.println(F("PASS"));
  Serial.print(F("Gate B "));
  if (Bfail) Serial.println(F("FAIL"));
  else Serial.println(F("PASS"));
  Serial.println();
  while (Serial.available()) Serial.read();
}

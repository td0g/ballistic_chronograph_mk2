


 //Performs chronograph test and returns time in half-micros
unsigned long measureHalfMicros(byte _backward){
  //Calculate maximum time between gates (given TEST_MIN_SPEED)
  unsigned long _secondGateMaxDelay = gateSeparation;
  _secondGateMaxDelay *= 2000;
  _secondGateMaxDelay /= TEST_MIN_SPEED;

  //Prepare for testing
  boolean done = false;
  unsigned long _triggerTime;
  unsigned int _bulletTransitCount = 0;
  unsigned int _triggerOvf;
  unsigned long _testTicks;
  unsigned long _testOvf;
  volatile unsigned int _ovfCount = 0;
  
  unsigned long _temp = gateSeparation * 2000 / maximumSpeed;
  unsigned int _testMinTicks = min(_temp, 60000);
   _temp = gateSeparation * 2000000 / maximumSpeed;
  bulletTransitTime = 0;
  _ovfCount = 0;
  lcd.clear();
  menuPosition |= 0b10000000;
  disableInterrupts();

  //Keep trying to test until valid data collected
  while (!done){
  //Turn off interrupts so that the microcontroller can focus on watching the gates
    if (!_backward) {
      while (GATE_B){};
      TCNT1 = 0; //reset timer
      ovfCount = 0;
  //Turn on the watchdog timer
      cli();
      wdt_reset();
      //WDTCSR = WDT_ON;
      sei();
      wdt_reset();
      while (TCNT1 < _testMinTicks){}; //Minimum speed delay
      while (GATE_A){};
      _testTicks = TCNT1;
      _testOvf = ovfCount;
      _testOvf = _testOvf << 16;
      _testTicks += _testOvf;
    }
    else {
      while (GATE_A){};
      TCNT1 = 0; //reset timer
      ovfCount = 0;
  //Turn on the watchdog timer
      cli();
      wdt_reset();
      //WDTCSR = WDT_ON;
      sei();
      wdt_reset();
      while (TCNT1 < _testMinTicks){}; //Minimum speed delay
      while (GATE_B){};
      _testTicks = TCNT1;
      _testOvf = ovfCount;
      _testOvf = _testOvf << 16;
      _testTicks += _testOvf;
    }

//Turn off WDT
  cli();
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 0;
  sei();
  done = true;
  }
  bulletTransitTime += _bulletTransitCount;
  if (distToTarget && triggeringEnabled) {
    ovfCount = 0;
    sei();  //Timer 1 overflow interrupt required
    unsigned long triggerTicks0 = distToTarget * bulletTransitTime / gateSeparation ;
    unsigned long triggerTicks1 = triggerTicks0 - (2 * _tTimeOffset[1]);
    triggerTicks0 -= (2 * _tTimeOffset[0]);

//Both triggers simultaneously
    if (triggerTicks0 == triggerTicks1){
      if (triggerTicks0 > 65535){
        unsigned long _triggerOvf = triggerTicks0;
        _triggerOvf <= 16;
        _triggerOvf &= 0b00000000000000001111111111111111;
        triggerTicks0 &= 0b00000000000000001111111111111111;
        while (ovfCount < _triggerOvf){};
        while (TCNT1 < triggerTicks0 && _ovfCount == _triggerOvf){};
        pinMode(12, OUTPUT);
        pinMode(13, OUTPUT);
      }
      else {
        while (TCNT1 < triggerTicks0 && !_ovfCount){};
        pinMode(12, OUTPUT);
        pinMode(13, OUTPUT);
      }
    }

//Pin 12 first, then 13
    else {
      unsigned long _triggerOvf1 = triggerTicks1;
      _triggerOvf1 <= 16;
      _triggerOvf1 &= 0b00000000000000001111111111111111;
      triggerTicks1 &= 0b00000000000000001111111111111111;
      unsigned long _triggerOvf0 = triggerTicks0;
      _triggerOvf0 <= 16;
      _triggerOvf0 &= 0b00000000000000001111111111111111;
      triggerTicks0 &= 0b00000000000000001111111111111111;
      if (triggerTicks0 < triggerTicks1){
        if (triggerTicks0 > 65535){
          while (ovfCount < _triggerOvf0){};
          while (TCNT1 < triggerTicks0 && _ovfCount == _triggerOvf0){};
          pinMode(12, OUTPUT);
          while (ovfCount < _triggerOvf1){};
          while (TCNT1 < triggerTicks1 && _ovfCount == _triggerOvf1){};
          pinMode(13, OUTPUT);
        }
        else {
          while (TCNT1 < triggerTicks0 && !_ovfCount){};
          pinMode(12, OUTPUT);      
          if (triggerTicks1 > 65535){
            while (ovfCount < _triggerOvf1){};
            while (TCNT1 < triggerTicks1 && _ovfCount == _triggerOvf1){};
            pinMode(13, OUTPUT);
          }
          else {
            while (TCNT1 < triggerTicks1 && !_ovfCount){};
            pinMode(13, OUTPUT);
          }
        }
      }
  //Pin 13 first, then 12
      else {
        if (triggerTicks1 > 65535){
          while (ovfCount < _triggerOvf1){};
          while (TCNT1 < triggerTicks1 && _ovfCount == _triggerOvf1){};
          pinMode(13, OUTPUT);
          while (ovfCount < _triggerOvf0){};
          while (TCNT1 < triggerTicks0 && _ovfCount == _triggerOvf0){};
          pinMode(12, OUTPUT);
        }
        else {
          while (TCNT1 < triggerTicks1 && !_ovfCount){};
          pinMode(13, OUTPUT);      
          if (triggerTicks0 > 65535){
            while (ovfCount < _triggerOvf0){};
            while (TCNT1 < triggerTicks0 && _ovfCount == _triggerOvf0){};
            pinMode(12, OUTPUT);
          }
          else {
            while (TCNT1 < triggerTicks0 && !_ovfCount){};
            pinMode(12, OUTPUT);
          }
        }
      }
    }
  }
  enableInterrupts();
  bulletTransitTime = _testTicks;
  return _testTicks;
}




//Returns last test speed (if units == 0 then m/s; if units == 1 then FPS)
float lastTestSpeed(){
  //  (Gate dist(mm) * (1m/1000mm) / Test Time (.5us) * (1s / 2000000))
  // = Gate Dist / Test Time * 2000
  float _t;
  _t = gateSeparation;
  _t *= 2000;
  _t /= bulletTransitTime;
  if (units) _t *= FPS_CONVERSION;
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
      if (GATE_A) Ahigh = true;
      else Alow = true;
      if (GATE_B) Bhigh = true;
      else Blow = true;
    }
    Serial.print(Ahigh);
    Serial.print(F(" Ahigh / Alow "));
    Serial.print(Alow);
    Serial.print(F("   "));
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

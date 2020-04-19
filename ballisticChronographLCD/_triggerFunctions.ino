

boolean setTrigger(byte _pin, unsigned long _comp){
  for (byte i = 0; i < MAX_TRIGGERS; i++){
    if (_pin == _tPin[i]) {
      _tTimeOffset[i] = _comp;
      bitSet(_tOn, i);
      return true;
    }
  }
  for (byte i = 0; i < MAX_TRIGGERS; i++){
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
  for (byte i = 0; i < MAX_TRIGGERS; i++){
    if (_tOn & (1 << i)) _t++;
  }
  return _t;
}

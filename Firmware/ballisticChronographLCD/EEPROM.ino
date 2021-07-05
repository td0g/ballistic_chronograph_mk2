unsigned int EEPROMReadint(unsigned int _i){
  unsigned int _t;
  _t = EEPROM.read(_i);
  _t *= 256;
  _t += EEPROM.read(_i + 1);
  return (_t);
}

void EEPROMWriteint(unsigned int _i, unsigned int _d){
  byte t;
  t = _d;
  EEPROM.update(_i+1, t);
  t = _d >> 8;
  EEPROM.update(_i, t);
}

ISR(WDT_vect){
//This is called when the first gate has transited but some of the others have not.
//Cannot use Serial.print() here, so use the serialChar and serialString functions instead.
  enableSerial();
  serialString("\n\tTIMEOUT");
  serialChar('\n');
  #ifndef GATE_C_PIN
    return;
  #endif
  
  serialString("Time:");
  volatile byte J = 1;
  while (J < GATE_COUNT && testTimes[J]){
      serialString("\t\t");
      serialLong(testTimes[J]);
      J++;
  }  
  
  serialString("\ndT:  ");
  for (byte j = J-1; j > 0; j--)testTimes[j] = testTimes[j] - testTimes[j-1];
  for (byte j = 1; j < J; j++){
    serialString("\t\t");
    serialLong(testTimes[j]);
  }
  
  serialString("\nSpeed:");
  for (byte j = 0; j < J; j++){
    serialString("\t\t");
    float _s = gateSeparation[j] * 2000;
    _s /= testTimes[j];
    serialString(String(_s, 2));
  }
}



void serialChar(char _c){
    //while ((UCSR0A & _BV (TXC0)) == 0){};
  UDR0 = _c; //https://forum.arduino.cc/index.php?topic=86485.0
  while (!(UCSR0A & (1<<UDRE0))){};
  //for (int i = 0; i < 30000; i++){
  //  __asm__ __volatile__ ("nop\n\t");
 // }
}



void serialString(String _s){
  static char _c[12];
  byte len = _s.length();
  _s.toCharArray(_c, len);
  for (byte i = 0; i < len; i++) serialChar(_c[i]);
}



void serialLong(unsigned long _l){
  char _c[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};
  ltoa(_l, _c, 10);
  for (byte i = 0; i < 7; i++) serialChar(_c[i]);
}

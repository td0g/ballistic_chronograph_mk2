

void processCommand(){
  if (serialBuffer[0] == 'b') {backlightOn = parseNumber('b',1 - backlightOn);digitalWrite(backlightPin, backlightOn);}
  else if (serialBuffer[0] == 'd') {distToTarget = parseNumber('d', 0); Serial.println(distToTarget);}
  else if (serialBuffer[0] == 'f') liveFeed();
  else if (serialBuffer[0] == 'g') {Serial.println(testAB()); Serial.print(F("Speed in m/s: ")); Serial.println(testSpeed());}
  else if (serialBuffer[0] == 'h') printHelp();
  else if (serialBuffer[0] == 'm') {
    camPin = parseNumber('m', 0);
    if (!camPin) Serial.print(F("No Camera"));
    else {
      Serial.print(F("Camera Pin "));
      Serial.println(camPin);
    }
  }
  else if (serialBuffer[0] == 'n') {
    gunPin = parseNumber('n', 0);
    if (!gunPin) Serial.print(F("No Gun"));
    else {
      Serial.print(F("Gun Pin "));
      Serial.println(gunPin);
    }
  }
  else if (serialBuffer[0] == 'p'){
    if (setTrigger(parseNumber('p',0), parseNumber('t', 0))) {
      Serial.print(F("Trigger pin, time offset "));
      Serial.print(parseNumber('p',0));
      Serial.print(" ");
      Serial.print(parseNumber('t',0));
      if (parseNumber('h', 0) > 0) Serial.print(F(" - HIGHSPEED"));
      Serial.println();
    }
    else Serial.println("ERROR");
  }
  else if (serialBuffer[0] == 'q') macro();
  else if (serialBuffer[0] == 'r'){
    if (clearTrigger(parseNumber('r',-1))) {
      Serial.print(F("Trigger removed, pin "));
      Serial.println(parseNumber('r',0));
    }
    else Serial.println("ERROR");
  }
  else if (serialBuffer[0] == 's') {
    safety = parseNumber('s',0);
    Serial.print(F("Safety O"));
    if (safety) Serial.println("n");
    else Serial.println(F("ff"));
  }
  else if (serialBuffer[0] == 't') triggerNow();
  else if (serialBuffer[0] == 'x'){gunPin = parseNumber('x', 0); Serial.print(F("Gun assigned to pin ")); Serial.println(gunPin);}
  else if (serialBuffer[0] == 'y'){_bMinTime = 1000000 * GATE_SEPARATION / parseNumber('y', 1); Serial.print(F("Max Time (us)")); Serial.println(_bMinTime);}
  else if (serialBuffer[0] == 'z'){_bTimeout = parseNumber('z',1000000); Serial.print(F("Timeout (us) ")); Serial.println(_bTimeout);}
  else {
    Serial.println(" Command not recognized");
    Serial.println(sofar);
  }
  Serial.println();
}

void printHelp(){
  Serial.println(F("HELP:"));
  Serial.println(F("b(X) - Turn on/off backlight"));
  Serial.print(F("dXX - Set trigger distance (currently "));
  Serial.print(distToTarget);
  Serial.println(F(" m)"));
  Serial.println(F("f - Live feed until enter pressed"));
  Serial.println(F("g - Start Test"));
  Serial.println(F("m(X) - Set / Clear Camera Pin"));
  Serial.println(F("n(X) - Set / Clear Gun Pin"));
  Serial.println(F("pXX (tXX) - Set trigger on pin, set us offset, h1 = HIGHSPEED"));
  Serial.println(F("Available Trigger Pins: 11, 12, 13"));
  Serial.println(F("rXX - Remove trigger"));
  Serial.print(F("s - Safety on/off (Saftey is currently o"));
  if (safety) Serial.println("n");
  else Serial.println("ff");
  Serial.println(F("t - Test flash triggers now"));
  Serial.print(F("xXX - Set gun pin (currently "));
  Serial.print(gunPin);
  Serial.println(F(")"));
  Serial.print(F("yXX - Set minimum speed in m/s (currently "));
  Serial.print(_bMinTime);
  Serial.println(F(" us)"));
  Serial.print(F("zXX - Set test timeout in microseconds (currently "));
  Serial.print(_bTimeout);
  Serial.println(F(" us)"));
  Serial.println();
  Serial.print(F("Current triggers: "));
  Serial.println(triggerCount());
  Serial.println();
}


float parseNumber(char code,float val) {
  char *ptr=serialBuffer + left;  // start at the beginning of buffer
  while((long)ptr > 1 && (*ptr) && (long)ptr < (long)serialBuffer+sofar) {  // walk to the end
    if(*ptr==code) {  // if you find code on your walk,
      return atof(ptr+1);  // convert the digits that follow into a float and return it
    }
    ptr++;  // take a step from here to the letter after the next space
  }
  return val;  // end reached, nothing found, return default val.
}


void getCommand(){
  if (Serial.available()){
  char c;
    c = Serial.read();
    if(c == '\n') {
      processCommand();
      sofar=0;
    }
    else if(c != 0 && sofar < MAX_BUF) serialBuffer[sofar++]=c;
  }
}

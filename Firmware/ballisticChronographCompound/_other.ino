void setPinStates(){
    #ifdef PULLUP
    pinMode(GATE_A_PIN, INPUT_PULLUP);
    pinMode(GATE_B_PIN, INPUT_PULLUP);
    #ifdef GATE_C_PIN
      pinMode(GATE_C_PIN, INPUT_PULLUP);
      #ifdef GATE_D_PIN
        pinMode(GATE_D_PIN, INPUT_PULLUP);
        #ifdef GATE_E_PIN
          pinMode(GATE_E_PIN, INPUT_PULLUP);
          #ifdef GATE_F_PIN
            pinMode(GATE_F_PIN, INPUT_PULLUP);
            #ifdef GATE_G_PIN
              pinMode(GATE_G_PIN, INPUT_PULLUP);          
              #ifdef GATE_H_PIN
                pinMode(GATE_H_PIN, INPUT_PULLUP);          
                #ifdef GATE_I_PIN
                  pinMode(GATE_I_PIN, INPUT_PULLUP);
                  #ifdef GATE_J_PIN
                    pinMode(GATE_J_PIN, INPUT_PULLUP);
                    #ifdef GATE_K_PIN
                      pinMode(GATE_K_PIN, INPUT_PULLUP);
                      #ifdef GATE_L_PIN
                        pinMode(GATE_L_PIN, INPUT_PULLUP);
                        #ifdef GATE_M_PIN
                          pinMode(GATE_M_PIN, INPUT_PULLUP);
                          #ifdef GATE_N_PIN
                            pinMode(GATE_N_PIN, INPUT_PULLUP);
                            #ifdef GATE_O_PIN
                              pinMode(GATE_O_PIN, INPUT_PULLUP);
                              #ifdef GATE_P_PIN
                                pinMode(GATE_P_PIN, INPUT_PULLUP);
                              #endif
                            #endif
                          #endif
                        #endif
                      #endif
                    #endif
                  #endif
                #endif
              #endif
            #endif
          #endif
        #endif
      #endif
    #endif
  #endif
}





void printStats(){
  Serial.print(F("\n\n###################################\n\tTEST NUMBER "));
  Serial.print(testIndex);
  testIndex++;
  Serial.print(F("\nGate #:\t\t"));
  for (byte i = 0; i < GATE_COUNT; i++){
    TAB;
    Serial.print(i+1);
  }
  Serial.print(F("\nTransit Time (us):\t"));
  for (byte i = 0; i < GATE_COUNT; i++){
    TAB;
    unsigned long halfTestTime = testTimes[i] / 2;
    Serial.print(halfTestTime);
  }
  
  Serial.println(F("\n\nGate span | Time to traverse gate (uS) | Speed (m/s) | Speed (fps) | Acceleration from prior span (m/s^2): "));
  for (byte n = 1; n < GATE_COUNT; n++){
    for (byte i = 0; i < GATE_COUNT-n; i++){
        Serial.print(i+1);
        Serial.print(F("-"));
        Serial.print(i+n+1);
        Serial.print(F(":\t\t"));
        Serial.print((testTimes[i+n] - testTimes[i]) / 2);
        TAB;
        Serial.print(calcSpeedMPS(i, i+n));
        TAB;
        Serial.print(calcSpeedFPS(i, i+n));
        TAB;
        if (i > 0){
          float acceleration = calcSpeedMPS(i, i+n)-  calcSpeedMPS(i-1, i+n-1);
          acceleration = acceleration / (testTimes[i+n] - testTimes[i+n-1] + testTimes[i]-testTimes[i - 1]);
          acceleration = acceleration * 4000000;
          Serial.print(acceleration);
        }
        Serial.println();
    }
    Serial.println();
  }
  #ifdef GATE_C_PIN
    Serial.println(F("\nAcceleration Calculations"));
    for (byte i = GATE_COUNT; i > 2; i--){
      Serial.print(F(" -"));
      TAB;
      TAB;
      Serial.print(i);
    }
    for (byte i = 0; i < GATE_COUNT-2; i++){
      Serial.println();
      Serial.print(i + 1);
      TAB;
      for (byte j = GATE_COUNT-1; j > i + 1 ; j--){
        for (byte l = i+1; l < j; l++){
          Serial.print(calcLinearAcceleration(i, l, j));
          if (l + 1 != j) Serial.print(F(","));
        }
       TAB;
      }
    }
  #endif


//Wait until Serial is all finished
    //delay(250);
    while ((UCSR0A & _BV (TXC0)) == 0){};
}

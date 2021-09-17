void runDiagnostics(){
  
  //Diagnostics Check
  #ifdef DIAGNOSTICS_CHECKS
    unsigned long d = DIAGNOSTICS_CHECKS;
    bool diagPass = true;
    while(GATE_A && d) d--;
    if (d) {
      diagPass = false;
      Serial.println(F("Gate A failed diagnostics check"));
    }
    d = DIAGNOSTICS_CHECKS;
    while(GATE_B && d) d--;
    if (d) {
      diagPass = false;
      Serial.println(F("Gate B failed diagnostics check"));
    }
    #ifdef GATE_C_PIN
      d = DIAGNOSTICS_CHECKS;
      while(GATE_C && d) d--;
      if (d) {
        diagPass = false;
        Serial.println(F("Gate C failed diagnostics check"));
      }
      #ifdef GATE_D_PIN
        d = DIAGNOSTICS_CHECKS;
        while(GATE_D && d) d--;
        if (d) {
          diagPass = false;
          Serial.println(F("Gate D failed diagnostics check"));
        }
        #ifdef GATE_E_PIN
          d = DIAGNOSTICS_CHECKS;
          while(GATE_E && d) d--;
          if (d) {
            diagPass = false;
            Serial.println(F("Gate E failed diagnostics check"));
          }
          #ifdef GATE_F_PIN
            d = DIAGNOSTICS_CHECKS;
            while(GATE_F && d) d--;
            if (d) {
              diagPass = false;
              Serial.println(F("Gate F failed diagnostics check"));
            }
            #ifdef GATE_G_PIN
              d = DIAGNOSTICS_CHECKS;
              while(GATE_G && d) d--; 
              if (d) {
                diagPass = false;
                Serial.println(F("Gate G failed diagnostics check"));
              }     
              #ifdef GATE_H_PIN
                d = DIAGNOSTICS_CHECKS;
                while(GATE_H && d) d--; 
                if (d) {
                  diagPass = false;
                  Serial.println(F("Gate H failed diagnostics check"));
                }      
                #ifdef GATE_I_PIN
                  d = DIAGNOSTICS_CHECKS;
                  while(GATE_I && d) d--;
                  if (d) {
                    diagPass = false;
                    Serial.println(F("Gate I failed diagnostics check"));
                  }
                  #ifdef GATE_J_PIN
                    d = DIAGNOSTICS_CHECKS;
                    while(GATE_J && d) d--;
                    if (d) {
                      diagPass = false;
                      Serial.println(F("Gate J failed diagnostics check"));
                    }
                    #ifdef GATE_K_PIN
                      d = DIAGNOSTICS_CHECKS;
                      while(GATE_K && d) d--;
                      if (d) {
                        diagPass = false;
                        Serial.println(F("Gate K failed diagnostics check"));
                      }
                      #ifdef GATE_L_PIN
                        d = DIAGNOSTICS_CHECKS;
                        while(GATE_L && d) d--;
                        if (d) {
                          diagPass = false;
                          Serial.println(F("Gate L failed diagnostics check"));
                        }
                        #ifdef GATE_M_PIN
                          d = DIAGNOSTICS_CHECKS;
                          while(GATE_M && d) d--;
                          if (d) {
                            diagPass = false;
                            Serial.println(F("Gate M failed diagnostics check"));
                          }
                          #ifdef GATE_N_PIN
                            d = DIAGNOSTICS_CHECKS;
                            while(GATE_N && d) d--;
                            if (d) {
                              diagPass = false;
                              Serial.println(F("Gate N failed diagnostics check"));
                            }
                            #ifdef GATE_O_PIN
                              d = DIAGNOSTICS_CHECKS;
                              while(GATE_O && d) d--;
                              if (d) {
                                diagPass = false;
                                Serial.println(F("Gate O failed diagnostics check"));
                              }
                              #ifdef GATE_P_PIN
                                d = DIAGNOSTICS_CHECKS;
                                while(GATE_P && d) d--;
                                if (d) {
                                  diagPass = false;
                                  Serial.println(F("Gate P failed diagnostics check"));
                                }
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

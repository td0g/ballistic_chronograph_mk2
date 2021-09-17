//Pin Selection Definitions
  #if (GATE_A_PIN == 2)
    #define GATE_A_PIN2 (PIND & 0b00000100)
  #elif (GATE_A_PIN == 3)
    #define GATE_A_PIN2 (PIND & 0b00001000)
  #elif (GATE_A_PIN == 4)
    #define GATE_A_PIN2 (PIND & 0b00010000)
  #elif (GATE_A_PIN == 5)
    #define GATE_A_PIN2 (PIND & 0b00100000)
  #elif (GATE_A_PIN == 6)
    #define GATE_A_PIN2 (PIND & 0b01000000)
  #elif (GATE_A_PIN == 7)
    #define GATE_A_PIN2 (PIND & 0b10000000)
  #elif (GATE_A_PIN == 8)
    #define GATE_A_PIN2 (PINB & 0b00000001)
  #elif (GATE_A_PIN == 9)
    #define GATE_A_PIN2 (PINB & 0b00000010)
  #elif (GATE_A_PIN == 10)
    #define GATE_A_PIN2 (PINB & 0b00000100)
  #elif (GATE_A_PIN == 11)
    #define GATE_A_PIN2 (PINB & 0b00001000)
  #elif (GATE_A_PIN == 12)
    #define GATE_A_PIN2 (PINB & 0b00010000)
  #elif (GATE_A_PIN == 13)
    #define GATE_A_PIN2 (PINB & 0b00100000)
  #elif (GATE_A_PIN == 14)
    #define GATE_A_PIN2 (PINC & 0b00000001)
  #elif (GATE_A_PIN == 15)
    #define GATE_A_PIN2 (PINC & 0b00000010)
  #elif (GATE_A_PIN == 16)
    #define GATE_A_PIN2 (PINC & 0b00000100)
  #elif (GATE_A_PIN == 17)
    #define GATE_A_PIN2 (PINC & 0b00001000)
  #elif (GATE_A_PIN == 18)
    #define GATE_A_PIN2 (PINC & 0b00010000)
  #elif (GATE_A_PIN == 19)
    #define GATE_A_PIN2 (PINC & 0b00100000)
  #else
    #error "You must set Gate A to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
  #endif

  #ifdef ACTIVE_LOW
    #define GATE_A GATE_A_PIN2
  #else
    #define GATE_A !GATE_A_PIN2
  #endif

  #ifndef GATE_AB_SEPARATION
    #define GATE_AB_SEPARATION GATE_SEPARATION_DEFAULT
  #endif
          
  #if (GATE_B_PIN == 2)
    #define GATE_B_PIN2 (PIND & 0b00000100)
  #elif (GATE_B_PIN == 3)
    #define GATE_B_PIN2 (PIND & 0b00001000)
  #elif (GATE_B_PIN == 4)
    #define GATE_B_PIN2 (PIND & 0b00010000)
  #elif (GATE_B_PIN == 5)
    #define GATE_B_PIN2 (PIND & 0b00100000)
  #elif (GATE_B_PIN == 6)
    #define GATE_B_PIN2 (PIND & 0b01000000)
  #elif (GATE_B_PIN == 7)
    #define GATE_B_PIN2 (PIND & 0b10000000)
  #elif (GATE_B_PIN == 8)
    #define GATE_B_PIN2 (PINB & 0b00000001)
  #elif (GATE_B_PIN == 9)
    #define GATE_B_PIN2 (PINB & 0b00000010)
  #elif (GATE_B_PIN == 10)
    #define GATE_B_PIN2 (PINB & 0b00000100)
  #elif (GATE_B_PIN == 11)
    #define GATE_B_PIN2 (PINB & 0b00001000)
  #elif (GATE_B_PIN == 12)
    #define GATE_B_PIN2 (PINB & 0b00010000)
  #elif (GATE_B_PIN == 13)
    #define GATE_B_PIN2 (PINB & 0b00100000)
  #elif (GATE_B_PIN == 14 || GATE_B_PIN == A0)
    #define GATE_B_PIN2 (PINC & 0b00000001)
  #elif (GATE_B_PIN == 15 || GATE_B_PIN == A1)
    #define GATE_B_PIN2 (PINC & 0b00000010)
  #elif (GATE_B_PIN == 16 || GATE_B_PIN == A2)
    #define GATE_B_PIN2 (PINC & 0b00000100)
  #elif (GATE_B_PIN == 17 || GATE_B_PIN == A3)
    #define GATE_B_PIN2 (PINC & 0b00001000)
  #elif (GATE_B_PIN == 18 || GATE_B_PIN == A4)
    #define GATE_B_PIN2 (PINC & 0b00010000)
  #elif (GATE_B_PIN == 19 || GATE_B_PIN == A5)
    #define GATE_B_PIN2 (PINC & 0b00100000)
  #else
    #error "You must set Gate B to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
  #endif

  #ifdef ACTIVE_LOW
    #define GATE_B GATE_B_PIN2
  #else
    #define GATE_B !GATE_B_PIN2
  #endif
  
  #ifdef GATE_C_PIN
    #ifndef GATE_BC_SEPARATION
      #define GATE_BC_SEPARATION GATE_SEPARATION_DEFAULT
    #endif
    #if (GATE_C_PIN == 2)
      #define GATE_C_PIN2 (PIND & 0b00000100)
    #elif (GATE_C_PIN == 3)
      #define GATE_C_PIN2 (PIND & 0b00001000)
    #elif (GATE_C_PIN == 4)
      #define GATE_C_PIN2 (PIND & 0b00010000)
    #elif (GATE_C_PIN == 5)
      #define GATE_C_PIN2 (PIND & 0b00100000)
    #elif (GATE_C_PIN == 6)
      #define GATE_C_PIN2 (PIND & 0b01000000)
    #elif (GATE_C_PIN == 7)
      #define GATE_C_PIN2 (PIND & 0b10000000)
    #elif (GATE_C_PIN == 8)
      #define GATE_C_PIN2 (PINB & 0b00000001)
    #elif (GATE_C_PIN == 9)
      #define GATE_C_PIN2 (PINB & 0b00000010)
    #elif (GATE_C_PIN == 10)
      #define GATE_C_PIN2 (PINB & 0b00000100)
    #elif (GATE_C_PIN == 11)
      #define GATE_C_PIN2 (PINB & 0b00001000)
    #elif (GATE_C_PIN == 12)
      #define GATE_C_PIN2 (PINB & 0b00010000)
    #elif (GATE_C_PIN == 13)
      #define GATE_C_PIN2 (PINB & 0b00100000)
    #elif (GATE_C_PIN == 14)
      #define GATE_C_PIN2 (PINC & 0b00000001)
    #elif (GATE_C_PIN == 15)
      #define GATE_C_PIN2 (PINC & 0b00000010)
    #elif (GATE_C_PIN == 16)
      #define GATE_C_PIN2 (PINC & 0b00000100)
    #elif (GATE_C_PIN == 17)
      #define GATE_C_PIN2 (PINC & 0b00001000)
    #elif (GATE_C_PIN == 18)
      #define GATE_C_PIN2 (PINC & 0b00010000)
    #elif (GATE_C_PIN == 19)
      #define GATE_C_PIN2 (PINC & 0b00100000)
    #else
      #error "You must set Gate C to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
    #endif

    #ifdef ACTIVE_LOW
      #define GATE_C GATE_C_PIN2
    #else
      #define GATE_C !GATE_C_PIN2
    #endif
  
    #ifdef GATE_D_PIN
      #ifndef GATE_CD_SEPARATION
        #define GATE_CD_SEPARATION GATE_SEPARATION_DEFAULT
      #endif
      #if (GATE_D_PIN == 2)
        #define GATE_D_PIN2 (PIND & 0b00000100)
      #elif (GATE_D_PIN == 3)
        #define GATE_D_PIN2 (PIND & 0b00001000)
      #elif (GATE_D_PIN == 4)
        #define GATE_D_PIN2 (PIND & 0b00010000)
      #elif (GATE_D_PIN == 5)
        #define GATE_D_PIN2 (PIND & 0b00100000)
      #elif (GATE_D_PIN == 6)
        #define GATE_D_PIN2 (PIND & 0b01000000)
      #elif (GATE_D_PIN == 7)
        #define GATE_D_PIN2 (PIND & 0b10000000)
      #elif (GATE_D_PIN == 8)
        #define GATE_D_PIN2 (PINB & 0b00000001)
      #elif (GATE_D_PIN == 9)
        #define GATE_D_PIN2 (PINB & 0b00000010)
      #elif (GATE_D_PIN == 10)
        #define GATE_D_PIN2 (PINB & 0b00000100)
      #elif (GATE_D_PIN == 11)
        #define GATE_D_PIN2 (PINB & 0b00001000)
      #elif (GATE_D_PIN == 12)
        #define GATE_D_PIN2 (PINB & 0b00010000)
      #elif (GATE_D_PIN == 13)
        #define GATE_D_PIN2 (PINB & 0b00100000)
      #elif (GATE_D_PIN == 14)
        #define GATE_D_PIN2 (PINC & 0b00000001)
      #elif (GATE_D_PIN == 15)
        #define GATE_D_PIN2 (PINC & 0b00000010)
      #elif (GATE_D_PIN == 16)
        #define GATE_D_PIN2 (PINC & 0b00000100)
      #elif (GATE_D_PIN == 17)
        #define GATE_D_PIN2 (PINC & 0b00001000)
      #elif (GATE_D_PIN == 18)
        #define GATE_D_PIN2 (PINC & 0b00010000)
      #elif (GATE_D_PIN == 19)
        #define GATE_D_PIN2 (PINC & 0b00100000)
      #else
        #error "You must set Gate D to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
      #endif
      
      #ifdef ACTIVE_LOW
        #define GATE_D GATE_D_PIN2
      #else
        #define GATE_D !GATE_D_PIN2
      #endif
  

      #ifdef GATE_E_PIN
        #ifndef GATE_DE_SEPARATION
          #define GATE_DE_SEPARATION GATE_SEPARATION_DEFAULT
        #endif
        #if (GATE_E_PIN == 2)
          #define GATE_E_PIN2 (PIND & 0b00000100)
        #elif (GATE_E_PIN == 3)
          #define GATE_E_PIN2 (PIND & 0b00001000)
        #elif (GATE_E_PIN == 4)
          #define GATE_E_PIN2 (PIND & 0b00010000)
        #elif (GATE_E_PIN == 5)
          #define GATE_E_PIN2 (PIND & 0b00100000)
        #elif (GATE_E_PIN == 6)
          #define GATE_E_PIN2 (PIND & 0b01000000)
        #elif (GATE_E_PIN == 7)
          #define GATE_E_PIN2 (PIND & 0b10000000)
        #elif (GATE_E_PIN == 8)
          #define GATE_E_PIN2 (PINB & 0b00000001)
        #elif (GATE_E_PIN == 9)
          #define GATE_E_PIN2 (PINB & 0b00000010)
        #elif (GATE_E_PIN == 10)
          #define GATE_E_PIN2 (PINB & 0b00000100)
        #elif (GATE_E_PIN == 11)
          #define GATE_E_PIN2 (PINB & 0b00001000)
        #elif (GATE_E_PIN == 12)
          #define GATE_E_PIN2 (PINB & 0b00010000)
        #elif (GATE_E_PIN == 13)
          #define GATE_E_PIN2 (PINB & 0b00100000)
        #elif (GATE_E_PIN == 14)
          #define GATE_E_PIN2 (PINC & 0b00000001)
        #elif (GATE_E_PIN == 15)
          #define GATE_E_PIN2 (PINC & 0b00000010)
        #elif (GATE_E_PIN == 16)
          #define GATE_E_PIN2 (PINC & 0b00000100)
        #elif (GATE_E_PIN == 17)
          #define GATE_E_PIN2 (PINC & 0b00001000)
        #elif (GATE_E_PIN == 18)
          #define GATE_E_PIN2 (PINC & 0b00010000)
        #elif (GATE_E_PIN == 19)
          #define GATE_E_PIN2 (PINC & 0b00100000)
        #else
          #error "You must set Gate E to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
        #endif

        #ifdef ACTIVE_LOW
          #define GATE_E GATE_E_PIN2
        #else
          #define GATE_E !GATE_E_PIN2
        #endif
  
        #ifdef GATE_F_PIN
          #ifndef GATE_EF_SEPARATION
            #define GATE_EF_SEPARATION GATE_SEPARATION_DEFAULT
          #endif
          #if (GATE_F_PIN == 2)
            #define GATE_F_PIN2 (PIND & 0b00000100)
          #elif (GATE_F_PIN == 3)
            #define GATE_F_PIN2 (PIND & 0b00001000)
          #elif (GATE_F_PIN == 4)
            #define GATE_F_PIN2 (PIND & 0b00010000)
          #elif (GATE_F_PIN == 5)
            #define GATE_F_PIN2 (PIND & 0b00100000)
          #elif (GATE_F_PIN == 6)
            #define GATE_F_PIN2 (PIND & 0b01000000)
          #elif (GATE_F_PIN == 7)
            #define GATE_F_PIN2 (PIND & 0b10000000)
          #elif (GATE_F_PIN == 8)
            #define GATE_F_PIN2 (PINB & 0b00000001)
          #elif (GATE_F_PIN == 9)
            #define GATE_F_PIN2 (PINB & 0b00000010)
          #elif (GATE_F_PIN == 10)
            #define GATE_F_PIN2 (PINB & 0b00000100)
          #elif (GATE_F_PIN == 11)
            #define GATE_F_PIN2 (PINB & 0b00001000)
          #elif (GATE_F_PIN == 12)
            #define GATE_F_PIN2 (PINB & 0b00010000)
          #elif (GATE_F_PIN == 13)
            #define GATE_F_PIN2 (PINB & 0b00100000)
          #elif (GATE_F_PIN == 14)
            #define GATE_F_PIN2 (PINC & 0b00000001)
          #elif (GATE_F_PIN == 15)
            #define GATE_F_PIN2 (PINC & 0b00000010)
          #elif (GATE_F_PIN == 16)
            #define GATE_F_PIN2 (PINC & 0b00000100)
          #elif (GATE_F_PIN == 17)
            #define GATE_F_PIN2 (PINC & 0b00001000)
          #elif (GATE_F_PIN == 18)
            #define GATE_F_PIN2 (PINC & 0b00010000)
          #elif (GATE_F_PIN == 19)
            #define GATE_F_PIN2 (PINC & 0b00100000)
          #else
            #error "You must set Gate F to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
          #endif

          
          #ifdef ACTIVE_LOW
            #define GATE_F GATE_F_PIN2
          #else
            #define GATE_F !GATE_F_PIN2
          #endif

          #ifdef GATE_G_PIN
            #ifndef GATE_FG_SEPARATION
              #define GATE_FG_SEPARATION GATE_SEPARATION_DEFAULT
            #endif
            #if (GATE_G_PIN == 2)
              #define GATE_G_PIN2 (PIND & 0b00000100)
            #elif (GATE_G_PIN == 3)
              #define GATE_G_PIN2 (PIND & 0b00001000)
            #elif (GATE_G_PIN == 4)
              #define GATE_G_PIN2 (PIND & 0b00010000)
            #elif (GATE_G_PIN == 5)
              #define GATE_G_PIN2 (PIND & 0b00100000)
            #elif (GATE_G_PIN == 6)
              #define GATE_G_PIN2 (PIND & 0b01000000)
            #elif (GATE_G_PIN == 7)
              #define GATE_G_PIN2 (PIND & 0b10000000)
            #elif (GATE_G_PIN == 8)
              #define GATE_G_PIN2 (PINB & 0b00000001)
            #elif (GATE_G_PIN == 9)
              #define GATE_G_PIN2 (PINB & 0b00000010)
            #elif (GATE_G_PIN == 10)
              #define GATE_G_PIN2 (PINB & 0b00000100)
            #elif (GATE_G_PIN == 11)
              #define GATE_G_PIN2 (PINB & 0b00001000)
            #elif (GATE_G_PIN == 12)
              #define GATE_G_PIN2 (PINB & 0b00010000)
            #elif (GATE_G_PIN == 13)
              #define GATE_G_PIN2 (PINB & 0b00100000)
            #elif (GATE_G_PIN == 14)
              #define GATE_G_PIN2 (PINC & 0b00000001)
            #elif (GATE_G_PIN == 15)
              #define GATE_G_PIN2 (PINC & 0b00000010)
            #elif (GATE_G_PIN == 16)
              #define GATE_G_PIN2 (PINC & 0b00000100)
            #elif (GATE_G_PIN == 17)
              #define GATE_G_PIN2 (PINC & 0b00001000)
            #elif (GATE_G_PIN == 18)
              #define GATE_G_PIN2 (PINC & 0b00010000)
            #elif (GATE_G_PIN == 19)
              #define GATE_G_PIN2 (PINC & 0b00100000)
            #else
              #error "You must set Gate G to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
            #endif
  
            
            #ifdef ACTIVE_LOW
              #define GATE_G GATE_G_PIN2
            #else
              #define GATE_G !GATE_G_PIN2
            #endif

            #ifdef GATE_H_PIN
              #ifndef GATE_GH_SEPARATION
                #define GATE_GH_SEPARATION GATE_SEPARATION_DEFAULT
              #endif
              #if (GATE_H_PIN == 2)
                #define GATE_H_PIN2 (PIND & 0b00000100)
              #elif (GATE_H_PIN == 3)
                #define GATE_H_PIN2 (PIND & 0b00001000)
              #elif (GATE_H_PIN == 4)
                #define GATE_H_PIN2 (PIND & 0b00010000)
              #elif (GATE_H_PIN == 5)
                #define GATE_H_PIN2 (PIND & 0b00100000)
              #elif (GATE_H_PIN == 6)
                #define GATE_H_PIN2 (PIND & 0b01000000)
              #elif (GATE_H_PIN == 7)
                #define GATE_H_PIN2 (PIND & 0b10000000)
              #elif (GATE_H_PIN == 8)
                #define GATE_H_PIN2 (PINB & 0b00000001)
              #elif (GATE_H_PIN == 9)
                #define GATE_H_PIN2 (PINB & 0b00000010)
              #elif (GATE_H_PIN == 10)
                #define GATE_H_PIN2 (PINB & 0b00000100)
              #elif (GATE_H_PIN == 11)
                #define GATE_H_PIN2 (PINB & 0b00001000)
              #elif (GATE_H_PIN == 12)
                #define GATE_H_PIN2 (PINB & 0b00010000)
              #elif (GATE_H_PIN == 13)
                #define GATE_H_PIN2 (PINB & 0b00100000)
              #elif (GATE_H_PIN == 14)
                #define GATE_H_PIN2 (PINC & 0b00000001)
              #elif (GATE_H_PIN == 15)
                #define GATE_H_PIN2 (PINC & 0b00000010)
              #elif (GATE_H_PIN == 16)
                #define GATE_H_PIN2 (PINC & 0b00000100)
              #elif (GATE_H_PIN == 17)
                #define GATE_H_PIN2 (PINC & 0b00001000)
              #elif (GATE_H_PIN == 18)
                #define GATE_H_PIN2 (PINC & 0b00010000)
              #elif (GATE_H_PIN == 19)
                #define GATE_H_PIN2 (PINC & 0b00100000)
              #else
                #error "You must set Gate H to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
              #endif
    
              
              #ifdef ACTIVE_LOW
                #define GATE_H GATE_H_PIN2
              #else
                #define GATE_H !GATE_H_PIN2
              #endif

              #ifdef GATE_I_PIN
                #ifndef GATE_HI_SEPARATION
                  #define GATE_HI_SEPARATION GATE_SEPARATION_DEFAULT
                #endif
                #if (GATE_I_PIN == 2)
                  #define GATE_I_PIN2 (PIND & 0b00000100)
                #elif (GATE_I_PIN == 3)
                  #define GATE_I_PIN2 (PIND & 0b00001000)
                #elif (GATE_I_PIN == 4)
                  #define GATE_I_PIN2 (PIND & 0b00010000)
                #elif (GATE_I_PIN == 5)
                  #define GATE_I_PIN2 (PIND & 0b00100000)
                #elif (GATE_I_PIN == 6)
                  #define GATE_I_PIN2 (PIND & 0b01000000)
                #elif (GATE_I_PIN == 7)
                  #define GATE_I_PIN2 (PIND & 0b10000000)
                #elif (GATE_I_PIN == 8)
                  #define GATE_I_PIN2 (PINB & 0b00000001)
                #elif (GATE_I_PIN == 9)
                  #define GATE_I_PIN2 (PINB & 0b00000010)
                #elif (GATE_I_PIN == 10)
                  #define GATE_I_PIN2 (PINB & 0b00000100)
                #elif (GATE_I_PIN == 11)
                  #define GATE_I_PIN2 (PINB & 0b00001000)
                #elif (GATE_I_PIN == 12)
                  #define GATE_I_PIN2 (PINB & 0b00010000)
                #elif (GATE_I_PIN == 13)
                  #define GATE_I_PIN2 (PINB & 0b00100000)
                #elif (GATE_I_PIN == 14)
                  #define GATE_I_PIN2 (PINC & 0b00000001)
                #elif (GATE_I_PIN == 15)
                  #define GATE_I_PIN2 (PINC & 0b00000010)
                #elif (GATE_I_PIN == 16)
                  #define GATE_I_PIN2 (PINC & 0b00000100)
                #elif (GATE_I_PIN == 17)
                  #define GATE_I_PIN2 (PINC & 0b00001000)
                #elif (GATE_I_PIN == 18)
                  #define GATE_I_PIN2 (PINC & 0b00010000)
                #elif (GATE_I_PIN == 19)
                  #define GATE_I_PIN2 (PINC & 0b00100000)
                #else
                  #error "You must set Gate I to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
                #endif
                
                #ifdef ACTIVE_LOW
                  #define GATE_I GATE_I_PIN2
                #else
                  #define GATE_I !GATE_I_PIN2
                #endif

                #ifdef GATE_J_PIN
                  #ifndef GATE_IJ_SEPARATION
                    #define GATE_IJ_SEPARATION GATE_SEPARATION_DEFAULT
                  #endif
                  #if (GATE_J_PIN == 2)
                    #define GATE_J_PIN2 (PIND & 0b00000100)
                  #elif (GATE_J_PIN == 3)
                    #define GATE_J_PIN2 (PIND & 0b00001000)
                  #elif (GATE_J_PIN == 4)
                    #define GATE_J_PIN2 (PIND & 0b00010000)
                  #elif (GATE_J_PIN == 5)
                    #define GATE_J_PIN2 (PIND & 0b00100000)
                  #elif (GATE_J_PIN == 6)
                    #define GATE_J_PIN2 (PIND & 0b01000000)
                  #elif (GATE_J_PIN == 7)
                    #define GATE_J_PIN2 (PIND & 0b10000000)
                  #elif (GATE_J_PIN == 8)
                    #define GATE_J_PIN2 (PINB & 0b00000001)
                  #elif (GATE_J_PIN == 9)
                    #define GATE_J_PIN2 (PINB & 0b00000010)
                  #elif (GATE_J_PIN == 10)
                    #define GATE_J_PIN2 (PINB & 0b00000100)
                  #elif (GATE_J_PIN == 11)
                    #define GATE_J_PIN2 (PINB & 0b00001000)
                  #elif (GATE_J_PIN == 12)
                    #define GATE_J_PIN2 (PINB & 0b00010000)
                  #elif (GATE_J_PIN == 13)
                    #define GATE_J_PIN2 (PINB & 0b00100000)
                  #elif (GATE_J_PIN == 14)
                    #define GATE_J_PIN2 (PINC & 0b00000001)
                  #elif (GATE_J_PIN == 15)
                    #define GATE_J_PIN2 (PINC & 0b00000010)
                  #elif (GATE_J_PIN == 16)
                    #define GATE_J_PIN2 (PINC & 0b00000100)
                  #elif (GATE_J_PIN == 17)
                    #define GATE_J_PIN2 (PINC & 0b00001000)
                  #elif (GATE_J_PIN == 18)
                    #define GATE_J_PIN2 (PINC & 0b00010000)
                  #elif (GATE_J_PIN == 19)
                    #define GATE_J_PIN2 (PINC & 0b00100000)
                  #else
                    #error "You must set Gate J to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
                  #endif
        
                  
                  #ifdef ACTIVE_LOW
                    #define GATE_J GATE_J_PIN2
                  #else
                    #define GATE_J !GATE_J_PIN2
                  #endif

                  #ifdef GATE_K_PIN
                    #ifndef GATE_JK_SEPARATION
                      #define GATE_JK_SEPARATION GATE_SEPARATION_DEFAULT
                    #endif
                    #if (GATE_K_PIN == 2)
                      #define GATE_K_PIN2 (PIND & 0b00000100)
                    #elif (GATE_K_PIN == 3)
                      #define GATE_K_PIN2 (PIND & 0b00001000)
                    #elif (GATE_K_PIN == 4)
                      #define GATE_K_PIN2 (PIND & 0b00010000)
                    #elif (GATE_K_PIN == 5)
                      #define GATE_K_PIN2 (PIND & 0b00100000)
                    #elif (GATE_K_PIN == 6)
                      #define GATE_K_PIN2 (PIND & 0b01000000)
                    #elif (GATE_K_PIN == 7)
                      #define GATE_K_PIN2 (PIND & 0b10000000)
                    #elif (GATE_K_PIN == 8)
                      #define GATE_K_PIN2 (PINB & 0b00000001)
                    #elif (GATE_K_PIN == 9)
                      #define GATE_K_PIN2 (PINB & 0b00000010)
                    #elif (GATE_K_PIN == 10)
                      #define GATE_K_PIN2 (PINB & 0b00000100)
                    #elif (GATE_K_PIN == 11)
                      #define GATE_K_PIN2 (PINB & 0b00001000)
                    #elif (GATE_K_PIN == 12)
                      #define GATE_K_PIN2 (PINB & 0b00010000)
                    #elif (GATE_K_PIN == 13)
                      #define GATE_K_PIN2 (PINB & 0b00100000)
                    #elif (GATE_K_PIN == 14)
                      #define GATE_K_PIN2 (PINC & 0b00000001)
                    #elif (GATE_K_PIN == 15)
                      #define GATE_K_PIN2 (PINC & 0b00000010)
                    #elif (GATE_K_PIN == 16)
                      #define GATE_K_PIN2 (PINC & 0b00000100)
                    #elif (GATE_K_PIN == 17)
                      #define GATE_K_PIN2 (PINC & 0b00001000)
                    #elif (GATE_K_PIN == 18)
                      #define GATE_K_PIN2 (PINC & 0b00010000)
                    #elif (GATE_K_PIN == 19)
                      #define GATE_K_PIN2 (PINC & 0b00100000)
                    #else
                      #error "You must set Gate K to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
                    #endif
          
                    #ifdef ACTIVE_LOW
                      #define GATE_K GATE_K_PIN2
                    #else
                      #define GATE_K !GATE_K_PIN2
                    #endif
                    
                    #ifdef GATE_L_PIN
                      #ifndef GATE_KL_SEPARATION
                        #define GATE_KL_SEPARATION GATE_SEPARATION_DEFAULT
                      #endif
                      #if (GATE_L_PIN == 2)
                        #define GATE_L_PIN2 (PIND & 0b00000100)
                      #elif (GATE_L_PIN == 3)
                        #define GATE_L_PIN2 (PIND & 0b00001000)
                      #elif (GATE_L_PIN == 4)
                        #define GATE_L_PIN2 (PIND & 0b00010000)
                      #elif (GATE_L_PIN == 5)
                        #define GATE_L_PIN2 (PIND & 0b00100000)
                      #elif (GATE_L_PIN == 6)
                        #define GATE_L_PIN2 (PIND & 0b01000000)
                      #elif (GATE_L_PIN == 7)
                        #define GATE_L_PIN2 (PIND & 0b10000000)
                      #elif (GATE_L_PIN == 8)
                        #define GATE_L_PIN2 (PINB & 0b00000001)
                      #elif (GATE_L_PIN == 9)
                        #define GATE_L_PIN2 (PINB & 0b00000010)
                      #elif (GATE_L_PIN == 10)
                        #define GATE_L_PIN2 (PINB & 0b00000100)
                      #elif (GATE_L_PIN == 11)
                        #define GATE_L_PIN2 (PINB & 0b00001000)
                      #elif (GATE_L_PIN == 12)
                        #define GATE_L_PIN2 (PINB & 0b00010000)
                      #elif (GATE_L_PIN == 13)
                        #define GATE_L_PIN2 (PINB & 0b00100000)
                      #elif (GATE_L_PIN == 14)
                        #define GATE_L_PIN2 (PINC & 0b00000001)
                      #elif (GATE_L_PIN == 15)
                        #define GATE_L_PIN2 (PINC & 0b00000010)
                      #elif (GATE_L_PIN == 16)
                        #define GATE_L_PIN2 (PINC & 0b00000100)
                      #elif (GATE_L_PIN == 17)
                        #define GATE_L_PIN2 (PINC & 0b00001000)
                      #elif (GATE_L_PIN == 18)
                        #define GATE_L_PIN2 (PINC & 0b00010000)
                      #elif (GATE_L_PIN == 19)
                        #define GATE_L_PIN2 (PINC & 0b00100000)
                      #else
                        #error "You must set Gate L to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
                      #endif
            
                      #ifdef ACTIVE_LOW
                        #define GATE_L GATE_L_PIN2
                      #else
                        #define GATE_L !GATE_L_PIN2
                      #endif

                      #ifdef GATE_M_PIN
                        #ifndef GATE_LM_SEPARATION
                          #define GATE_LM_SEPARATION GATE_SEPARATION_DEFAULT
                        #endif
                        #if (GATE_M_PIN == 2)
                          #define GATE_M_PIN2 (PIND & 0b00000100)
                        #elif (GATE_M_PIN == 3)
                          #define GATE_M_PIN2 (PIND & 0b00001000)
                        #elif (GATE_M_PIN == 4)
                          #define GATE_M_PIN2 (PIND & 0b00010000)
                        #elif (GATE_M_PIN == 5)
                          #define GATE_M_PIN2 (PIND & 0b00100000)
                        #elif (GATE_M_PIN == 6)
                          #define GATE_M_PIN2 (PIND & 0b01000000)
                        #elif (GATE_M_PIN == 7)
                          #define GATE_M_PIN2 (PIND & 0b10000000)
                        #elif (GATE_M_PIN == 8)
                          #define GATE_M_PIN2 (PINB & 0b00000001)
                        #elif (GATE_M_PIN == 9)
                          #define GATE_M_PIN2 (PINB & 0b00000010)
                        #elif (GATE_M_PIN == 10)
                          #define GATE_M_PIN2 (PINB & 0b00000100)
                        #elif (GATE_M_PIN == 11)
                          #define GATE_M_PIN2 (PINB & 0b00001000)
                        #elif (GATE_M_PIN == 12)
                          #define GATE_M_PIN2 (PINB & 0b00010000)
                        #elif (GATE_M_PIN == 13)
                          #define GATE_M_PIN2 (PINB & 0b00100000)
                        #elif (GATE_M_PIN == 14)
                          #define GATE_M_PIN2 (PINC & 0b00000001)
                        #elif (GATE_M_PIN == 15)
                          #define GATE_M_PIN2 (PINC & 0b00000010)
                        #elif (GATE_M_PIN == 16)
                          #define GATE_M_PIN2 (PINC & 0b00000100)
                        #elif (GATE_M_PIN == 17)
                          #define GATE_M_PIN2 (PINC & 0b00001000)
                        #elif (GATE_M_PIN == 18)
                          #define GATE_M_PIN2 (PINC & 0b00010000)
                        #elif (GATE_M_PIN == 19)
                          #define GATE_M_PIN2 (PINC & 0b00100000)
                        #else
                          #error "You must set Gate M to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
                        #endif
              
                        #ifdef ACTIVE_LOW
                          #define GATE_M GATE_M_PIN2
                        #else
                          #define GATE_M !GATE_M_PIN2
                        #endif

                        #ifdef GATE_N_PIN
                          #ifndef GATE_MN_SEPARATION
                            #define GATE_MN_SEPARATION GATE_SEPARATION_DEFAULT
                          #endif
                          #if (GATE_N_PIN == 2)
                            #define GATE_N_PIN2 (PIND & 0b00000100)
                          #elif (GATE_N_PIN == 3)
                            #define GATE_N_PIN2 (PIND & 0b00001000)
                          #elif (GATE_N_PIN == 4)
                            #define GATE_N_PIN2 (PIND & 0b00010000)
                          #elif (GATE_N_PIN == 5)
                            #define GATE_N_PIN2 (PIND & 0b00100000)
                          #elif (GATE_N_PIN == 6)
                            #define GATE_N_PIN2 (PIND & 0b01000000)
                          #elif (GATE_N_PIN == 7)
                            #define GATE_N_PIN2 (PIND & 0b10000000)
                          #elif (GATE_N_PIN == 8)
                            #define GATE_N_PIN2 (PINB & 0b00000001)
                          #elif (GATE_N_PIN == 9)
                            #define GATE_N_PIN2 (PINB & 0b00000010)
                          #elif (GATE_N_PIN == 10)
                            #define GATE_N_PIN2 (PINB & 0b00000100)
                          #elif (GATE_N_PIN == 11)
                            #define GATE_N_PIN2 (PINB & 0b00001000)
                          #elif (GATE_N_PIN == 12)
                            #define GATE_N_PIN2 (PINB & 0b00010000)
                          #elif (GATE_N_PIN == 13)
                            #define GATE_N_PIN2 (PINB & 0b00100000)
                          #elif (GATE_N_PIN == 14)
                            #define GATE_N_PIN2 (PINC & 0b00000001)
                          #elif (GATE_N_PIN == 15)
                            #define GATE_N_PIN2 (PINC & 0b00000010)
                          #elif (GATE_N_PIN == 16)
                            #define GATE_N_PIN2 (PINC & 0b00000100)
                          #elif (GATE_N_PIN == 17)
                            #define GATE_N_PIN2 (PINC & 0b00001000)
                          #elif (GATE_N_PIN == 18)
                            #define GATE_N_PIN2 (PINC & 0b00010000)
                          #elif (GATE_N_PIN == 19)
                            #define GATE_N_PIN2 (PINC & 0b00100000)
                          #else
                            #error "You must set Gate N to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
                          #endif
                
                          #ifdef ACTIVE_LOW
                            #define GATE_N GATE_N_PIN2
                          #else
                            #define GATE_N !GATE_N_PIN2
                          #endif

                          #ifdef GATE_O_PIN
                            #ifndef GATE_NO_SEPARATION
                              #define GATE_NO_SEPARATION GATE_SEPARATION_DEFAULT
                            #endif
                            #if (GATE_O_PIN == 2)
                              #define GATE_O_PIN2 (PIND & 0b00000100)
                            #elif (GATE_O_PIN == 3)
                              #define GATE_O_PIN2 (PIND & 0b00001000)
                            #elif (GATE_O_PIN == 4)
                              #define GATE_O_PIN2 (PIND & 0b00010000)
                            #elif (GATE_O_PIN == 5)
                              #define GATE_O_PIN2 (PIND & 0b00100000)
                            #elif (GATE_O_PIN == 6)
                              #define GATE_O_PIN2 (PIND & 0b01000000)
                            #elif (GATE_O_PIN == 7)
                              #define GATE_O_PIN2 (PIND & 0b10000000)
                            #elif (GATE_O_PIN == 8)
                              #define GATE_O_PIN2 (PINB & 0b00000001)
                            #elif (GATE_O_PIN == 9)
                              #define GATE_O_PIN2 (PINB & 0b00000010)
                            #elif (GATE_O_PIN == 10)
                              #define GATE_O_PIN2 (PINB & 0b00000100)
                            #elif (GATE_O_PIN == 11)
                              #define GATE_O_PIN2 (PINB & 0b00001000)
                            #elif (GATE_O_PIN == 12)
                              #define GATE_O_PIN2 (PINB & 0b00010000)
                            #elif (GATE_O_PIN == 13)
                              #define GATE_O_PIN2 (PINB & 0b00100000)
                            #elif (GATE_O_PIN == 14)
                              #define GATE_O_PIN2 (PINC & 0b00000001)
                            #elif (GATE_O_PIN == 15)
                              #define GATE_O_PIN2 (PINC & 0b00000010)
                            #elif (GATE_O_PIN == 16)
                              #define GATE_O_PIN2 (PINC & 0b00000100)
                            #elif (GATE_O_PIN == 17)
                              #define GATE_O_PIN2 (PINC & 0b00001000)
                            #elif (GATE_O_PIN == 18)
                              #define GATE_O_PIN2 (PINC & 0b00010000)
                            #elif (GATE_O_PIN == 19)
                              #define GATE_O_PIN2 (PINC & 0b00100000)
                            #else
                              #error "You must set Gate O to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
                            #endif
                  
                            #ifdef ACTIVE_LOW
                              #define GATE_O GATE_O_PIN2
                            #else
                              #define GATE_O !GATE_O_PIN2
                            #endif
                            
                            #ifdef GATE_P_PIN
                              #ifndef GATE_OP_SEPARATION
                                #define GATE_OP_SEPARATION GATE_SEPARATION_DEFAULT
                              #endif
                              #if (GATE_P_PIN == 2)
                                #define GATE_P_PIN2 (PIND & 0b00000100)
                              #elif (GATE_P_PIN == 3)
                                #define GATE_P_PIN2 (PIND & 0b00001000)
                              #elif (GATE_P_PIN == 4)
                                #define GATE_P_PIN2 (PIND & 0b00010000)
                              #elif (GATE_P_PIN == 5)
                                #define GATE_P_PIN2 (PIND & 0b00100000)
                              #elif (GATE_P_PIN == 6)
                                #define GATE_P_PIN2 (PIND & 0b01000000)
                              #elif (GATE_P_PIN == 7)
                                #define GATE_P_PIN2 (PIND & 0b10000000)
                              #elif (GATE_P_PIN == 8)
                                #define GATE_P_PIN2 (PINB & 0b00000001)
                              #elif (GATE_P_PIN == 9)
                                #define GATE_P_PIN2 (PINB & 0b00000010)
                              #elif (GATE_P_PIN == 10)
                                #define GATE_P_PIN2 (PINB & 0b00000100)
                              #elif (GATE_P_PIN == 11)
                                #define GATE_P_PIN2 (PINB & 0b00001000)
                              #elif (GATE_P_PIN == 12)
                                #define GATE_P_PIN2 (PINB & 0b00010000)
                              #elif (GATE_P_PIN == 13)
                                #define GATE_P_PIN2 (PINB & 0b00100000)
                              #elif (GATE_P_PIN == 14)
                                #define GATE_P_PIN2 (PINC & 0b00000001)
                              #elif (GATE_P_PIN == 15)
                                #define GATE_P_PIN2 (PINC & 0b00000010)
                              #elif (GATE_P_PIN == 16)
                                #define GATE_P_PIN2 (PINC & 0b00000100)
                              #elif (GATE_P_PIN == 17)
                                #define GATE_P_PIN2 (PINC & 0b00001000)
                              #elif (GATE_P_PIN == 18)
                                #define GATE_P_PIN2 (PINC & 0b00010000)
                              #elif (GATE_P_PIN == 19)
                                #define GATE_P_PIN2 (PINC & 0b00100000)
                              #else
                                #error "You must set Gate P to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
                              #endif
                    
                              #ifdef ACTIVE_LOW
                                #define GATE_P GATE_P_PIN2
                              #else
                                #define GATE_P !GATE_P_PIN2
                              #endif
                    
                              #define GATE_COUNT 16
                              #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION, GATE_GH_SEPARATION, GATE_HI_SEPARATION, GATE_IJ_SEPARATION, GATE_JK_SEPARATION, GATE_KL_SEPARATION, GATE_LM_SEPARATION, GATE_MN_SEPARATION, GATE_NO_SEPARATION, GATE_OP_SEPARATION}
                              
                            #endif
                            
                            #ifndef GATE_COUNT
                              #define GATE_COUNT 15
                              #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION, GATE_GH_SEPARATION, GATE_HI_SEPARATION, GATE_IJ_SEPARATION, GATE_JK_SEPARATION, GATE_KL_SEPARATION, GATE_LM_SEPARATION, GATE_MN_SEPARATION, GATE_NO_SEPARATION}
                            #endif
                          
                          #endif
                        
                          #ifndef GATE_COUNT
                            #define GATE_COUNT 14
                            #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION, GATE_GH_SEPARATION, GATE_HI_SEPARATION, GATE_IJ_SEPARATION, GATE_JK_SEPARATION, GATE_KL_SEPARATION, GATE_LM_SEPARATION, GATE_MN_SEPARATION}
                          #endif
                        
                        #endif
              
                        #ifndef GATE_COUNT
                          #define GATE_COUNT 13
                          #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION, GATE_GH_SEPARATION, GATE_HI_SEPARATION, GATE_IJ_SEPARATION, GATE_JK_SEPARATION, GATE_KL_SEPARATION, GATE_LM_SEPARATION}
                        #endif
                      
                      #endif
                      
                      #ifndef GATE_COUNT
                        #define GATE_COUNT 12
                        #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION, GATE_GH_SEPARATION, GATE_HI_SEPARATION, GATE_IJ_SEPARATION, GATE_JK_SEPARATION, GATE_KL_SEPARATION}
                      #endif
                      
                    #endif
          
                    #ifndef GATE_COUNT
                      #define GATE_COUNT 11
                      #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION, GATE_GH_SEPARATION, GATE_HI_SEPARATION, GATE_IJ_SEPARATION, GATE_JK_SEPARATION}
                    #endif
                    
                  #endif
        
                  #ifndef GATE_COUNT
                    #define GATE_COUNT 10
                    #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION, GATE_GH_SEPARATION, GATE_HI_SEPARATION, GATE_IJ_SEPARATION}
                  #endif
                  
                #endif
              
                #ifndef GATE_COUNT
                  #define GATE_COUNT 9
                  #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION, GATE_GH_SEPARATION, GATE_HI_SEPARATION}
                #endif
                
              #endif
    
              #ifndef GATE_COUNT
                #define GATE_COUNT 8
                #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION, GATE_GH_SEPARATION}
              #endif
              
            #endif
  
            #ifndef GATE_COUNT
              #define GATE_COUNT 7
              #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION, GATE_FG_SEPARATION}
            #endif
            
          #endif
          
          #ifndef GATE_COUNT
            #define GATE_COUNT 6
            #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION, GATE_EF_SEPARATION}
          #endif
        #endif

        #ifndef GATE_COUNT
          #define GATE_COUNT 5
          #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION, GATE_DE_SEPARATION}
        #endif
      #endif

      #ifndef GATE_COUNT
        #define GATE_COUNT 4
        #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION, GATE_BC_SEPARATION, GATE_CD_SEPARATION}
      #endif
    #endif

    #ifndef GATE_COUNT
      #define GATE_COUNT 3
      #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION}
    #endif
  #endif

  #ifndef GATE_COUNT
    #define GATE_COUNT 2
    #define GATE_SEPARATION_ARRAY {GATE_AB_SEPARATION}
  #endif


  
  #if (MAX_TRANSIT_TIME == 16)
    #define WDT_ON 0b01001000
  #elif (MAX_TRANSIT_TIME == 32)
    #define WDT_ON 0b01001001
  #elif (MAX_TRANSIT_TIME == 64)
    #define WDT_ON 0b01001010
  #elif (MAX_TRANSIT_TIME == 125)
    #define WDT_ON 0b01001011
  #elif (MAX_TRANSIT_TIME == 250)
    #define WDT_ON 0b01001100
  #elif (MAX_TRANSIT_TIME == 500)
    #define WDT_ON 0b01001101
  #elif (MAX_TRANSIT_TIME == 1000)
    #define WDT_ON 0b01001110
  #elif (MAX_TRANSIT_TIME == 2000)
    #define WDT_ON 0b01001111
  #elif (MAX_TRANSIT_TIME == 4000)
    #define WDT_ON 0b01101000
  #elif (MAX_TRANSIT_TIME == 8000)
    #define WDT_ON 0b01101001
  #else
    #error "you need to set MAX_TRANSIT_TIME correctly"
  #endif

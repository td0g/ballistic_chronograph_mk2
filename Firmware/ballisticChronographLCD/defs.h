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
  #elif (GATE_B_PIN == 14)
    #define GATE_B_PIN2 (PINC & 0b00000001)
  #elif (GATE_B_PIN == 15)
    #define GATE_B_PIN2 (PINC & 0b00000010)
  #elif (GATE_B_PIN == 16)
    #define GATE_B_PIN2 (PINC & 0b00000100)
  #elif (GATE_B_PIN == 17)
    #define GATE_B_PIN2 (PINC & 0b00001000)
  #elif (GATE_B_PIN == 18)
    #define GATE_B_PIN2 (PINC & 0b00010000)
  #elif (GATE_B_PIN == 19)
    #define GATE_B_PIN2 (PINC & 0b00100000)
  #else
    #error "You must set Gate B to a valid pin!  Use 14 for A0, 15 for A1, and so on..."
  #endif

  #ifdef ACTIVE_LOW
    #define GATE_B GATE_B_PIN2
  #else
    #define GATE_B !GATE_B_PIN2
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

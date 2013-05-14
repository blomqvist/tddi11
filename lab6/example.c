/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2,1 --- 5/8/2011 15:9:5 PST

Modifications:
- Add void as return value from functions.
- return 0 from main

*/

#include "rims.h"

/*Global C code is defined at global scope in generated code*/

byte BLINK_Clk;
void TimerISR() {
   BLINK_Clk = 1;
}

enum BLINK_States { BLINK_OFF, BLINK_BLINK } BLINK_State;

void BLINK_Tick() {
   switch(BLINK_State) { // Transitions
         case BLINK_OFF:
         if (A > 5) {
            BLINK_State = BLINK_BLINK;
         }
         break;
      case BLINK_BLINK:
         if (A <= 5) {
            BLINK_State = BLINK_OFF;
         }
         break;
      default:
         BLINK_State = BLINK_OFF;
   } // Transitions

   switch(BLINK_State) { // State actions
      case BLINK_OFF:
         B = 0;
         break;
      case BLINK_BLINK:
         B = !B;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions
}

int main()
{
  const unsigned int BLINK_Period = 300;
  TimerSet(BLINK_Period);
  TimerOn();
  
  BLINK_State = -1; // Initial state
  B = 0; // Init outputs
  
  while(1)
  {
    BLINK_Tick();
    while(!BLINK_Clk)
      ;
    BLINK_Clk = 0;
  } // while (1)
  return 0;
} // Main

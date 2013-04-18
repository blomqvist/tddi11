#include "rims.h"

void HotelSafe();
void Safe();

volatile int timer_period_elapsed;
volatile int keyboard_event;
volatile int code;

void KeyboardISR()
{
  /* Your code here */
  Safe();
}

void TimerISR()
{
  /* Your code here */
}

int main()
{   
   B = 1; // Init outputs

   while(1)
   {

     /* Your code here */
     
   } // while (1)

   return 0;
} // Main

void HotelSafe()
{
  /* Your code here */  
}

/* Draw state machine of below implementation */
void Safe()
{
  static enum { LOCK, PIN1, PIN2, PIN3, PINX, OPEN } state = LOCK;
  const char* debug[] = {
    "LOCK", "PIN1", "PIN2", "PIN3", "PINX", "OPEN", 0
  };
  static byte pin1 = 1, pin2 = 1, pin3 = 1, pin4 = 1;
  static byte count = 0;

  printf("Entry State = %s, A = %d\n", debug[state], A);
  
  /* Transitions */
  switch( state )
  {
    case LOCK: if ( A == pin1 ) state = PIN1; break;
    case PIN1: if ( A == pin2 ) state = PIN2; break;
    case PIN2: if ( A == pin3 ) state = PIN3; break;
    case PIN3: if ( A == pin4 ) state = PINX; break;
    case PINX: if ( count == 4 ) state = OPEN; break;
    case OPEN: if ( A == 11 ) state = LOCK; break;
  }

  /* Actions */
  switch( state )
  {
    case LOCK: B = 1; pin1 = 1, pin2 = 1, pin3 = 1, pin4 = 1; break;
    case PIN1: B = 0; pin2 += 1; break;
    case PIN2: B = 0; pin3 += 2; break;
    case PIN3: B = 0; pin4 += 3; count = 0; break;
    case PINX: B = 0; ++count; break;
    case OPEN: B = 2; break;
  }
  
  printf("Exit State = %s\n", debug[state]);
}

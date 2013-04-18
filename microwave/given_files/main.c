#include "given_files/rims.h"

volatile int timer_period_elapsed;

static bool time_set = false;
static int clock;

void Set_Time();
void Heat();

  
void TimerISR()
{
   timer_period_elapsed = 1;
}

void set_display(int value)
{
  /* Your code here */
}

void seconds_to_display(int seconds)
{
  set_display( 0 /* Your code here */ );
}

int main()
{
   TimerSet(200);
   TimerOn();
   
   B = 0; // Init outputs

   byte count = 0;

   while(1)
   {
     while ( ! timer_period_elapsed )
       ;
     timer_period_elapsed = 0;
     
     B = count;
     count = (count + 1);
   
   } // while (1)

   return 0;
} // Main


// input definitions for the state machine(s)
#define INC_PRESSED (A & 0x01)
#define DEC_PRESSED (A & 0x02)
#define START_PRESSED /* Your code here */
#define DOOR_OPEN /* Your code here */
#define DOOR_CLOSED /* Your code here */


void Heat()
{
  /* Your code here */
}


// Set_Time updates the following two global variables:
//  bool time_set;
//  int clock;
// 200ms period
void Set_Time()
{
  static enum {INIT,INC_10S, INC_20S, INC_1M} state = INIT;
  static int press_count;

  // Transitions
  switch (state)
  {
    case INIT:
      press_count = 0;
      state = INC_10S;
      clock = 0;
      break;
      
    case INC_10S:
      if ( INC_PRESSED )
      {
        clock += 10;
        ++press_count;
      }
      else if ( DEC_PRESSED )
      {
        clock /= 2;
        press_count = 0;
      }
      if (press_count >= 6)
      {
        press_count = 0;
        state = INC_20S;
      }
      break;
      
    case INC_20S:
      if ( INC_PRESSED )
      {
        clock += 20;
        ++press_count;
      }
      else if ( DEC_PRESSED )
      {
        clock /= 2;
        press_count = 0;
        state = INC_10S;
      }
      if (press_count >= 6)
      {
        press_count = 0;
        state = INC_1M;
      }
      break;
      
    case INC_1M:
      if ( INC_PRESSED )
      {
        clock += 60;
        state = INC_1M;
      }
      else if ( DEC_PRESSED )
      {
        clock /= 2;
        press_count = 0;
        state = INC_10S;
      }
      break;
  }

  // Action for the state just set
  switch (state)
  {
    case INIT:
      // just to disable compiler warning
      break;
      
    case INC_10S:
      // if clock equals 0 time is not set
      time_set = (clock != 0);
      break;
      
    case INC_20S:
      time_set = (clock != 0);
      break;
      
    case INC_1M:
      time_set = (clock != 0);
      break;
  }
  // Note: Above switch happen to set the output in same way in all
  //       states. This can of course be optimized by simply removing
  //       the entire switch and just set the output. But it also
  //       serves as an example for how the action part of the
  //       state-machine looks, that's why it is included.

  // max clock allowed
  if (clock > 99*60+59)
    clock = 99*60+59;
}

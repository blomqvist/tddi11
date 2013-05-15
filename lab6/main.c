#include "rims.h"

byte T_FLAG;

void TimerISR() {
  T_FLAG = 1;
}

enum BLINK_STATES { OFF, BLINK, ON } blink_state;
enum MOTION_STATES { SLEEP, DATA, ROAD, COUNTER } motion_state;
bool lamp_state = false;
bool did_read = false; // indicates if a value was previously fjslkadjsa
unsigned int counter;

void button_press()
{
  byte A_READ = A & 128;
  if (A_READ)
    blink_state == ON ? blink_state = OFF : blink_state++;
}

void enable()
{
 
  byte A_READ = A & 127; // MASK OUT THAT SHIT HEHE

  switch(motion_state) 
    {
    case SLEEP:
      B = 0; // TURN ALL THE LIGHTS OFF
      if (A_READ > 3)
	++motion_state; // GO TO DATA
      break;
    case DATA:
      if (A_READ > 3)
	++motion_state; // ON THE ROAD, AGAIN
      else
	motion_state = SLEEP; // We'll tuck you right back in... Sleep tight, hun.
      break;
    case ROAD:
      B = (lamp_state) ? 255 : 0; // Check if LEDs should be on or off
      if (A_READ > 3) {
	counter = 100; // counter reset
	break;
      }
    case COUNTER:
      if (--counter == 0) {
	motion_state = SLEEP; // GO BACK TO SLEEP YOU FOOL :-)
      }
      break;
    }
}

void toggle()
{
  switch (blink_state) {
    case OFF:
      button_press();
      lamp_state = false;
      counter = 0; // Always off
      // Nothing else to be done here - lamp's off
      break;
    case BLINK:
      button_press();
      lamp_state = !lamp_state; // Toggle LEDs
      break;
    case ON:
      button_press();
      lamp_state = true; // LEDs always ON
      break;
    default:
      blink_state = OFF;
      counter = 0;
      break;
  }
  
  enable();
}

int main()
{
  // Set interrupt timer and enable
  TimerSet(100);
  TimerOn();

  B = 0;
  blink_state = OFF;
  motion_state = SLEEP;
  counter = 0;
  T_FLAG = 0;
  
  for (;;)
  {
    toggle();
    while (!T_FLAG)
      ;
    T_FLAG = 0;
  }

  return 0;
}


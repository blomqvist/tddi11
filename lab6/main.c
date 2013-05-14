#include "rims.h"

byte T_FLAG;

void TimerISR() {
  T_FLAG = 1;
}

enum BLINK_STATES { OFF, BLINK, ON } blink_state;
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
  if (!blink_state) {
    B = 0;
    return;
  }
  
  byte A_READ = A & 127;
  if (A_READ > 3)
  {
    if (did_read)
    {
      if (lamp_state)
	B = 255;
      else
	B = 0;
      counter = 100;
    }
    did_read = true;
  }
  else
  {
    if (counter) --counter;
    if (!counter)
    {
      did_read = false;
      B = 0;
    }
    else // counter > 0
    {
      if (lamp_state)
	B = 255;
      else
	B = 0;
    }
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


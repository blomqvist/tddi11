#include <dos.h>
#include <libepc.h>

#include "serial.h"

/* Function prototypes */
void InitOutBound(void) ;
void InitInBound(void) ;
void InitSerial(void) ;

void OutBound(void) ;
void InBound(void) ;

QUEUE *inbound_queue ;

int main()
{
  inbound_queue = QueueCreate(sizeof(char), 20) ;
  
  ClearScreen(0x07) ;
  SetCursorVisible(TRUE) ;
  InitSerial() ;
  
  InitOutBound() ;
  InitInBound() ;
  
  for (;;)
  {
    OutBound() ;
    InBound() ;
  }
  
  return 0 ;
}

void InitSerial(void)
{
  /* Disable interrupts during initialization */
  disable() ;
  
  /* 9600 baud */
  outportb(SER_LCR, SER_LCR_DLAB) ;
  outportb(SER_DLO, 12) ;
  outportb(SER_DHI, 0) ;
  
  /* 8 data bits, even parity, 1 stop bit */
  outportb(SER_LCR, 0x1B) ;
  
  /* Enable only receiver data ready interrupts */
  outportb(SER_IER, 0x01) ;
  
  /* Request to send, data terminal ready, enable interrupts */
  outportb(SER_MCR, SER_MCR_RTS|SER_MCR_DTR|SER_MCR_OUT2) ;

  /* Store address of ISR in IDT */
  SetISR(IRQ2INT(SER_IRQ), SerialISR) ;
  
  /* Unmask the UART's IRQ line */
  outportb(0x21, inportb(0x21) & ~SER_MSK) ;
  
  /* Re-enable interrupts */
  enable() ;
}

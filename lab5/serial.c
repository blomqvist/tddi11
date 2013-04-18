#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>
#include <dos.h>
#include <pc.h>

#include "serial.h"

void OSSerialISR(void) ;

OS_EVENT *com1_queue = NULL ;

BYTE8 SerialGet(void)
{
  char err ;
  return ((unsigned) OSQPend(com1_queue, 0, &err)) & 0xFF ;
}

void SerialPut(char ch)
{
  /* This function uses programmed waiting loop I/O	*/
  /* to output the ASCII character 'ch' to the UART.	*/
  
  while ((inportb(SER_LSR) & SER_LSR_THRE) == 0)
  {
    OSTimeDly(1) ;
  }
  
  outportb(SER_THR, ch) ;
}

void SerialInit(void)
{
  static void *com1_q[20] ;
  
  if (com1_queue)
    return ;
  
  com1_queue = OSQCreate(com1_q, ENTRIES(com1_q)) ;
  
  disable() ;
  
  outportb(SER_IER, 0x00) ;
  
  /* Setup for 38400 baud */
  outportb(SER_LCR, SER_LCR_DLAB) ;
  outportb(SER_DLO, 3) ;
  outportb(SER_DHI, 0) ;
  
  /* 8 data bits, no parity, 1 stop bit */
  outportb(SER_LCR, 0x03) ;
  
  /* Set FIFO to trigger at 14 */
  outportb(SER_FCR, 0xC7) ;
  
  /* Request to send, data terminal ready, enable interrupts */
  outportb(SER_MCR, SER_MCR_RTS|SER_MCR_DTR|SER_MCR_OUT2) ;
  
  /* Enable only receiver data ready interrupts */
  outportb(SER_IER, 0x01) ;
  
  SetISR(IRQ2INT(IRQ_COM1_COM3), OSSerialISR) ;
  outportb(0x21, inportb(0x21) & ~SER_MSK) ;
  
  enable() ;
}

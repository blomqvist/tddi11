#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>
#include <dos.h>

#include "inbound.h"
#include "elapsed.h"
#include "packet.h"

#define	STACK_SIZE	1000

extern void OutboundThread() ;

PRIVATE OS_STK *CreateStack(void)
{
  OS_STK *top = (OS_STK *) malloc(STACK_SIZE) + STACK_SIZE ;
  
  if (!top)
  {
    for (;;)
      ;
  }
  return top ;
}

int main()
{
  ClearScreen(0x07) ;
  SetCursorVisible(TRUE) ;
  
  OSInit() ;
  OSTaskCreate(ReceivePackets,	NULL, CreateStack(), 0);
  OSTaskCreate(InboundTime,	    NULL, CreateStack(), 1);
  OSTaskCreate(InboundText,	    NULL, CreateStack(), 2);
  OSTaskCreate(OutboundThread,	NULL, CreateStack(), 3);
  OSTaskCreate(ElapsedLocal,	  NULL, CreateStack(), 4);
  OSTaskCreate(InboundRecieved, NULL, CreateStack(), 5);
  OSStart() ;

  return 0 ;
}

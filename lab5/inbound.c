#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>

#include "packet.h"

PRIVATE OS_EVENT *display_queue = NULL ;

PRIVATE void InboundCreateQ(void)
{
  if (!display_queue)
  {
    static void *display_q[20] ;
    display_queue = OSQCreate(display_q, ENTRIES(display_q)) ;
  }
}

void PostText(BYTE8 *bfr)
{
  InboundCreateQ() ;
  OSQPost(display_queue, bfr) ;
}

void InboundText(void)
{
  WINDOW *remote ;
  
  remote = WindowCreate("Remote", 14, 24, 0, 79) ;
  InboundCreateQ() ;
  
  for (;;)
  {
    char *bfr ;
    BYTE8 err ;
    
    bfr = OSQPend(display_queue, 0, &err) ;
    WindowPutChar(remote, *bfr) ;
    free(bfr) ;
  }
}


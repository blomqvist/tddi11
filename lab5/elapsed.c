#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>

#include "elapsed.h"
#include "packet.h"

PRIVATE char *AsciiTime(TIME *elapsed) ;
PRIVATE void UpdateTime(TIME *elapsed) ;

PRIVATE OS_EVENT *time_queue = NULL ;

PRIVATE void TimeCreateQ(void)
{
  static void *time_q[20] ;
  
  if (!time_queue)
  {
    time_queue = OSQCreate(time_q, ENTRIES(time_q)) ;
  }
}

void PostTime(BYTE8 *bfr)
{
  TimeCreateQ() ;
  OSQPost(time_queue, bfr) ;
}

void InboundTime(void)
{
  WINDOW *w ;
  
  w = (WINDOW *) WindowCreate("Remote", 11, 13, 56, 72) ;
  if (!w)
    return ;
  TimeCreateQ() ;
  
  for (;;)
  {
    BYTE8 err ;
    char *bfr ;
    
    bfr = OSQPend(time_queue, 0, &err) ;
    WindowSetCursor(w, 0, 1) ;
    WindowPutString(w, bfr) ;
    free(bfr) ;
  }
}

void ElapsedLocal(void)
{
  WINDOW *w ;
  
  w = (WINDOW *) WindowCreate("Local", 11, 13, 10, 23) ;
  if (!w)
    return ;

  /* SerialInit have a guard inside to prevent multiple initializations */
  SerialInit();
  
  for (;;)
  {
    static TIME elapsed = {0, 0, 0, 0} ;
    char *bfr ;
    
    /* Update the display */
    WindowSetCursor(w, 0, 1) ;
    bfr = AsciiTime(&elapsed) ;
    SendPacket(2, bfr, 11) ;
    WindowPutString(w, bfr) ;
    
    OSTimeDly(100) ; /* Sleep for about .1 second */
    
    /* update elapsed hours, minutes, and seconds */
    UpdateTime(&elapsed) ;
  }
}

PRIVATE void UpdateTime(TIME *elapsed)
{
  int ticks = OSTimeGet() ;
  
  elapsed->tenths = ticks / 100 ;
  elapsed->secs = elapsed->tenths / 10 ;
  elapsed->tenths %= 10 ;
  elapsed->mins = elapsed->secs / 60 ;
  elapsed->secs %= 60 ;
  elapsed->hours = elapsed->mins / 60 ;
  elapsed->mins %= 60 ;
}

PRIVATE char *AsciiTime(TIME *elapsed)
{
  static char _bfr[] = "XX:XX:XX.X" ;
  char *bfr ;
  
  bfr = FormatUnsigned(_bfr, elapsed->hours, 10, 2, '0') ;
  *bfr++ = ':' ;
  bfr = FormatUnsigned(bfr, elapsed->mins,  10, 2, '0') ;
  *bfr++ = ':' ;
  bfr = FormatUnsigned(bfr, elapsed->secs,  10, 2, '0') ;
  *bfr++ = '.' ;
  FormatUnsigned(bfr, elapsed->tenths, 10, 1, '0') ;
  return _bfr ;
}

#include <libepc.h>

#include "serial.h"

PRIVATE WINDOW *w ;

void InitInBound(void)
{
  w = WindowCreate("Remote", 13, 24, 0, 79) ;
}

void InBound(void)
{
  extern QUEUE *inbound_queue ;
  char ascii ;
  
  if (QueueRemove(inbound_queue, &ascii))
  {
    WindowPutChar(w, ascii) ;
  }
}

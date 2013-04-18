#include <libepc.h>
#include <mtc.h>

#include "serial.h"

void InBound(void)
{
  extern QUEUE *inbound_queue ;
  WINDOW *w ;
  
  w = WindowCreate("Remote", 11, 21, 0, 79) ;
  
  if (!w)
    return ;
  
  for (;;)
  {
    char ascii ;
    
    while (!QueueRemove(inbound_queue, &ascii))
      MtCYield() ;
    WindowPutChar(w, ascii) ;
  }
}

#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>

#include "inbound.h"
#include "elapsed.h"
#include "serial.h"

static OS_EVENT* oe = NULL;

static OS_EVENT *recieved_queue = NULL ;

PRIVATE void RecievedCreateQ(void)
{
  if (!recieved_queue)
  {
    static void *recieved_q[20] ;
    recieved_queue = OSQCreate(recieved_q, ENTRIES(recieved_q)) ;
  }
}


void PostRecieved(BYTE8 *bfr)
{
  RecievedCreateQ() ;
  OSQPost(recieved_queue, bfr) ;
}

void SendPacket(int type, BYTE8* bfr, int bytes)
{
  // Create semaphore
  if (!oe)
    oe = OSSemCreate(1);

  // Acquire lock
  OSSemPend(oe, 0, NULL);
  // 0xFF -> Type -> Numbytes -> bfr
  SerialPut(0xFF);
  SerialPut(type);
  SerialPut(bytes);
  
  unsigned it = 0;
  for (; it < bytes; ++it) {
    SerialPut(bfr[it]);
  }

  // Release lock
  OSSemPost(oe);

}

void ReceivePackets(void)
{
  SerialInit() ;
  
  static unsigned recieved = 0;
  for (;;)
  {
    int type, byte, bytes ;
    BYTE8 *bfr ;
    
    if (SerialGet() != 0xFF)
      continue ;
    
    switch (type = SerialGet())
    {
      //If flag is 1 we send chat
      //If flag is 2 we send time
      default:
        continue ;
      case 1:
	
      case 2:
      
      case 3:
        break;
    }
    
    bytes = SerialGet();
    bfr = (BYTE8 *) malloc(bytes) ;
    
    if (!bfr) {
      for (;;)
        ;
    }
    
    for (byte = 0; byte < bytes; byte++) {
      bfr[byte] = SerialGet() ; // Get chars
    }
    
    // Add recieved bytes
    if (type == 1) {
      recieved += bytes;
    }

    
    switch (type) {
      case 1:
        PostText(bfr);
        
        static char _char[] = "0000";
        FormatUnsigned(_char, recieved, 10, 4, ' ');
        SendPacket(3, _char, 4);
        break ;
      case 2:
        PostTime(bfr) ;
        break ;
      case 3:
        PostRecieved(bfr);
        break;
    }
  }
}

void InboundRecieved(void)
{
  WINDOW *remote ;
  
  remote = WindowCreate("Remcount", 11, 13, 32, 46) ;
  RecievedCreateQ() ;
  
  for (;;)
  {
    char *bfr;
    BYTE8 err;
    bfr = OSQPend(recieved_queue, 0, &err);
    WindowSetCursor(remote, 0, 7);
    WindowPutString(remote, bfr) ;
    free(bfr) ;
  }
}



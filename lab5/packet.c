#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>

#include "inbound.h"
#include "elapsed.h"
#include "serial.h"

static OS_EVENT* oe = NULL;
static OS_EVENT* char_queue = NULL;

static unsigned charcounter = 0;

void SendCharCountQ(void)
{
  if (!char_queue) {
    static void *char_q[20];
    char_queue = OSQCreate(char_q, ENTRIES(char_q));
  }
}

void PostChar(BYTE8 *bfr)
{
  SendCharCountQ();
  OSQPost(char_queue, bfr);
}

void ReceivePackets(void)
{
  SerialInit() ;
  
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
        break;
    }
    
    bytes = SerialGet();
    bfr = (BYTE8 *) malloc(bytes) ;
    if (!bfr)
    {
      for (;;)
        ;
    }
    
    for (byte = 0; byte < bytes; byte++)
    {
      if (type == 1)

    free(bfr);

    OSTimeDly(100);
  }
}


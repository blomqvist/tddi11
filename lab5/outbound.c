#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>
#include <ctype.h>
#include <dos.h>

#include "packet.h"
#include "serial.h"

OS_EVENT *kybd_queue = NULL ;
void OSKeyboardISR(void) ;

PRIVATE void KeyboardInit(void) ;

void OutboundThread(void)
{
  WINDOW *local ;
  
  /* INITIALIZATION: Paint the local window. Create a	*/
  /* mailbox object to receive keystroke codes from the	*/
  /* keyboard ISR. Initialize the keyboard hardware.	*/
  /* Point interrupt vector 33 at the keyboard ISR.	*/
  /* Unmask the IRQ line in the 8259 PIC.			*/
  
  local = WindowCreate("Local", 0, 10, 0, 79) ;
  KeyboardInit() ;
  /* SerialInit have a guard inside to prevent multiple initializations */
  SerialInit() ;
 
  for (;;)
  {
    BYTE8 err, scan_code ;
    char ascii ;
    
    /* Suspend this thread (let it "sleep") until a	*/
    /* keyboard interrupt posts something to our	*/
    /* mailbox.  But first position the cursor 	*/
    /* at the next character position as a prompt.	*/
    
    WindowSelect(local) ;
    scan_code = ((unsigned) OSQPend(kybd_queue, 0, &err)) & 0xFF ;
    if (scan_code & 0x80)
      continue ; /* Key up */
    
    /* The keyboard ISR just woke us up. scan_code	*/
    /* is the keystroke that occurred. First check	*/
    /* to see if it simply changes state, like caps	*/
    /* lock, shift, ctrl, or alt.  Then convert the	*/
    /* scancode to ascii using the current state.	*/
    
    if (SetsKybdState(scan_code))
      continue ;
    
    ascii = ScanCode2Ascii(scan_code) & 0xFF ;
    if (!isprint(ascii) && !iscntrl(ascii))
      continue ;

    /* Display the character in the local window.	*/
    
    WindowPutChar(local, ascii) ;
    
    SendPacket(1, &ascii, 1) ;
    if (ascii == '\r')
    {
      static char linefeed = '\n' ;
      WindowPutChar(local, linefeed) ;
      SendPacket(1, &linefeed, 1) ;
    }
  }
}

PRIVATE void KeyboardInit(void)
{
  static void *q[20] ;
  
  kybd_queue = OSQCreate(q, ENTRIES(q)) ;
  SetISR(IRQ2INT(IRQ_KYBD), OSKeyboardISR) ;
  outportb(0x21, inportb(0x21) & ~0x02) ;
}

#include <libepc.h>
#include <ctype.h>
#include <mtc.h>

#include "serial.h"

void OutBound(void)
{
  WINDOW *w ;
  
  w = WindowCreate("Local", 0, 10, 0, 79) ;
  if (!w)
    return ;
  
  for (;;)
  {
    BYTE8 code ;
    char ascii ;
    
    MtCYield() ;
    
    WindowSelect(w) ;
    
    if (!ScanCodeRdy())
      continue ;
    
    code = GetScanCode() ;
    
    if (code & 0x80)
      continue ;
    
    if (SetsKybdState(code))
      continue ;
    
    ascii = ScanCode2Ascii(code) & 0xFF ;
    if (!isprint(ascii) && !iscntrl(ascii))
      continue ;
    
    WindowPutChar(w, ascii) ;
    
    SerialPut(ascii) ;
    if (ascii == '\r')
    {
      WindowPutChar(w, '\n') ;
      SerialPut('\n') ;
    }
  }
}


#include <ctype.h>
#include <libepc.h>

#include "serial.h"

PRIVATE WINDOW *w ;

void InitOutBound(void)
{
  w = WindowCreate("Local", 0, 11, 0, 79) ;
}

void OutBound(void)
{
  WindowSelect(w) ;
  
  if (ScanCodeRdy())
  {
    BYTE8 code = GetScanCode() ;
    if (!(code & 0x80) && !SetsKybdState(code))
    {
      char ascii = ScanCode2Ascii(code) & 0xFF ;
      if (isprint(ascii) | iscntrl(ascii))
      {
        WindowPutChar(w, ascii) ;
        
        SerialPut(ascii) ;
        if (ascii == '\r')
        {
          WindowPutChar(w, '\n') ;
          SerialPut('\n') ;
        }
      }
    }
  }
}

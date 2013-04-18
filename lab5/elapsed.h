typedef struct TIME
{
  unsigned	hours ;
  unsigned	mins ;
  unsigned	secs ;
  unsigned	tenths ;
} TIME ;

void PostTime(BYTE8 *bfr) ;
void InboundTime() ;
void ElapsedLocal() ;

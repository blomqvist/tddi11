#include <libepc.h>

int main(int argc, char *argv[])
{
   ClearScreen(0x07);
   SetCursorPosition(0, 0);
   
   PutString("Hello World\r\n");
   
   return 0;
}

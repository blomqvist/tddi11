/*
 * Understanding bits, bytes, hexadecimal notation and data
 * representation is essential when programming close to hardware.
 *
 * This lab will let you use the bit-manipulation operations in C, and
 * will look at the behaviour of datatypes in C in conjuction with the
 * manipulations.
 *
 * How to write some literal values and types in C:
 *
 *  4711    A decimal signed integer
 *
 *  4711UL  A decimal unsigned long integer
 *
 *  0xA2    A hexadeciaml unsigned integer (162 deciaml)
 *          Also the bit pattern 0b10100010  
 *
 *  '3'     The ascii code (integer) for character 3
 *
 *  'Q'     The ascii code (integer) for letter Q
 *
 *  ""      Constant pointer to the ascii sequence {'\0'}
 *          Commonly known as the empty C-string.
 *  "3B"    Constant pointer to the ascii sequence {'3', 'B', '\0'}
 *
 *  3.14    A floating point number (float, double)
 *
 * A bit is either logic one or logic zero.
 * A nibble is 4 bits.
 * A byte is 8 bits.
 * A word is 2 bytes (16 bits).
 * A dword (double word) is 4 bytes (32 bits)
 * A qword (quadruple word) is 8 bytes (64 bits)
 *
 * In C an int is as many bits as the normal CPU register length.
 * (CPU dependent)
 */

#include <stdio.h>

#define new_line printf("\n")

/* Some aliases for datatypes. */
typedef char byte;
typedef short word;
typedef unsigned char ubyte;
typedef unsigned short uword;

/* Functions ready to use, found last in file. */
char* byte_to_binary_buffer(byte b, char* buf);
char* byte_to_binary(byte b);
char* word_to_binary(word b);

/* Functions you will implement later, found last in file. */
char low_bcd(byte b);
char high_bcd(byte b);

/* Example of function-like macros:
   Presume this macro-definition:
   
     #define square(a) (a*a)

   Presume this code:

     int b = square( 3+4 );

   Produces this code:

     int b = (3+4*3+4);

   A better macro use parentheses vigourusly:
   
     #define square(a) ((a)*(a))
     int b = square( 3+4 );
     int b = ((3+4)*(3+4));
 */

#define low_nibble(byte)  /* YOUR CODE HERE */
#define high_nibble(byte) /* YOUR CODE HERE */

#define low_byte(word)  /* YOUR CODE HERE */
#define high_byte(word) /* YOUR CODE HERE */

int main()
{
  int input;
  byte B;
  word W;

  new_line;
  printf("Table of 16 8-bit values.\n");
  printf("-------------------------\n");
  printf(" Hexa-   Signed  Unsigned  Binary\n");
  printf("decimal  Decimal  Decimal  Pattern\n");
  byte p = -8;
  for (int i = 0; i < 16; ++i)
  {
    printf("   0x%02hhx  %7hhd  %7hhu  %6s\n",
           p, p, p, byte_to_binary(p));
    ++p;
  }
  new_line;
  
  printf("Enter B in hexadecimal notation: ");
  scanf("%x", (unsigned int*)&input);
  B = input;
  
  printf("Enter W in decimal notation: ");
  scanf("%d", &input);
  W = input;

  /* Your modifications go below this line. */

#if 0
  /* You can use this kind of #if to disable code that do not compile */
#endif
  
  new_line;
  printf("B =     0x%02hhX (hexadecimal)\n", B);
  printf("B =     %4hhd (decimal)\n", B);
  printf("B =     %4hhu (unsigned)\n", B);
  printf("B = %s (binary)\n", byte_to_binary(B)); /* EXAMPLE HERE. */

  new_line;
  printf("W =   0x%04hX (hexadecimal)\n", /* YOUR CODE HERE */);
  printf("W =   %6hd (decimal)\n", /* YOUR CODE HERE */);
  printf("W =   %6hu (unsigned)\n", /* YOUR CODE HERE */);
  printf("W = %s (binary)\n", /* YOUR CODE HERE */);
  
  new_line;
  printf("~ %s  (B)\n", /* YOUR CODE HERE */);
  printf("----------\n");
  printf("= %s\n", /* YOUR CODE HERE */);

  /* If you think about it you can determine each missing constant by
   * entering appropriate input. You only need one test run to find
   * each constant. */
  new_line;
  printf("  %s  (B)\n", /* YOUR CODE HERE */);
  printf("& %s  (%s)\n", "????????", "figure out the constant");
  printf("----------\n");
  printf("= %s\n", /* YOUR CODE HERE */);

  new_line;
  printf("  %s  (B)\n", /* YOUR CODE HERE */);
  printf("| %s  (%s)\n", "????????", "figure out the constant");
  printf("----------\n");
  printf("= %s\n", /* YOUR CODE HERE */);

  new_line;
  printf("  %s  (B)\n", /* YOUR CODE HERE */);
  printf("^ %s  (%s)\n", "????????", "figure out the constant");
  printf("----------\n");
  printf("= %s\n", /* YOUR CODE HERE */);

  new_line;
  printf("  %s  (W)\n", /* YOUR CODE HERE */);
  printf("+ %s  (B)\n", /* YOUR CODE HERE */);
  printf("------------------\n");
  printf("= %s\n", /* YOUR CODE HERE */);
  
  new_line;
  printf("B original reference value       : %s\n", /* YOUR CODE HERE */);
  printf("B arithm/logic shift 2 steps left: %s\n", /* YOUR CODE HERE */);
  
  new_line;
  printf("B original reference value       : %s\n", /* YOUR CODE HERE */);
  printf("B arithmetic shift 2 steps right : %s\n", /* YOUR CODE HERE */);
  printf("B logical shift 2 steps right    : %s\n", /* YOUR CODE HERE */);

  new_line;
  printf("W original reference value   : %s\n", /* YOUR CODE HERE */);
  printf("W with 4 central bits set    : %s\n", /* YOUR CODE HERE */);
  printf("W with 4 central bits cleared: %s\n", /* YOUR CODE HERE */);
  printf("W with 4 central bits toggled: %s\n", /* YOUR CODE HERE */);
  
  new_line;
  printf("W original reference value         : %s\n", /* YOUR CODE HERE */);
  printf("B original reference value         :     %s\n", /* YOUR CODE HERE */);
  printf("W with 8 central bits replaced by B: %s\n", /* YOUR CODE HERE */);

  new_line;
  printf("W original reference value: %s\n", /* YOUR CODE HERE */);
  printf("W with bit B toggled      : %s\n", /* YOUR CODE HERE */);

 
  /* In BCD each nibble of a byte represents one decimal digit.
   * Each nibble in BCD is only defined for range 0-9.
   * If any nibble represent the values 10-15 it is shown as '?'.
   */
  new_line;
  byte B_low = low_nibble(B); /* Implement the macros!! */
  byte B_high = high_nibble(B);
  printf("B reference = %8s %hhx\n", /* YOUR CODE HERE */, /* AND HERE*/);
  printf("High nibble = %-8s %hhx\n", /* YOUR CODE HERE */, /* AND HERE*/);
  printf("Low  nibble = %8s  %hhx\n", /* YOUR CODE HERE */, /* AND HERE*/);
  /* Implement the BCD functions below found below. */
  printf("B as BCD    = %10c%c\n", high_bcd(B), low_bcd(B));
  
  new_line;
  byte W_low = low_byte(W); /* Implement the macros!! */
  byte W_high = high_byte(W);
  printf("W      = %16s\n", /* YOUR CODE HERE */);
  printf("W_high = %-16s\n", /* YOUR CODE HERE */);
  printf("W_low  = %16s\n", /* YOUR CODE HERE */);
  
  /* Interpret W as Time of Day in hours, minutes and seconds.
   * The 6 lowest bits are seconds (0-59)
   * The 6 following bits are minutes (0-59)
   * The four highest bits are hours (0-12)
   * Values outside the given range is indicated with "??"
   */
  new_line;
  printf("W as Time of day = ");
  byte hour = /* YOUR CODE HERE */;
  byte minute = /* YOUR CODE HERE */;
  byte second = /* YOUR CODE HERE */;

  if (/* YOUR CODE HERE */)
    printf("??:");
  else
    printf("%02hhd:", hour);

  /* YOUR CODE HERE */
  
  return 0; 
}

char low_bcd(byte b)
{
  /* YOUR CODE HERE */

  return '?';
}

char high_bcd(byte b)
{
  /* YOUR CODE HERE */

  return '?';
}



/************** Given code, do not modify below this line. ****************/

char* byte_to_binary_buffer(byte b, char* buf)
{
  int i;
  for (i = 7; i >= 0; --i)
  {
    buf[i] = (b & 0x1) + '0';
    b >>= 1;
  }
  return buf;
}

char* byte_to_binary(byte b)
{
  static char binbuf[8+1] = {0,0,0,0,0,0,0,0,0};
  return byte_to_binary_buffer(b, binbuf);
}

char* word_to_binary(word w)
{
  static char binbuf[16+1] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  byte_to_binary_buffer(low_byte(w), &binbuf[8]);
  return byte_to_binary_buffer(high_byte(w), binbuf);
}

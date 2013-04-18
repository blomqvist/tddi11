#include <stdio.h>

typedef unsigned long long int ulli;
typedef unsigned int uint;

uint exp_bits(ulli n);
uint get_exponent(ulli n);
ulli get_mantissa(ulli n);
ulli set_exponent(ulli n, uint exp);

int main()
{
  ulli number;
  uint new_exponent;

  printf("                             ................\n");
  printf("Enter 16 hexadeximal digits: ");
  scanf("%llx", &number);
  printf("Enter hexadeximal digits for new exponent: ");
  scanf("%x", &new_exponent);
  printf("\n");

  printf("entered number         (hex) %016llx\n", number);
  printf("number of exp bits are (dec) %16u\n", exp_bits(number));
  printf("value of exponent is   (hex) %16x\n", get_exponent(number));
  printf("value of mantissa is   (hex) %16llx\n", get_mantissa(number));

  number = set_exponent(number, new_exponent);
  printf("\n");
  
  printf("modified number        (hex) %016llx\n", number);
  printf("number of exp bits are (dec) %16u\n", exp_bits(number));
  printf("value of exponent is   (hex) %16x\n", get_exponent(number));
  printf("value of mantissa is   (hex) %16llx\n", get_mantissa(number));

  return 0;
}

/* HINT:
   Study the binary result of (( 1ULL << X ) - 1) for various X.
   Note which bits that are high. May be useful for some masks.
   
   Easy to forget is that literal number 1 is only 32-bit.
   Writing 1ULL gives 64-bit unsigned long long.

   A suitable simplification of the assignment (for reduced score) is
   to assume the exponent is always 11 bits and solve accordingly.
*/

/* Return the number of exponent bits in 64-bit ultimate number n */
uint exp_bits(ulli n)
{
  return n; /* Dummy code, Your code instead! */
}

/* Return the unsigned value of exponent bits in 64-bit ultimate number n */
uint get_exponent(ulli n)
{
  return n; /* Dummy code, Your code instead! */
}

/* Replace the exponent bits in 64-bit ultimate number n with value of exp */
ulli set_exponent(ulli n, uint exp)
{
  return n+exp; /* Dummy code, Your code instead! */
}


/* NOTE!!
 * If you solved 'get_exponent' above correct 'get_mantissa' does not
 * add much points, solve it only if you have the time.
 */
  
/* Return the unsigned value of mantissa bits in 64-bit ultimate number n */
ulli get_mantissa(ulli n)
{
  return n; /* Dummy code, Your code instead! */
}


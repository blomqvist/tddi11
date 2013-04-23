#include <libepc.h>

void lmultiply(unsigned long long int l1,
                unsigned long long int l2,
                unsigned char *result);

struct test_case {
  unsigned long long int a;
  unsigned long long int b;
  unsigned long long int rh;
  unsigned long long int rl;
};

struct test_case cases[6] = {

  { 0x0000111122223333ULL, 0x0000555566667777ULL,
    0x0000000005B061D9ULL, 0x58BF0ECA7C0481B5ULL },

  { 0x3456FEDCAAAA1000ULL, 0xEDBA00112233FF01ULL,
    0x309A912AF7188C57ULL, 0xE62072DD409A1000ULL },

  { 0xFFFFEEEEDDDDCCCCULL, 0xBBBBAAAA99998888ULL,
    0xBBBB9E2692C5DDDCULL, 0xC28F7531048D2C60ULL },

  { 0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL,
    0xFFFFFFFFFFFFFFFEULL, 0x0000000000000001ULL },
  
  { 0x00000001FFFFFFFFULL, 0x00000001FFFFFFFFULL,
    0x0000000000000003ULL, 0xFFFFFFFC00000001ULL },

  { 0xFFFEFFFFFFFFFFFFULL, 0xFFFF0001FFFFFFFFULL,
    0xFFFE0002FFFDFFFEULL, 0x0001FFFE00000001ULL }
};

void PutUnsignedLongLong(unsigned long long int* ulli)
{
  unsigned long int* uli = (unsigned long int*)ulli; 
  PutUnsigned(uli[1], 16, 8);
  PutUnsigned(uli[0], 16, 8); 
}

#define LOW32(x)  ((x) & 0xFFFFFFFF)
#define HIGH32(x) (((x) >> 32) & 0xFFFFFFFF)

void lmultiply(unsigned long long int l1,
		unsigned long long int l2,
		unsigned char *result)
{
  int i = 0;
  unsigned long long int al_bl, al_bh, ah_bl, ah_bh, res;
  unsigned int* res_ptr = result;

  al_bl = LOW32(l1)  * LOW32(l2);
  al_bh = LOW32(l1)  * HIGH32(l2);
  ah_bl = HIGH32(l1) * LOW32(l2);
  ah_bh = HIGH32(l1) * HIGH32(l2);
  
  res = al_bl;

  for (i = 0; i < 4; ++i) 
    res_ptr[i] = 0;
  
  for (i = 0; i < 2; ++i) { 
    *res_ptr = res >> (i*32);
    ++res_ptr;
  }

  res = al_bh;

  --res_ptr;

  for (i = 0; i < 2; ++i) { 
    *res_ptr += res >> (i*32);
    ++res_ptr;
  }

  --res_ptr;
  --res_ptr;
  res = ah_bl;

  for (i = 0; i < 2; ++i) { 
    *res_ptr += res >> (i*32);
    ++res_ptr;
  }
 
  res = ah_bh;
  --res_ptr;

  for (i = 0; i < 2; ++i) { 
    *res_ptr += res >> (i*32);
    ++res_ptr;
  }

}

int main(int argc, char *argv[])
{
  unsigned char result[16];
  int i;
  
  ClearScreen(0x07);
  SetCursorPosition(0, 0);

  for (i = 0; i < 6; ++i)
  {
    PutString("Test : ");
    PutUnsignedLongLong(&cases[i].a);
    PutString(" * ");
    PutUnsignedLongLong(&cases[i].b); 
    PutString("\r\n");
   
    PutString("    == ");
    PutUnsignedLongLong(&cases[i].rh);
    PutUnsignedLongLong(&cases[i].rl);
    PutString("\r\n");
    
    lmultiply(cases[i].a, cases[i].b, result);
    
    PutString("Result ");
    PutUnsignedLongLong(&result[8]);
    PutUnsignedLongLong(&result[0]); 
    PutString("\r\n");
    
    PutString("\r\n");
  }

  return 0;
}

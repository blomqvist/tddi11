#ifndef _RIMS_H_
#define _RIMS_H_

#include <stdio.h>

typedef enum { false, true } bool;
typedef unsigned char byte;

extern volatile byte B;
extern volatile byte A;
extern volatile byte READY;

void TimerISR();
//void TimerSet(int msec);
//void TimerOn();
void TimerSetOnce(int msec);

#define B0 assign_bit_0_in_B_instead_of_B0
#define B1 assign_bit_1_in_B_instead_of_B1
#define B2 assign_bit_2_in_B_instead_of_B2
#define B3 assign_bit_3_in_B_instead_of_B3
#define B4 assign_bit_4_in_B_instead_of_B4
#define B5 assign_bit_5_in_B_instead_of_B5
#define B6 assign_bit_6_in_B_instead_of_B6
#define B7 assign_bit_7_in_B_instead_of_B7

#define A0 read_bit_0_in_A_instead_of_A0
#define A1 read_bit_1_in_A_instead_of_A1
#define A2 read_bit_2_in_A_instead_of_A2
#define A3 read_bit_3_in_A_instead_of_A3
#define A4 read_bit_4_in_A_instead_of_A4
#define A5 read_bit_5_in_A_instead_of_A5
#define A6 read_bit_6_in_A_instead_of_A6
#define A7 read_bit_7_in_A_instead_of_A7


/* System and compatibility things */

#define BASE_TICK 5 /* ms */
#define UNUSED __attribute__ (( unused ))
#define debug(format, ...) // printf(format, ## __VA_ARGS__ )

/* Increase compatibility to RIMS and avoid extensive CPU usage :-) */
int  app_main();
bool true_test( int, const char* );

#define main( ... ) app_main(void)
#define while( cond ) while ( true_test(cond, #cond) )

#endif

//------------------------------------------------------------------------------
// Prog: BlinkerAllC.c
// Name: Timothy Leach
// Func: Given a Nios Timer module in continous run mode w/ a fixed period,
//       Toggle all 18 DE2-115 LEDs every time the timer rolls over past zero.
//
//------------------------------------------------------------------------------
# include <alt_types.h>
#define LED_BASE 0x????????       // LED PIO Base address. Value TBD by Qsys.
#define TIMER_BASE 0x????????     // TIMER   Base address. Value TBD by Qsys.

int main()
{
  volatile alt_u32 * LEDBase = (alt_u32 *) LED_BASE;
  volatile alt_u16 * TimerBase = (alt_u16 *) TIMER_BASE;

  // Set all LEDs to OFF
  LEDBase = 0x0000;

  // Set timer CONT  bit to continuous mode
  // and set the START bit to start timer
  *(TimerBase + 1) = 0x03;

  while (1)
  {
      asm volatile (
        "LOOP: \n\t"
        "ldb r7, 0(%[Rcounter]) \n\t"
        "andhi r7, r7, 0x01\n\t"
        "bne r7, r0, CONTINUE \n\t"                     // Branch if TO bit is not 0
        "br LOOP \n\t"                                  // Loop until TO bit is not 0
        "CONTINUE:\n\t"
        "andhi %[RLED], %[RLED] 0xffff \n\t"
        "andhi %[Rcounter], %[Rcounter], 0x01\n\t"

      :
      :[Rcounter] "r" (TimerBase), [RLED] "r" (LEDBase)
      :"memory", "r7"
      );
  }

  return 0;
}
//------------------------------------------------------------------------------
// Func: BinToAscii()

//----------------------------

void BinToAscii(char* buf, alt_u32 number)
{
    alt_u8 tempNum;
    alt_u8 i;
    for(i = 0; i < 10; i++)
    {
        tempNum = num % 10;
        buf[i] = tempNum;
        num = num/10;
    }
}


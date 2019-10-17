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
    // spin while TO bit=0 (=> no rollover)
      while(*TimerBase & 0xFF)
      {}

    // Toggle all LEDs
      LEDBase = 0xFFFF;

    // Clear timer TO bit
      *TimerBase ^= 0x01;
  }

  return 0;
}
//------------------------------------------------------------------------------

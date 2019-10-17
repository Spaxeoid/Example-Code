//------------------------------------------------------------------------------
// Prog: BlinkerAllC.c
// Name: Timothy Leach
// Func: Given a Nios Timer module in continous run mode w/ a fixed period,
//       Toggle all 18 DE2-115 LEDs every time the timer rolls over past zero.
//
//------------------------------------------------------------------------------
# include <alt_types.h>
#define TIMER_BASE 0x????????     // TIMER   Base address. Value TBD by Qsys.

int main()
{
    volatile alt_u32* addressPIO = 0x??????;
    volatile alt_u16 * TimerBase = (alt_u16 *) TIMER_BASE;
    volatile alt_u32* jtagPTR = 0x00081000;
    volatile alt_u32 edge;
    alt_u32 timeA = 0x00000000;
    alt_u32 timeB = 0x00000000;
    alt_u32 time;
    alt_u8 buf[256];

    while(1)
    {
        *(TimerBase + 1) = 0xff;
        edge = *(addressPIO + 3);
        while(edge == 0x0000){}
        edge = 0x0000;
        timeB = *(TimerBase + 4);

        while(edge == 0x0000){}
        edge = 0x0000;
        timeA = *(TimerBase + 4);

        time = timeA - timeB;

        BinToAscii(buf, time);
        TerminalPrintString(buf, jtagPTR);
    }



    return 0;
}
//------------------------------------------------------------------------------
// Function: Print the argument pointer's char string to JTAG UART (stdout)
// Args: strPtr = pointer to start of char string in memory.
//       jtagPTR = pointer to the JTAG UART
//------------------------------------------------------------------------------
void TerminalPrintString(alt_u8* strPtr, volatile alt_u32* jtagPTR)
{
    alt_u32 control;
    while (*strPtr != 0x00)     // While current char != NULL
    {
        control = *(jtagPTR + 1);
        if(control & 0xFFFF0000)
        {
            *(jtagPTR) = *strPtr;
            strPtr++;                 // Advance to next char
        }
    }
}

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
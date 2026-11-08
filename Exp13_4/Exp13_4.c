/* ========================================================================== */
/*             Exp13_4.c : Nested Interrupt of Timer 0 & Timer 1              */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

static volatile uint16_t int0_count, int1_count; // interrupt counter
static volatile uint8_t LED;                     // LED output value

void TF0_ISR(void) __interrupt(1)
{                 // Timer 0 (high priority) interrupt function
    int0_count--; // interrupt by 1000 times ?
    if (int0_count == 0) {
        int0_count = 1000;
        LED ^= 0x01; // if yes, blink LED1
        DIG_SELECT = LED;
    }
}

void TF1_ISR(void) __interrupt(3)
{                 // Timer 1 (low priority) interrupt function
    int1_count--; // interrupt by 4000 times ?
    if (int1_count == 0) {
        int1_count = 4000;
        ET0 = 0; // guard shared LED/DIG_SELECT against high-priority TF0_ISR
        LED ^= 0x08; // if yes, blink LED4
        DIG_SELECT = LED;
        ET0 = 1;
    }
}

void main(void)
{
    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, "Timer 1  Timer 0"); // display title
    LCD_string(0xC0, " LED4      LED1 ");

    int0_count = 1000; // int. counter(10000Hz/1000 = 10Hz)
    int1_count = 4000; // int. counter(8000Hz/4000 = 2Hz)
    DIG_SELECT = LED;  // initialize LED4, LED1

    TMOD = 0x22;     // Timer 0 and 1, mode 2
    TH0 = (0 - 200); // initialize time constant of Timer 0 (10000Hz)
    TL0 = (0 - 200);
    TH1 = (0 - 250); // initialize time constant of Timer 1 (8000Hz)
    TL1 = (0 - 250);
    TF0 = 0;
    TF1 = 0;

    PT0 = 1; // Timer 0 high priority, Timer 1 low priority (enables nesting)
    PT1 = 0;
    TR0 = 1;
    TR1 = 1;
    ET0 = 1;
    ET1 = 1;
    EA = 1;

    while (true) {
        ; // infinite loop
    }
}

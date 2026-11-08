/* ========================================================================== */
/*              Exp13_3.c : Timer 2, Auto-reload Mode Interrupt               */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

volatile uint8_t int_count; // interrupt counter
volatile uint8_t LED;       // LED output value

void TF2_ISR(void) __interrupt(5)
{                // Timer 2 interrupt function
    TF2 = 0;     // clear TF2 flag
    int_count--; // interrupt by 20 times ?
    if (int_count == 0) {
        int_count = 20;
        LED ^= 0x09; // if yes, blink LED4, LED1
        DIG_SELECT = LED;
    }
}

void main(void)
{
    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " T2,Auto-reload "); // display title
    LCD_string(0xC0, " blink LED4 & 1 ");

    int_count = 20; // interrupt counter(40Hz/20 = 2Hz)
    LED = 0x01;     // initialize LED4, LED1
    DIG_SELECT = LED;

    T2CON = 0x00;                   // stop Timer 2 during setup
    T2MOD = 0x00;                   // (up counter)
    RCAP2H = (0 - 50000U) >> 8;     // initialize time constant
    RCAP2L = (0 - 50000U) & 0x00FF; // (24MHz/12/50000 = 40Hz)
    TH2 = (0 - 50000U) >> 8;        // initial Timer 2 value
    TL2 = (0 - 50000U) & 0x00FF;
    TR2 = 1; // Timer 2, 16-bit auto-reload run
    PT2 = 1; // interrupt priority
    ET2 = 1; // enable Timer 2 interrupt
    EA = 1;

    while (true) {
        ; // infinite loop
    }
}

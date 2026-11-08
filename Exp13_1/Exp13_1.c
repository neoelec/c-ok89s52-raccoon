/* ========================================================================== */
/*                   Exp13_1.c : Timer 0, Mode 1 Interrupt                    */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

volatile uint8_t int_count; // interrupt counter
volatile uint8_t LED;       // LED output value

void TF0_ISR(void) __interrupt(1)
{                            // Timer 0 interrupt function
    TH0 = (0 - 50000U) >> 8; // initial Timer 0 value
    TL0 = (0 - 50000U) & 0x00FF;

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

    LCD_string(0x80, " Timer 0,Mode 1 "); // display title
    LCD_string(0xC0, " blink LED4 & 1 ");

    int_count = 20; // interrupt counter(40Hz/20 = 2Hz)
    LED = 0x01;     // initialize LED4, LED1
    DIG_SELECT = LED;

    TMOD = (TMOD & 0xF0) | 0x01; // Timer 0, mode 1
    TH0 = (0 - 50000U) >> 8;     // initial Timer 0 value
    TL0 = (0 - 50000U) & 0x00FF; // (24MHz/12/50000 = 40Hz)
    TF0 = 0;
    TR0 = 1;
    PT0 = 1; // interrupt priority
    ET0 = 1; // enable Timer 0 interrupt
    EA = 1;

    while (true) {
        ; // infinite loop
    }
}

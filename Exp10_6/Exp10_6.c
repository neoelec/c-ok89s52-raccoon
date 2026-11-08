/* ========================================================================== */
/*             Exp10_6.c : -INT0 Interrupt Program(Edge Trigger)              */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void INT0_ISR(void) __interrupt(0)
{ // -INT0 interrupt function
    uint8_t i, LED;

    for (i = 1, LED = 0x01; i <= 5; i++) { // shift from LED1 to LED4
        DIG_SELECT = LED;
        Delay_ms(200); // delay 200 ms
        LED <<= 1;
    }
}

void main(void)
{
    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, "-INT0 Interrupt "); // display title
    LCD_string(0xC0, " (Edge Trigger) ");

    IT0 = 1; // -INT0=edge trigger
    IE0 = 0;
    PX0 = 1; // interrupt priority
    EX0 = 1; // enable -INT0 interrupt
    EA = 1;

    while (true) {
        ; // wait interrupt
    }
}

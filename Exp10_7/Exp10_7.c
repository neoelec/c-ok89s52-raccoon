/* ========================================================================== */
/*          Exp10_7.c : -INT0 Interrupt Count Program(No Debouncing)          */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

static volatile uint8_t int_count; // interrupt counter

void INT0_ISR(void) __interrupt(0)
{                // -INT0 interrupt function
    int_count++; // increment interrupt count (no debouncing)
}

void main(void)
{
    uint8_t i, j, LED, count, shown = 0;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, "  -INT0 Count   "); // display title
    LCD_string(0xC0, "      000       ");

    IT0 = 1; // -INT0=edge trigger
    IE0 = 0;
    PX0 = 1; // interrupt priority
    EX0 = 1; // enable -INT0 interrupt
    EA = 1;

    while (true) {
        for (i = 1, LED = 0x01; i <= 4; i++) { // shift from LED1 to LED4
            DIG_SELECT = LED;
            for (j = 0; j < 20; j++) {
                count = int_count;
                if (count != shown) {
                    LCD_command(0xC6); // display interrupt count
                    LCD_3dec(count);
                    shown = count;
                }

                Delay_ms(10); // 20 * 10 ms = 200 ms
            }

            LED <<= 1;
        }
    }
}

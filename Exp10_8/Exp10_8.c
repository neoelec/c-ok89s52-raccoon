/* ========================================================================== */
/*           Exp10_8.c : -INT0 Interrupt Count Program(Debouncing)            */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

static volatile __bit int_req; // interrupt request flag

void INT0_ISR(void) __interrupt(0)
{                // -INT0 interrupt function
    EX0 = 0;     // mask bounce edges until main completes debouncing
    int_req = 1; // request count update in main loop
}

void main(void)
{
    uint8_t i, j, LED, int_count = 0;

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
                if (int_req) {
                    int_req = 0;
                    Beep();            // beep and delay for debouncing
                    int_count++;       // increment interrupt count
                    LCD_command(0xC6); // display interrupt count
                    LCD_3dec(int_count);
                    do {
                        while (!P3_2) {
                            ; // wait until SW2 off(-INT0=1)
                        }

                        Delay_ms(50); // delay for release debouncing
                    } while (!P3_2);

                    IE0 = 0; // clear any bounce interrupt flag
                    EX0 = 1;
                }

                Delay_ms(10); // 20 * 10 ms = 200 ms
            }

            LED <<= 1;
        }
    }
}

/* ========================================================================== */
/*              Exp18_1.c : Execution Time by Optimization Level              */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#pragma opt_code_speed

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint16_t i, time;
    volatile uint16_t j;
    volatile float x, y;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " Execution Time "); // display title
    LCD_string(0xC0, "   00000 [us]   ");

    TMOD = (TMOD & 0xF0) | 0x01; // Timer 0, mode 1
    TR0 = 0;
    TH0 = 0; // clear Timer 0
    TL0 = 0;
    TR0 = 1; // start Timer 0

    for (i = 1, x = 0.0; i <= 20; i++) {
        j = i + 500;       // integer addition
        j = i * 500;       // integer multiplication
        x += 12.34;        // real addition
        y = x * 56.78 * j; // real & integer
    }

    TR0 = 0;                           // stop Timer 0
    time = ((uint16_t)TH0 << 8) | TL0; // read Timer 0
    LCD_command(0xC3);                 // display execution time
    LCD_5dec(time / 2);

    while (true) {
    }
}

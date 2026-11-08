/* ========================================================================== */
/*          Exp11_2.c : 7-Segment LED Display - Different Characters          */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t i, j, digit;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " 7-segment LED  "); // display title
    LCD_string(0xC0, "                ");

    while (true) {
        for (i = 1; i <= 250; i++) { // display from 0 to 7
            for (j = 0, digit = 0x80; j <= 7; j++) {
                DIG_SELECT = 0x00;        // blank before changing pattern
                SEG_PATTERN = Bin2LED(j); // output segment pattern data
                DIG_SELECT = digit;       // output digit select data
                Delay_ms(1);              // delay 1ms
                digit >>= 1;
            }
        }

        for (i = 1; i <= 250; i++) { // display from 8 to F
            for (j = 8, digit = 0x80; j <= 0x0F; j++) {
                DIG_SELECT = 0x00;        // blank before changing pattern
                SEG_PATTERN = Bin2LED(j); // output segment pattern data
                DIG_SELECT = digit;       // output digit select data
                Delay_ms(1);              // delay 1ms
                digit >>= 1;
            }
        }
    }
}

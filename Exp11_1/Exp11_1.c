/* ========================================================================== */
/*            Exp11_1.c : 7-Segment LED Display - Same Characters             */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    static const uint8_t __code random[8] = { 0x04, 0x80, 0x40, 0x02,
                                              0x08, 0x10, 0x20, 0x02 };
    uint8_t i, j, digit;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " 7-segment LED  "); // display title
    LCD_string(0xC0, "                ");

    while (true) {
        DIG_SELECT = 0xFF;            // select all digits
        for (i = 0; i <= 0x0F; i++) { // display from 0 to F
            SEG_PATTERN = Bin2LED(i);
            Delay_ms(1000);
        }

        SEG_PATTERN = Bin2LED('H'); // display "H"
        Delay_ms(1000);
        SEG_PATTERN = Bin2LED('-'); // display "-"
        Delay_ms(1000);
        SEG_PATTERN = Bin2LED('.'); // display "."
        Delay_ms(1000);
        SEG_PATTERN = Bin2LED(0x27); // display "'"
        Delay_ms(1000);

        for (i = 1, digit = 0x80; i <= 8; i++) { // display random pattern
            DIG_SELECT = digit;
            for (j = 0; j <= 7; j++) {
                SEG_PATTERN = random[j];
                Delay_ms(100);
            }

            digit >>= 1;
        }
    }
}

/* ========================================================================== */
/*                     Exp06_2.c : Basic Decimal Addition                     */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t i, j;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " 8-Bit Addition "); // display title
    LCD_string(0xC0, "000 + 000 = 000 ");

    for (i = 10; i <= 200; i += 10) {     // i = from 10 to 200
        for (j = 10; j <= 200; j += 10) { // j = from 10 to 200
            LCD_command(0xC0);            // display augend
            LCD_3dec((uint16_t)i);
            LCD_command(0xC6); // display addend
            LCD_3dec((uint16_t)j);
            LCD_command(0xCC); // display result of addition
            LCD_3dec((uint16_t)(i + j));
            Delay_ms(500);
        }
    }

    while (true) {
    }
}

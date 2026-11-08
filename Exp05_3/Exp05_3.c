/* ========================================================================== */
/*                     Exp05_3.c : Integer Number Display                     */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t i;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " INTEGER = 000  "); // display title
    LCD_string(0xC0, "= 00H = 00000000");

    for (i = 1; i > 0; i++) { // integer number from 1 to 255
        LCD_command(0x8B);    // display decimal number
        LCD_3dec((uint16_t)i);
        LCD_command(0xC2); // display hexadecimal number
        LCD_02hex(i);
        LCD_command(0xC8); // display binary number
        LCD_08bin(i);
        Delay_ms(1000);
    }

    while (true) {
    }
}

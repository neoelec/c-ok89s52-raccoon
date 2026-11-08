/* ========================================================================== */
/*                   Exp06_1.c : Basic Hexadecimal Addition                   */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t i, j;
    uint16_t k;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    while (true) {
        Beep();
        LCD_string(0x80, " 8-Bit Addition "); // display title
        LCD_string(0xC0, "00H + 00H = 00H ");

        for (i = 1, j = 0x11; i <= 7;
             i++, j += 0x11) { // integer from 0x11 to 0x77
            LCD_command(0xC0); // display augend
            LCD_02hex(j);
            LCD_command(0xC6); // display addend
            LCD_02hex(j);
            LCD_command(0xCC); // display result of addition
            LCD_02hex(j + j);
            Delay_ms(2000);
        }

        Beep();
        LCD_string(0x80, " 0000H + 0000H  "); // display title
        LCD_string(0xC0, "    = 0000H     ");

        for (i = 1, k = 0x1111; i <= 7;
             i++, k += 0x1111) { // integer from 0x1111 to 0x7777
            LCD_command(0x81);   // display augend
            LCD_04hex(k);
            LCD_command(0x89); // display addend
            LCD_04hex(k);
            LCD_command(0xC6); // display result of addition
            LCD_04hex(k + k);
            Delay_ms(2000);
        }
    }
}

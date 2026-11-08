/* ========================================================================== */
/*                Exp10_3.c : Key Input Count - No Debouncing                 */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t key1 = 0, key2 = 0, key3 = 0, key4 = 0;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, "KEY1=00  KEY2=00"); // display title
    LCD_string(0xC0, "KEY3=00  KEY4=00");

    while (true) {
        switch (P1 & 0x1E) { // key input without debouncing
        case 0x1C:
            DIG_SELECT = 0x01;
            key1++; // display key1 count
            if (key1 > 99) {
                key1 = 0;
            }

            LCD_command(0x85);
            LCD_2dec(key1);
            break;
        case 0x1A:
            DIG_SELECT = 0x02;
            key2++; // display key2 count
            if (key2 > 99) {
                key2 = 0;
            }

            LCD_command(0x8E);
            LCD_2dec(key2);
            break;
        case 0x16:
            DIG_SELECT = 0x04;
            key3++; // display key3 count
            if (key3 > 99) {
                key3 = 0;
            }

            LCD_command(0xC5);
            LCD_2dec(key3);
            break;
        case 0x0E:
            DIG_SELECT = 0x08;
            key4++; // display key4 count
            if (key4 > 99) {
                key4 = 0;
            }

            LCD_command(0xCE);
            LCD_2dec(key4);
            break;
        }
    }
}
